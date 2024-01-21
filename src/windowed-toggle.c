#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

__declspec(dllimport) BOOL DDIsWindowed();

// Change the windowed checkbox to defer to cnc ddraw


// cnc-ddraw specific settings
#define WM_TOGGLE_FULLSCREEN WM_APP+117

#define CNC_DDRAW_SET_FULLSCREEN 1
#define CNC_DDRAW_SET_WINDOWED 2


// Replace original runInAWindow bool with ours to make sure the game doesn't change its behavior
bool g_runInAWindow;

// Skip reading the original windowed pref so the game always thinks it's in fullscreen
CLEAR(0x004C754A, 0x90, 0x004C7550);

// Determine windowed state from cnc ddraw
CALL(0x004888E3, _ReadWindowedState);
void ReadWindowedState(int itemNum, bool state) {
    g_runInAWindow = DDIsWindowed();

    // Original function call replaced by the patch
    ((void (*)(int, bool))0x004CFD40)(itemNum, g_runInAWindow);
}

// Change prefs toggle to work with our bool
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
