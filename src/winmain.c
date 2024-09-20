#include <windows.h>
#include "macros/patch.h"
#include "wine.h"
#include "nova.h"


char g_iniPath[MAX_PATH];

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    if (wine_add_dll_overrides()) {
        // Newly added dll overrides only work after a restart
        char exePath[MAX_PATH];
        GetModuleFileName(NULL, exePath, sizeof(exePath));
        ShellExecuteA(NULL, "open", exePath, cmdline, NULL, cmdshow);
        return 0;
    }

    // Get path to exe
    char exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, sizeof(exePath));

    // Store the app path in the registry
    HKEY appPath;
    RegCreateKeyExA(
        HKEY_CURRENT_USER,
        "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\EV Nova.exe",
        0,
        NULL,
        REG_OPTION_NON_VOLATILE,
        KEY_WRITE,
        NULL,
        &appPath,
        NULL
    );
    RegSetValueExA(appPath, NULL, 0, REG_SZ, (BYTE *)exePath, sizeof(exePath));

    // Get full path to ddraw.ini
    char drivePath[10];
    char dirPath[MAX_PATH];
    _splitpath(exePath, drivePath, dirPath, NULL, NULL);
    _makepath(g_iniPath, drivePath, dirPath, "ddraw", "ini");

    return OriginalCRTStartup();
}
