#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Applies a scale factor to dialogs


bool g_scaleEnabled = false;
double g_scaleFactor = 0;
int g_gridCellWidth = 83; // Used in scale-grid.asm
int g_gridCellHeight = 54;


// Double the width of the button buffer to avoid clipping
SETDWORD(0x004A329A + 1, 400);

// Get the scale factor from the ini
CALL(0x004D2B9E, _initFontsAndScaleFactor);
void initFontsAndScaleFactor() {
    char buf[8];
    GetPrivateProfileStringA("EV Nova", "ui_scale", "1.0", buf, sizeof buf, ".\\ddraw.ini");
    g_scaleFactor = atof(buf);
    if (g_scaleFactor == 0) {
        g_scaleFactor = 1.0;
    }
    g_scaleEnabled = g_scaleFactor != 1.0;
    g_gridCellWidth = ROUND(g_gridCellWidth * g_scaleFactor);
    g_gridCellHeight = ROUND(g_gridCellHeight * g_scaleFactor);
    
    // Original function call replaced by the patch
    ((void (*)())0x004BC3E0)();
}

// Apply the scale factor to a value
int scale(int val) {
    return ROUND(val * g_scaleFactor);
}

// Apply the scale factor to a rect
void scaleRect(QDRect *rect) {
    if (g_scaleEnabled) {
        rect->top = scale(rect->top);
        rect->left = scale(rect->left);
        rect->bottom = scale(rect->bottom);
        rect->right = scale(rect->right);
    }
}


// Replace CALL to parseDlog
CALL(0x004CF7C3, _parseDlogScaled);
int parseDlogScaled(short *parsedDlog, unsigned short *dlogResource) {
    // Read the bounds rect
    short top = SWAP16(dlogResource[0]);
    short left = SWAP16(dlogResource[1]);
    short bottom = SWAP16(dlogResource[2]);
    short right = SWAP16(dlogResource[3]);

    // Calculate width and height
    short width = scale(right - left);
    short height = scale(bottom - top);

    // Center on screen
    parsedDlog[6] = (g_nv_screenHeight - height) / 2;
    parsedDlog[7] = (g_nv_screenWidth - width) / 2;
    parsedDlog[8] = parsedDlog[6] + height;
    parsedDlog[9] = parsedDlog[7] + width;

    // Return the DITL id
    return (int)SWAP16(dlogResource[9]);
}

// Replace CALL to processDitlEntry
CALL(0x004CF15E, _processDitlEntry);
int *processDitlEntry(int itemType, int resourceId, int unknown1, int unknown2,
    QDRect *bounds, char *text, int textLength, void *output) {
    // Scale the bounds rect then proceed with original call
    scaleRect(bounds);
    return nv_ProcessDitlEntry(itemType, resourceId, unknown1, unknown2, bounds, text, textLength, output);
}


// Apply the scale factor to multipart dialog backgrounds, as these don't normally scale to fit
CALL(0x00447781, _scaleAndShiftRect); // Misson Offer middle
CALL(0x004477F6, _scaleAndShiftRect); // Misson Offer upper
CALL(0x00447879, _scaleAndShiftRect_bottom); // Mission Offer lower
CALL(0x00499956, _scaleAndShiftRect); // Generic middle
CALL(0x004999CB, _scaleAndShiftRect); // Generic upper
CALL(0x00499A4D, _scaleAndShiftRect_bottom); // Generic lower
CALL(0x0049A6D4, _scaleAndShiftRect); // Player Info middle
CALL(0x0049A762, _scaleAndShiftRect); // Player Info upper
CALL(0x0049A801, _scaleAndShiftRect_bottom); // Player Info lower

// Scale a rect before shifting it
void scaleAndShiftRect(QDRect *frame, int x, int y) {
    scaleRect(frame);
    nv_ShiftRect(frame, x, y);
}

// Scale a rect before shifting it, while keeping it bottom-aligned
void scaleAndShiftRect_bottom(QDRect *frame, int x, int y) {
    short bottom = frame->bottom;
    scaleRect(frame);
    y -= frame->bottom - bottom;
    nv_ShiftRect(frame, x, y);
}


// Apply the scale factor to font sizes
int scaleFontSize(int size) {
    if (!g_scaleEnabled) {
        return size;
    }
    int newSize = scale(size);
    // Until Status Bar scaling can be implemented, we need to limit some sizes
    if ((size == 10 || size == 12) && newSize > size + 2) {
        newSize = size + 2;
    }
    return newSize;
}

CALL(0x004BC698, _findFontScaled);
void *findFontScaled(void *name, int size, int style) {
    return nv_FindLoadedFont(name, scaleFontSize(size), style);
}
CALL(0x004BC6BF, _loadFontScaled);
void *loadFontScaled(void *name, int size, int style) {
    return nv_LoadFont(name, scaleFontSize(size), style);
}


// Apply the scale factor to text positions
// Start by re-implementing setDrawingOrigin
void setDrawingOrigin(short x, short y) {
    if (g_nv_currentContext != NULL) {
        g_nv_currentContext->posX = x;
        g_nv_currentContext->posY = y;
    }
}

// Replace the original setDrawingOrigin
LJMP(0x004BA2F0, _setDrawingOriginScaled);
void setDrawingOriginScaled(short x, short y) {
    if (g_scaleEnabled && g_nv_activeDialog != NULL && g_nv_currentContext != g_nv_buttonCanvas.context) {
        int itemNum = 0;
        if (g_nv_activeDialog == g_nv_playerInfoDialog) {
            itemNum = 6;
        }
        if (itemNum != 0) {
            QDRect bounds;
            nv_GetDialogItemAndBounds(g_nv_activeDialog, itemNum, NULL, NULL, &bounds);
            x = scale(x - bounds.left) + bounds.left;
            y = scale(y - bounds.top) + bounds.top;
        }
    }
    setDrawingOrigin(x, y);
}

// Don't apply scaling for centered text
CALL(0x0046232E, _setDrawingOrigin);


// Create a scaled rect, scaling only the difference from a given offset rect
void createBoundsRectScaled(QDRect *bounds, short left, short top, short right, short bottom, QDRect *offset) {
    bounds->top = scale(top - offset->top) + offset->top;
    bounds->left = scale(left - offset->left) + offset->left;
    bounds->bottom = scale(bottom - offset->bottom) + offset->bottom;
    bounds->right = scale(right - offset->right) + offset->right;
}

// Scale news text rects
CALL(0x0047D42B, _createNewsRect1);
void createNewsRect1(QDRect *bounds, short left, short top, short right, short bottom) {
    QDRect offset = g_nv_newsDialog->boundsZeroed;
    offset.bottom = offset.top;
    createBoundsRectScaled(bounds, left, top, right, bottom, &offset);
}
CALL(0x0047D4B4, _createNewsRect2);
void createNewsRect2(QDRect *bounds, short left, short top, short right, short bottom) {
    createBoundsRectScaled(bounds, left, top, right, bottom, &g_nv_newsDialog->boundsZeroed);
}
