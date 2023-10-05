#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Fixes display of MacRoman characters that are not ANSI compatible


// Replace CALL to alloc
CALL(0x004BC783, _alloc_Wide);

// Replace CALL to libiconv
CALL_NOP(0x004BC7C7, _libiconv_Wide);

// Replace CALLs to DrawTextA
CALL_NOP(0x004BC943, _DrawTextW);
CALL_NOP(0x004BC964, _DrawTextW);


// Allocate twice the number of bytes
void* alloc_Wide(size_t count) {
    return nv_Alloc(count * 2);
}

// Convert MacRoman to WideChar instead of CP1252
size_t libiconv_Wide(void* cd, const char** inbuf, size_t* inbytesleft, char** outbuf, size_t* outbytesleft) {
    return MultiByteToWideChar(CP_MACCP, 0, *inbuf, *inbytesleft, (LPWSTR)*outbuf, *outbytesleft);
}
