#include <windows.h>
#include "macros/patch.h"
#include "nova.h"
#include "imports.h"


CALL(0x00503FE5, _fake_WinMain);

int APIENTRY fake_WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    if (!imports_init())
        return 0;

    return nv_WinMain(hInst, hInstPrev, cmdline, cmdshow);
}
