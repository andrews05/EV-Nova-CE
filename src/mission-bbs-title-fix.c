#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Fixes a Wine-specific issue where the mission bbs title rendered poorly
// The title would be drawn black-on-white and then inverted, causing anti-aliasing to get messed up


// Change foreground color to white instead of black
SETDWORD(0x00441744 + 2, 0x00575AD8);
// Replace call to draw block text, which would normally fill with the background color (white) before drawing
CALL(0x0044185B, _drawMCTitle);
void drawMCTitle(char *text, int length, QDRect *rect) {
    g_nv_currentContext->posX = rect->left;
    g_nv_currentContext->posY = rect->top + g_nv_currentContext->fontSize;
    nv_DrawText(text, length, NULL, false, 0);
}
// Clear call to invert region
CLEAR(0x0044186B, 0x90, 0x0044186B + 5);
