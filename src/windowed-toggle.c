#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Change the windowed checkbox to defer to cnc ddraw


// cnc-ddraw specific settings
#define WM_TOGGLE_FULLSCREEN WM_APP+117

#define CNC_DDRAW_SET_FULLSCREEN 1
#define CNC_DDRAW_SET_WINDOWED 2


// Replace original runInAWindow bool with ours to make sure the game doesn't change its behavior
bool g_runInAWindow;

// Determine windowed state from ddraw ini
CALL(0x004161ED, _ReadPrefs);
void ReadPrefs() {
    // Setup g_runInAWindow bool
    char buf[8];
    GetPrivateProfileStringA("ddraw", "fullscreen", "false", buf, sizeof buf, ".\\ddraw.ini");
    BOOL upscaled = _strcmpi(buf, "yes") == 0 || _strcmpi(buf, "true") == 0 || _strcmpi(buf, "1") == 0;

    GetPrivateProfileStringA("ddraw", "windowed", "false", buf, sizeof buf, ".\\ddraw.ini");
    BOOL windowed = _strcmpi(buf, "yes") == 0 || _strcmpi(buf, "true") == 0 || _strcmpi(buf, "1") == 0;

    g_runInAWindow = windowed && !upscaled;
    
    // Original function call replaced by the patch
    ((void (*)())0x004C7400)();
}

// Change prefs dialog to work with our bool
SETDWORD(0x004888CA + 2, _g_runInAWindow);
SETDWORD(0x00488FD1 + 2, _g_runInAWindow);
SETDWORD(0x00488FDB + 1, _g_runInAWindow);

// Switch between windowed and fullscreen mode without restart
CALL(0x00488FE6, _ToggleFullscreen);
void ToggleFullscreen(int unknown) {
    PostMessageA(
        g_nv_hwnd,
        WM_TOGGLE_FULLSCREEN,
        g_runInAWindow ? CNC_DDRAW_SET_WINDOWED : CNC_DDRAW_SET_FULLSCREEN,
        0);

    // Original function call replaced by the patch
    ((void (*)(int))0x004CFDB0)(unknown);
}
