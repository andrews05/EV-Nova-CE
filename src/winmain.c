#include <windows.h>
#include "macros/patch.h"
#include "wine.h"
#include "nova.h"


char g_iniPath[MAX_PATH];

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    // Get path to exe
    char exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, sizeof(exePath));

    if (wine_add_dll_overrides()) {
        // Newly added dll overrides only work after a restart
        ShellExecuteA(NULL, "open", exePath, cmdline, NULL, cmdshow);
        return 0;
    }

    // Get full path to ddraw.ini
    char drivePath[10];
    char dirPath[MAX_PATH];
    _splitpath(exePath, drivePath, dirPath, NULL, NULL);
    _makepath(g_iniPath, drivePath, dirPath, "ddraw", "ini");

    return OriginalCRTStartup();
}
