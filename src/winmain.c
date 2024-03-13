#include <windows.h>
#include "macros/patch.h"
#include "nova.h"
#include "imports.h"


// LPSTR *g_argv; // Not currently needed
// int g_argc;
char g_iniPath[MAX_PATH];


CALL(0x00503FE5, _fake_WinMain);

int APIENTRY fake_WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    if (!imports_init())
        return 0;

    // Get args and convert from LPWSTR to LPSTR
    // LPWSTR *argvw = CommandLineToArgvW(GetCommandLineW(), &g_argc);
    // g_argv = malloc(sizeof(LPSTR) * g_argc);
    // for (int i = 0;  i < g_argc;  i++) {
    //     int length = WideCharToMultiByte(CP_UTF8, 0, argvw[i], -1, NULL, 0, NULL, NULL);
    //     g_argv[i] = malloc(length);
    //     WideCharToMultiByte(CP_UTF8, 0, argvw[i], -1, g_argv[i], length, NULL, NULL);
    // }

    // Get full path to ddraw.ini
    GetModuleFileName(NULL, g_iniPath, MAX_PATH);
    char drivePath[10];
    char dirPath[MAX_PATH];
    _splitpath(g_iniPath, drivePath, dirPath, NULL, NULL);
    _makepath(g_iniPath, drivePath, dirPath, "ddraw", "ini");

    return WinMain(hInst, hInstPrev, cmdline, cmdshow);
}
