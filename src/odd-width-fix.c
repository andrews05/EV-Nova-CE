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
// (Obsoleted by scale-dlog)
// CALL(0x004CF7C3, _parseDLOG);
// int parseDLOG(short *dialog, unsigned short *DLOGResource) {
//     // Read the bounds rect
//     short top = SWAP16(DLOGResource[0]);
//     short left = SWAP16(DLOGResource[1]);
//     short bottom = SWAP16(DLOGResource[2]);
//     short right = SWAP16(DLOGResource[3]);

//     // Calculate width and height
//     short width = right - left;
//     short height = bottom - top;

//     // Center on screen
//     dialog[6] = (g_nv_screenHeight - height) / 2;
//     dialog[7] = (g_nv_screenWidth - width) / 2;
//     dialog[8] = dialog[6] + height;
//     dialog[9] = dialog[7] + width;

//     // Return the DITL id
//     return (int)SWAP16(DLOGResource[9]);
// }


// Intercept all calls to create context
CALL(0x0046F7A3, _createContextFixed);
CALL(0x00476580, _createContextFixed);
CALL(0x0047900C, _createContextFixed);
CALL(0x004790C2, _createContextFixed);
int createContextFixed(NVContext **context, int depth, QDRect *bounds) {
    // Call the original function
    int result = ((int (*)(NVContext**, int, QDRect*))0x004BB870)(context, depth, bounds);
    // Ensure bytesPerRow is set correctly by querying the bitmap
    BITMAP bitmap;
    GetObject((*context)->bitmap.hbitmap, sizeof(BITMAP), &bitmap);
    (*context)->bitmap.raw.bytesPerRow = bitmap.bmWidthBytes;
    return result;
}
