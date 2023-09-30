#include <windows.h>
#include "macros/patch.h"
#include "nova.h"
#include "imports.h"


CALL(0x00503FE5, _fake_WinMain);

int APIENTRY fake_WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
    imports_init();	

    return nv_WinMain(hInst, hInstPrev, cmdline, cmdshow);
}
