#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Fixes dialogs with odd dimensions to render at their given size
// Also fixes text rendering with odd width resolutions

// Win Nova's code to center the dialog on screen inadvertently truncates the dimensions to a
// multiple of two. Correcting this prevents unnecessary scaling of the background. This is
// especially important for Wine on Apple Silicon, where reducing the width of the background
// causes an unexpected delay.


// Fix dialog placement
CALL(0x004CF7C3, _parseDLOG);
int parseDLOG(short *dialog, unsigned short *DLOGResource) {
    // Read the bounds rect
    short top = SWAP16(DLOGResource[0]);
    short left = SWAP16(DLOGResource[1]);
    short bottom = SWAP16(DLOGResource[2]);
    short right = SWAP16(DLOGResource[3]);

    // Calculate width and height
    short width = right - left;
    short height = bottom - top;

    // Center on screen
    dialog[6] = (g_nv_screenHeight - height) / 2;
    dialog[7] = (g_nv_screenWidth - width) / 2;
    dialog[8] = dialog[6] + height;
    dialog[9] = dialog[7] + width;

    // Return the DITL id
    return (int)SWAP16(DLOGResource[9]);
}


// Fix text rendering in odd-width dialogs
CALL(0x004CF83E, _configureBitmap_evenPadded);
int configureBitmap_evenPadded(void *ptr, int unknown1, int depth, QDRect *bounds) {
    QDRect newBounds = *bounds;
    // Ensure width is a multiple of 2 by incrementing the right edge as necessary
    // Nothing is drawn to the extra column so there are no side effects
    if ((newBounds.right - newBounds.left) % 2) {
        newBounds.right++;
    }
    return nv_ConfigureBitmap(ptr, unknown1, depth, &newBounds);
}


// Fix text rendering in odd-width resolutions
CALL(0x004162A0, _configureGameBounds_evenTruncated);
void configureGameBounds_evenTruncated() {
    QDRect *bounds = (QDRect *)0x0085F67E;
    bounds->top = 0;
    bounds->left = 0;
    bounds->bottom = g_nv_screenHeight;
    // Ensure width is a multiple of 2 by truncating the right edge
    // This results in the game rendering at an even width, with an extra blank column on the right
    bounds->right = g_nv_screenWidth & 0xFFFE;
}
