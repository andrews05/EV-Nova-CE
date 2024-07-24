#include <windows.h>
#include "macros/patch.h"
#include "nova.h"
#include "imports.h"
#include "wine.h"

int WinMainCRTStartup(void);

char g_iniPath[MAX_PATH];

CALL(0x00503FE5, _fake_WinMain);

int APIENTRY fake_WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    if (!imports_init()) {
        return 0;
    }

    // Get path to exe
    char exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, sizeof(exePath));

    if (wine_add_dll_overrides()) {
        // Newly added dll overrides only work after a restart
        ShellExecuteA(NULL, "open", exePath, cmdline, NULL, 0);
        return 0;
    }

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

    return WinMain(hInst, hInstPrev, cmdline, cmdshow);
    //return WinMainCRTStartup(); // uncomment for c++
}
