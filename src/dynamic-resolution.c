#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Allows dynamic resolution from cnc ddraw.ini or current display metrics


#define NV_SCREEN_FULLSCREEN 0x01 // Nova sets this from prefs
#define NV_SCREEN_UNKNOWN_1  0x02 // Nova always sets this
#define NV_SCREEN_BORDERLESS 0x20 // Nova never sets this
#define NV_SCREEN_ENUMERATE_DD_DEVICES 0x10000 // Exact meaning uncertain; Nova never sets this


// Replace CALL to InitializeMonitor
CALL(0x0041629B, _InitializeMonitor);
void InitializeMonitor() {
    // Get width and height from the ini
    int width = GetPrivateProfileIntA("EV Nova", "game_width", 0, g_iniPath);
    int height = GetPrivateProfileIntA("EV Nova", "game_height", 0, g_iniPath);

    // Fallback to current display metrics
    if (width == 0) {
        width = GetSystemMetrics(SM_CXSCREEN);
    }
    if (height == 0) {
        height = GetSystemMetrics(SM_CYSCREEN);
    }

    // Proceed with setup call
    // Fullscreen is forced on as exact behavior will be controlled by cnc ddraw
    nv_SetupScreen(width, height, 15, NV_SCREEN_FULLSCREEN | NV_SCREEN_UNKNOWN_1);
}
