#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Fixes display of MacRoman characters that are not ANSI compatible


// Clear CALL to libiconv_open
// This is not necessary for the patch but the call is no longer required so we may as well get rid of it
CLEAR(0x004BC43C, 0x90, 0x004BC442);
// Remove iconv.dll dependency
SETDWORD(0x00400000 + 0x18F5BC, 0); // OriginalFirstThunk
SETDWORD(0x00400000 + 0x18FA80, 0); // FirstThunk

// Replace CALL to alloc
CALL(0x004BC783, _alloc_Wide);

// Replace CALL to libiconv
CALL_NOP(0x004BC7C7, _libiconv_Wide);

// Replace CALLs to DrawTextA
CALL_NOP(0x004BC943, _DrawTextAToW);
CALL_NOP(0x004BC964, _DrawTextAToW);


int WINAPI DrawTextAToW(HDC hdc, LPCWSTR lpchText, int cchText, LPRECT lprc, UINT format) {
    return DrawTextW(hdc, lpchText, cchText, lprc, format);
}

// Allocate twice the number of bytes
void* alloc_Wide(size_t count) {
    return nv_Alloc(count * 2);
}

// Convert MacRoman to WideChar instead of CP1252
size_t libiconv_Wide(__attribute__((unused)) void* cd, const char** inbuf, size_t* inbytesleft, char** outbuf, size_t* outbytesleft) {
    return MultiByteToWideChar(CP_MACCP, 0, *inbuf, *inbytesleft, (LPWSTR)*outbuf, *outbytesleft);
}
