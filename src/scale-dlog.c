#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Applies a scale factor to dialogs


double g_scaleFactor = 0;
int g_gridCellWidth = 83;
int g_gridCellHeight = 54;

// Get the scale factor from the ini
void initScaleFactor() {
    char buf[8];
    GetPrivateProfileStringA("EV Nova", "ui_scale", "1.0", buf, sizeof buf, ".\\ddraw.ini");
    g_scaleFactor = atof(buf);
    g_gridCellWidth = ROUND(g_gridCellWidth * g_scaleFactor);
    g_gridCellHeight = ROUND(g_gridCellHeight * g_scaleFactor);
}

// Apply the scale factor to a value
int scale(int val) {
    if (g_scaleFactor == 0) {
        initScaleFactor();
    }
    return ROUND(val * g_scaleFactor);
}

// Apply the scale factor to a rect
void scaleRect(QDRect *rect) {
    rect->top = scale(rect->top);
    rect->left = scale(rect->left);
    rect->bottom = scale(rect->bottom);
    rect->right = scale(rect->right);
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
