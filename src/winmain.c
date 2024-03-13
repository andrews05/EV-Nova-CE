#include <windows.h>
#include "macros/patch.h"
#include "nova.h"
#include "imports.h"


char g_iniPath[MAX_PATH];

CALL(0x00503FE5, _fake_WinMain);

int APIENTRY fake_WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    if (!imports_init())
        return 0;

    // Get full path to ddraw.ini
    GetModuleFileName(NULL, g_iniPath, MAX_PATH);
    char drivePath[10];
    char dirPath[MAX_PATH];
    _splitpath(g_iniPath, drivePath, dirPath, NULL, NULL);
    _makepath(g_iniPath, drivePath, dirPath, "ddraw", "ini");

    return WinMain(hInst, hInstPrev, cmdline, cmdshow);
}
