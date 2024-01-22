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
#define DRAW_PSTRING_CENTERED_SCALED(addr, yOffset) \
    CALL(addr, _scale_ ## addr); \
    void scale_ ## addr(char *pString, short left, short right, short top) { \
        nv_DrawPStringCentered(pString, left, right, top - yOffset + scale(yOffset)); \
    }


bool g_scaleEnabled = false;
double g_scaleFactor = 0;
int g_gridCellWidth = 83; // Used in scale-grid.asm
int g_gridCellHeight = 54;
int g_gridThumbSize = 32;
int g_statusBarWidth = 194; // Used in scale-status-bar.asm
int g_listItemBaseHeight = 8; // Originally 9 (main font size) but changed to 8 to match sizing in Mac Nova which works better


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
    g_gridThumbSize = ROUND(g_gridThumbSize * g_scaleFactor);
    // Status bar width should be kept to a multiple of 2
    g_statusBarWidth = ROUND(g_statusBarWidth * g_scaleFactor / 2) * 2;
    g_listItemBaseHeight = ROUND(g_listItemBaseHeight * g_scaleFactor);
    
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

// Apply the scale factor to font sizes
LJMP(0x004B6920, _setFontSizeScaled);
void setFontSizeScaled(short size) {
    g_nv_currentContext->fontSize = scale(size);
}


/** DIALOGS **/

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


/** BUTTONS **/

// Increase the size of the button buffer to avoid clipping
SETBYTE(0x004A3298 + 1, 75);
SETDWORD(0x004A329A + 1, 500);

// Scale the button ends
CALL(0x004A34FA, _compositeButtonLeft);
void compositeButtonLeft(NVBitmap *source, NVBitmap *mask, NVBitmap *dest, QDRect *sourceFrame, QDRect *maskFrame, QDRect *destFrame) {
    destFrame->right = destFrame->left + scale(destFrame->right - destFrame->left);
    ((void (*)(NVBitmap*,NVBitmap*,NVBitmap*,QDRect*,QDRect*,QDRect*))0x004B9410)(source, mask, dest, sourceFrame, maskFrame, destFrame);
}
CALL(0x004A35B9, _compositeButtonRight);
void compositeButtonRight(NVBitmap *source, NVBitmap *mask, NVBitmap *dest, QDRect *sourceFrame, QDRect *maskFrame, QDRect *destFrame) {
    destFrame->left = destFrame->right - scale(destFrame->right - destFrame->left);
    ((void (*)(NVBitmap*,NVBitmap*,NVBitmap*,QDRect*,QDRect*,QDRect*))0x004B9410)(source, mask, dest, sourceFrame, maskFrame, destFrame);
}

// Button text position
SET_ORIGIN_SCALED(0x004a3732, 0, 5);


/** TEXT POSITIONS **/

// Rather than apply scaling to every single hardcoded offset, we're going
// to try to determine the bounds box that the text is positioned within.
// This is an easy way to cover dialog areas that contain many text elements.
// However, it only works relative to top-left and the dialog must be topmost.
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

// Override the above for centered text
CALL(0x0046232E, _setDrawingOrigin);
void setDrawingOrigin(short x, short y) {
    g_nv_currentContext->posX = x;
    g_nv_currentContext->posY = y;
}

// Spaceport title
DRAW_PSTRING_CENTERED_SCALED(0x00492d10, 18);

// Outfitter grid text
SET_ORIGIN_SCALED(0x0049175a, -3, 12);
SET_ORIGIN_SCALED(0x0049161f, 0, -6);
SET_ORIGIN_SCALED(0x00491522, 0, -14);
SET_ORIGIN_SCALED(0x004915ba, 0, -3);

// Shipyard grid text
SET_ORIGIN_SCALED(0x0049511c, 0, -6);
SET_ORIGIN_SCALED(0x0049501d, 0, -14);
SET_ORIGIN_SCALED(0x004950b6, 0, -3);

// Shipyard info title
DRAW_PSTRING_CENTERED_SCALED(0x00495df9, 18);

// Trade Center
SET_ORIGIN_SCALED(0x0048d792, 7, 12);
SET_ORIGIN_SCALED(0x0048d7c8, -123, 12);
SET_ORIGIN_SCALED(0x0048d816, -70, 12);
SET_ORIGIN_SCALED(0x0048e17e, 7, 10);
SET_ORIGIN_SCALED(0x0048e1e9, -110, 10);
SET_ORIGIN_SCALED(0x0048de8f, 6, 10);
SET_ORIGIN_SCALED(0x0048df1f, -110, 10);
SET_ORIGIN_SCALED(0x0048df52, -70, 10);
SET_ORIGIN_SCALED(0x0048e0a4, -10, 10);

// Map date
SET_ORIGIN_SCALED(0x004a6382, -5, 36);

// Player info
DRAW_PSTRING_CENTERED_SCALED(0x0049bf9e, 55);

// Mission Computer
SET_ORIGIN_SCALED(0x004416bf, 0, 12);

// Mission Info
SET_ORIGIN_SCALED(0x004470fd, 0, 9);

// Mission list
SETDWORD(0x0043ccae + 3, _g_listItemBaseHeight);
SETDWORD(0x00445ec8 + 3, _g_listItemBaseHeight);
SET_ORIGIN_SCALED(0x00448ac3, 4, 9);
SET_ORIGIN_SCALED(0x00448b4f, 4, 9);


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


/** GRID CELLS **/

// Scale grid cells and thumbnails
LJMP(0x00499150, _constructGridCells);
void constructGridCells(QDRect *bounds) {
    for (int i = 0; i < 20; i++) {
        int x = i % 4;
        int y = i / 4;
        QDRect *cell = g_nv_gridCellBounds + i;
        cell->left = x * g_gridCellWidth + bounds->left;
        cell->top = y * g_gridCellHeight + bounds->top;
        cell->right = cell->left + g_gridCellWidth + 1;
        cell->bottom = cell->top + g_gridCellHeight + 1;
        QDRect *thumb = g_nv_gridCellImageBounds + i;
        thumb->left = (cell->left + cell->right - g_gridThumbSize) / 2;
        thumb->bottom = (cell->top + cell->bottom + g_gridThumbSize / 2) / 2;
        thumb->right = thumb->left + g_gridThumbSize;
        thumb->top = thumb->bottom - g_gridThumbSize;
    }
    for (int i = 0; i < 0x80; i++) {
        QDRect *thumb = g_nv_gridThumbBounds + i;
        thumb->left = g_gridThumbSize * i;
        thumb->top = 0;
        thumb->right = thumb->left + g_gridThumbSize;
        thumb->bottom = g_gridThumbSize;
    }
}

CALL(0x0049EE94, _createThumbsBufferRect);
void createThumbsBufferRect(QDRect *rect, short left, short top, short right, short bottom) {
    rect->left = 0;
    rect->top = 0;
    rect->right = g_gridThumbSize * 0x80;
    rect->bottom = g_gridThumbSize;
}


/** STATUS BAR **/

// Apply the scale factor to the status bar background
CALL(0x004CDF58, _scaleAndShiftRect);

// Scale each status bar item from the intf resource
CALL(0x004CDEBF, _scaleIntfItems);
void scaleIntfItems(int unknown) {
    for (int i=0; i<8; i++) {
        scaleRect(&g_nv_statusBarAreas[i]);
    }
    // Original function call replaced by the patch
    ((void (*)(int))0x004D8BA0)(unknown);
}

// Scale target image
CALL(0x004601D5, _createTargetImageBoundsRect);
void createTargetImageBoundsRect(QDRect *bounds, short left, short top, short right, short bottom) {
    bounds->left = left + 64 - scale(64);
    bounds->top = top + 32 - scale(32);
    bounds->right = right - 64 + scale(64);
    bounds->bottom = bottom - 32 + scale(32);
}

// Nav system
DRAW_PSTRING_CENTERED_SCALED(0x0045e679, 22);
DRAW_PSTRING_CENTERED_SCALED(0x0045e6cf, 12);
DRAW_PSTRING_CENTERED_SCALED(0x0045e781, 29);
DRAW_PSTRING_CENTERED_SCALED(0x0045e72b, 29);
DRAW_PSTRING_CENTERED_SCALED(0x0045e5b9, 12);
DRAW_PSTRING_CENTERED_SCALED(0x0045e94f, 29);

// Secondary weapon
DRAW_PSTRING_CENTERED_SCALED(0x0046104e, 12);
DRAW_PSTRING_CENTERED_SCALED(0x0046114b, 12);
DRAW_PSTRING_CENTERED_SCALED(0x004610e1, 12);
DRAW_PSTRING_CENTERED_SCALED(0x0046124d, 12);

// Target
DRAW_PSTRING_CENTERED_SCALED(0x00460422, 47);
DRAW_PSTRING_CENTERED_SCALED(0x0046052c, 16);
DRAW_PSTRING_CENTERED_SCALED(0x0046057c, 16);
DRAW_PSTRING_CENTERED_SCALED(0x00460178, 16);
DRAW_PSTRING_CENTERED_SCALED(0x004602c7, 29);
DRAW_PSTRING_CENTERED_SCALED(0x00460695, -6);
DRAW_PSTRING_CENTERED_SCALED(0x004603c9, -6);
DRAW_PSTRING_CENTERED_SCALED(0x00460764, -6);
SET_ORIGIN_SCALED(0x0046078f, 5, -6);
SET_ORIGIN_SCALED(0x00460a4b, 5, -6);
SET_ORIGIN_SCALED(0x00460a07, -7, -6);
SET_ORIGIN_SCALED(0x00460e3d, -7, -6);

// Cargo
SET_ORIGIN_SCALED(0x00461432, 77, 12);
SET_ORIGIN_SCALED(0x00461471, 110, 12);
SET_ORIGIN_SCALED(0x004616fe, 77, 30);
SET_ORIGIN_SCALED(0x0046173d, 87, 46);
SET_ORIGIN_SCALED(0x0046156e, 77, 66);
SET_ORIGIN_SCALED(0x004615d1, 87, 82);

// Status message
// Nova used a weird calculation for the height to allow for wrapping at narrower resolutions. This could
// cause clipping at very wide resolutions though, so instead we use a fixed height with room for two lines.
CALL(0x004B002A, _createStatusMessageRect);
void createStatusMessageRect(QDRect *rect, short left, short top, short right, short bottom) {
    QDRect bounds = g_nv_mainContext->bitmap.bounds;
    rect->left = bounds.left + 25;
    rect->right = bounds.right - g_statusBarWidth - 50;
    rect->bottom = bounds.bottom - 5;
    rect->top = rect->bottom - scale(26) - 4;
}
// Clear the weird calculation
CLEAR(0x004B0051, 0x90, 0x004B0051 + 7);


/** ESCORT MENU **/

// Scale the escort menu
CALL(0x004ABDB0, _createEscortMenuRect);
void createEscortMenuRect(QDRect *rect, short left, short top, short right, short bottom) {
    rect->left = scale(left);
    rect->top = scale(top);
    rect->right = scale(right);
    rect->bottom = scale(bottom);
}
CALL(0x0049E7F2, _highlightEscortMenuItem);
void highlightEscortMenuItem(QDRect *rect) {
    rect->top = scale(rect->top);
    rect->bottom = scale(rect->bottom);
    ((void (*)(QDRect*))0x004B6B90)(rect);
}
CALL(0x0049E54E, _setEscortMenuTextOrigin);
CALL(0x0049E636, _setEscortMenuTextOrigin);
CALL(0x0049E759, _setEscortMenuTextOrigin);
void setEscortMenuTextOrigin(int x, int y) {
    g_nv_currentContext->posX = x;
    g_nv_currentContext->posY = scale(y);
}
