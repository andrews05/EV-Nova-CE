#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Applies a scale factor to dialogs


#define SET_ORIGIN_SCALED(addr, xOffset, yOffset) \
    CALL(addr, _scale_ ## addr); \
    void scale_ ## addr(int x, int y) { \
        g_nv_currentContext->posX = x - xOffset + scale(xOffset); \
        g_nv_currentContext->posY = y - yOffset + scale(yOffset); \
    }


bool g_scaleEnabled = false;
double g_scaleFactor = 0;
int g_gridCellWidth = 83; // Used in scale-grid.asm
int g_gridCellHeight = 54;
int g_statusBarWidth = 194; // Used in scale-status-bar.asm


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
    // Status bar width should be kept to a multiple of 2
    g_statusBarWidth = ROUND(g_statusBarWidth * g_scaleFactor / 2) * 2;
    
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


// Apply the scale factor to the status bar background
CALL(0x004CDF58, _scaleAndShiftRect);

// Scale each status bar item from the intf resource
CALL(0x004CDEBF, _scaleIntfItems);
void scaleIntfItems(int unknown) {
    QDRect *radar = (QDRect *)0x007355DC;
    for (int i=0; i<8; i++) {
        scaleRect(&radar[i]);
    }
    // Original function call replaced by the patch
    ((void (*)(int))0x004D8BA0)(unknown);
}


// Apply the scale factor to font sizes
CALL(0x004BC698, _findFontScaled);
void *findFontScaled(void *name, int size, int style) {
    return nv_FindLoadedFont(name, scale(size), style);
}
CALL(0x004BC6BF, _loadFontScaled);
void *loadFontScaled(void *name, int size, int style) {
    return nv_LoadFont(name, scale(size), style);
}


// Apply the scale factor to text positions
// Rather than apply scaling to every single hardcoded offset, we're going
// to try to determine the bounds box that the text is positioned within.
bool scalePointWithinBounds(short *x, short *y, QDRect *bounds) {
    // If the point is within this item's bounds, apply scaling to the difference
    if (*x >= bounds->left && *x < bounds->right-2 && *y >= bounds->top && *y < bounds->bottom-2) {
        *x = scale(*x - bounds->left) + bounds->left;
        *y = scale(*y - bounds->top) + bounds->top;
        return true;
    }
    return false;
}

// Replace the original setDrawingOrigin
LJMP(0x004BA2F0, _setDrawingOriginScaled);
void setDrawingOriginScaled(short x, short y) {
    if (g_scaleEnabled && g_nv_currentContext == g_nv_mainBufferCanvas.context) {
        if (g_nv_activeDialog != NULL) {
            // Apply scaling within specific dialog items
            int itemNums[3];
            int itemCount = 0;
            if (g_nv_activeDialog == g_nv_commsDialog) {
                // Ship and planet comms share the same dialog var with no easy way to distinguish them
                // Check all relevant items - the wrong one is unlikely to be an issue
                itemNums[0] = 12; // Ship info (not in planet comms)
                itemNums[1] = 6; // Planet info (offscreen button in ship comms)
                itemNums[2] = 10; // Ship response/escort costs (not in planet comms)
                itemCount = 3;
            } else if (g_nv_activeDialog == g_nv_plunderDialog) {
                itemNums[0] = 5; // Main text area
                itemCount = 1;
            } else if (g_nv_activeDialog == g_nv_shipyardDialog || g_nv_activeDialog == g_nv_outfitterDialog) {
                itemNums[0] = 9; // Purchase details
                itemCount = 1;
            } else if (g_nv_activeDialog == g_nv_shipInfoDialog) {
                itemNums[0] = 5; // Ship specs
                itemCount = 1;
            } else if (g_nv_activeDialog == g_nv_playerInfoDialog) {
                itemNums[0] = 6; // Main text area
                itemCount = 1;
            } else if (g_nv_activeDialog == g_nv_mapDialog) {
                itemNums[0] = 2; // Ports/hazards
                itemNums[1] = 6; // System info
                itemCount = 2;
            }

            // Check each item
            for (int i = 0; i < itemCount; i++) {
                QDRect bounds;
                nv_GetDialogItemAndBounds(g_nv_activeDialog, itemNums[i], NULL, NULL, &bounds);
                if (scalePointWithinBounds(&x, &y, &bounds)) {
                    break;
                }
            }
        } else {
            // Apply scaling within status bar items - target and cargo area
            int statusBarOffset = g_nv_mainContext->bitmap.bounds.right - g_statusBarWidth;
            for (int i = 6; i < 8; i++) {
                QDRect bounds = g_nv_statusBarAreas[i];
                nv_ShiftRect(&bounds, statusBarOffset, 0);
                scalePointWithinBounds(&x, &y, &bounds);
            }
        }
    }

    g_nv_currentContext->posX = x;
    g_nv_currentContext->posY = y;
}

// For centered text, scale only the y value
CALL(0x0046232E, _setDrawingOriginScaledY);
void setDrawingOriginScaledY(short x, short y) {
    setDrawingOriginScaled(x, y);
    g_nv_currentContext->posX = x;
}

// Outfitter names
SET_ORIGIN_SCALED(0x0049161f, 0, -6);
SET_ORIGIN_SCALED(0x00491522, 0, -14);
SET_ORIGIN_SCALED(0x004915ba, 0, -3);

// Shipyard names
SET_ORIGIN_SCALED(0x0049511c, 0, -6);
SET_ORIGIN_SCALED(0x0049501d, 0, -14);
SET_ORIGIN_SCALED(0x004950b6, 0, -3);

// Target
SET_ORIGIN_SCALED(0x0046078f, 5, -6);
SET_ORIGIN_SCALED(0x00460a4b, 5, -6);
SET_ORIGIN_SCALED(0x00460a07, -7, -6);
SET_ORIGIN_SCALED(0x00460e3d, -7, -6);


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
