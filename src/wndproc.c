#include <windows.h>
#include "macros/patch.h"
#include "nova.h"


SETDWORD(0x004D2973 + 4, _Wndproc);
LRESULT CALLBACK Wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_SETCURSOR:
    {
        // Make sure we restore the original cursor after window resize in main menu (Fixes random hourclass cursor as well)
        if (LOWORD(lParam) == HTCLIENT)
        {
            SetCursor(g_nv_cursor ? g_nv_cursor : LoadCursor(NULL, IDC_ARROW));
        }

        break;
    }
    }

    return nv_Wndproc(hwnd, uMsg, wParam, lParam);
}
