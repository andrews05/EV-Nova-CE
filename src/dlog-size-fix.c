#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Fixes dialogs to render with the correct width/height

// Win Nova's code to center the dialog on screen inadvertently truncates the dimensions to a
// multiple of two. Correcting this prevents unnecessary scaling of the background. This is
// especially important for Wine on Apple Silicon, where reducing the width of the background
// causes an unexpected delay.


// Replace CALL to parseDlog
CALL(0x004CF7C3, _parseDlog);
int parseDlog(short *parsedDlog, unsigned short *dlogResource) {
    // Read the bounds rect
    short top = SWAP16(dlogResource[0]);
    short left = SWAP16(dlogResource[1]);
    short bottom = SWAP16(dlogResource[2]);
    short right = SWAP16(dlogResource[3]);

    // Calculate width and height
    short width = right - left;
    short height = bottom - top;

    // Center on screen
    parsedDlog[6] = (g_nv_screenHeight - height) / 2;
    parsedDlog[7] = (g_nv_screenWidth - width) / 2;
    parsedDlog[8] = parsedDlog[6] + height;
    parsedDlog[9] = parsedDlog[7] + width;

    // Return the DITL id
    return (int)SWAP16(dlogResource[9]);
}


// Replace CALL to configureBitmap
CALL(0x004CF83E, _configureBitmap);
int configureBitmap(void *ptr, int unknown1, int depth, QDRect *bounds) {
    QDRect rect = *bounds;
    // Ensure width is a multiple of 2 by incrementing the right edge as necessary
    // This is required to avoid broken text rendering that might occur within odd-width dialogs
    if ((rect.right - rect.left) % 2) {
        rect.right++;
    }
    return nv_ConfigureBitmap(ptr, unknown1, depth, &rect);
}
