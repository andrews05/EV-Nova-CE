#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Allows dynamic resolution from cnc ddraw.ini or current display metrics


#define FLAGS_FULLSCREEN 0x01 // Nova sets this from prefs
#define FLAGS_UNKNOWN_1  0x02 // Nova always sets this
#define FLAGS_BORDERLESS 0x20 // Nova never sets this
#define FLAGS_ENUMERATE_DD_DEVICES 0x10000 // Exact meaning uncertain; Nova never sets this


// Replace CALL to InitializeMonitor
CALL(0x0041629B, _InitializeMonitor);

void InitializeMonitor() {
    // Get the full path to ddraw.ini in the current directy
    LPSTR ddrawIni = GlobalAlloc(0, 4096);
    GetFullPathNameA("ddraw.ini", 4096, ddrawIni, NULL);

    // Get width and height from the ini
    int width = GetPrivateProfileIntA("ddraw", "width", 0, ddrawIni);
    int height = GetPrivateProfileIntA("ddraw", "height", 0, ddrawIni);

    // Fallback to current display metrics
    if (width == 0) {
        width = GetSystemMetrics(SM_CXSCREEN);
    }
    if (height == 0) {
        height = GetSystemMetrics(SM_CYSCREEN);
    }

    // Proceed with setup call
    // Fullscreen is forced on as exact behavior will be controlled by cnc ddraw
    nv_SetupScreen(width, height, 15, FLAGS_FULLSCREEN | FLAGS_UNKNOWN_1);
}
