#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Allows dynamic resolution from cnc ddraw.ini or current display metrics


#define NV_SCREEN_FULLSCREEN 0x01 // Nova sets this from prefs
#define NV_SCREEN_UNKNOWN_1  0x02 // Nova always sets this
#define NV_SCREEN_BORDERLESS 0x20 // Nova never sets this
#define NV_SCREEN_ENUMERATE_DD_DEVICES 0x10000 // Exact meaning uncertain; Nova never sets this

// cnc-ddraw specific settings
#define WM_TOGGLE_FULLSCREEN WM_APP+117

#define CNC_DDRAW_SET_FULLSCREEN 1
#define CNC_DDRAW_SET_WINDOWED 2

// Replace CALL to InitializeMonitor
CALL(0x0041629B, _InitializeMonitor);

// Switch between windowed and fullscreen mode without restart
CALL(0x00488FE6, _ToggleFullscren);

// Replace original runInAWindow bool with ours to make sure the game doesn't change its behavior
// Init runInAWindow bool
SETDWORD(0x004C7750 + 2, _g_runInAWindow);
// Init secondary runInAWindow bool - Used to check if the "Run In A Winodw" setting was changed in the menu
SETDWORD(0x004C7618 + 3, _g_runInAWindow);

bool g_runInAWindow;

void InitializeMonitor() {
    // Setup g_runInAWindow bool
    char buf[8];
    GetPrivateProfileStringA("ddraw", "fullscreen", "false", buf, sizeof buf, ".\\ddraw.ini");
    BOOL upscaled = _strcmpi(buf, "yes") == 0 || _strcmpi(buf, "true") == 0 || _strcmpi(buf, "1") == 0;

    GetPrivateProfileStringA("ddraw", "windowed", "false", buf, sizeof buf, ".\\ddraw.ini");
    BOOL windowed = _strcmpi(buf, "yes") == 0 || _strcmpi(buf, "true") == 0 || _strcmpi(buf, "1") == 0;

    g_runInAWindow = g_nv_runInAWindowPref = windowed && !upscaled;

    // Get width and height from the ini
    int width = GetPrivateProfileIntA("EV Nova", "game_width", 0, ".\\ddraw.ini");
    int height = GetPrivateProfileIntA("EV Nova", "game_height", 0, ".\\ddraw.ini");

    // Fallback to current display metrics
    if (width == 0) {
        // Force width to a multiple of 2 as Nova won't render properly with an odd width
        width = GetSystemMetrics(SM_CXSCREEN) & 0xFFFE;
    }
    if (height == 0) {
        height = GetSystemMetrics(SM_CYSCREEN);
    }

    // Proceed with setup call
    // Fullscreen is forced on as exact behavior will be controlled by cnc ddraw
    nv_SetupScreen(width, height, 15, NV_SCREEN_FULLSCREEN | NV_SCREEN_UNKNOWN_1);

    // Let cnc-ddraw override the fullscreen mode if requested
    PostMessageA(
        g_nv_hwnd, 
        WM_TOGGLE_FULLSCREEN, 
        g_runInAWindow ? CNC_DDRAW_SET_WINDOWED : CNC_DDRAW_SET_FULLSCREEN,
        0);
}

void ToggleFullscren(int unknown) {
    // Switch instantly between windowed/fullscreen without restart
    PostMessageA(
        g_nv_hwnd,
        WM_TOGGLE_FULLSCREEN,
        g_nv_runInAWindowPref ? CNC_DDRAW_SET_WINDOWED : CNC_DDRAW_SET_FULLSCREEN,
        0);

    ((void (*)(int))0x004CFDB0)(unknown);
}
