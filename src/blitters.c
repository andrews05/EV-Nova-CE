#include <windows.h>
#include "macros/patch.h"
#include "nova.h"


void stretchBlit(HDC sContext, NVBitmap *dest, QDRect *srcRect, QDRect *destRect) {
    HGDIOBJ destPrev = SelectObject(dest->hdc, dest->hbitmap);
    SetStretchBltMode(dest->hdc, HALFTONE);
    StretchBlt(
        dest->hdc,
        destRect->left,
        destRect->top,
        destRect->right - destRect->left,
        destRect->bottom - destRect->top,
        sContext,
        srcRect->left,
        srcRect->top,
        srcRect->right - srcRect->left,
        srcRect->bottom - srcRect->top,
        SRCCOPY
    );
    SelectObject(dest->hdc, destPrev);
}

SETDWORD(0x00575BBC, _stretchBlit16to16);
void stretchBlit16to16(NVBitmap *source, NVBitmap *dest, QDRect *srcRect, QDRect *destRect, int xScale, int yScale, int halfXScale, int halfYScale) {

    // If we're downscaling an image 200x200 or smaller, use the original high-quality blitter
    if ((srcRect->right - srcRect->left) <= 200 && (srcRect->bottom - srcRect->top) <= 200 && xScale > 0x10000) {
        ((void (*)(NVBitmap *, NVBitmap *, QDRect *, QDRect *, int, int, int, int))0x004B7CB0)(source, dest, srcRect, destRect, xScale, yScale, halfXScale, halfYScale);
        return;
    }

    HGDIOBJ sourcePrev = SelectObject(source->hdc, source->hbitmap);
    if (sourcePrev) {
        // If the source has a valid hbitmap, use it directly
        stretchBlit(source->hdc, dest, srcRect, destRect);
        SelectObject(source->hdc, sourcePrev);
        return;
    }

    // Construct a temporary bitmap from the raw data
    HDC hContext = CreateCompatibleDC(dest->hdc);
    BITMAPINFO bi = {
        bmiHeader: {
            biSize: sizeof(BITMAPINFOHEADER),
            biWidth: source->raw.width,
            biHeight: -source->raw.height,
            biPlanes: 1,
            biBitCount: source->bitDepth,
            biCompression: BI_RGB,
            biSizeImage: 0,
        },
    };
    void *buffer;
    HBITMAP hBitmap = CreateDIBSection(hContext, &bi, DIB_RGB_COLORS, &buffer, NULL, 0);

    // Copy the raw data into the temporary bitmap (line by line in case byte length differs)
    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);
    void *input = source->raw.buffer;
    for (int i = 0; i < source->raw.height; i++) {
        memcpy(buffer, input, source->raw.bytesPerRow);
        buffer += bitmap.bmWidthBytes;
        input += source->raw.bytesPerRow;
    }

    // Perform the stretch blit, then cleanup
    SelectObject(hContext, hBitmap);
    stretchBlit(hContext, dest, srcRect, destRect);
    DeleteDC(hContext);
    DeleteObject(hBitmap);
}
