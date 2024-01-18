#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Display version in corner of main menu


char version[] = "EV Nova Community Edition r2";

CALL(0x004884BC, _drawBackground);
void drawBackground(NVBitmap *bitmap, QDRect *frame) {
    nv_DrawPict(bitmap, frame);
    g_nv_currentContext->fgColor.red = 0x9999;
    g_nv_currentContext->fgColor.green = 0x9999;
    g_nv_currentContext->fgColor.blue = 0x9999;
    g_nv_currentContext->posX = 5;
    g_nv_currentContext->posY = g_nv_currentContext->bitmap.bounds.bottom - 10;
    g_nv_currentContext->fontSize = 9;
    g_nv_currentContext->fontFace = g_nv_mainFontFace;
    nv_DrawText(version, sizeof(version) - 1, NULL, false, 0);
}
