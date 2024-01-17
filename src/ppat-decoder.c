#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Rewrite the ppat decoder (used for radar interference)
// This both avoids errors in the existing decoder and adds support for lower bit depths


short read16(void *data) {
    return SWAP16(*(short*)data);
}
int read32(void *data) {
    return SWAP32(*(int*)data);
}

LJMP(0x004FDF40, _decodePpat);
int decodePpat(NVRawBitmap *bitmap, void *ppat) {
    memset(bitmap, 0, 0x1C);

    // Read the header
    short type = read16(ppat); 
    short mapOffset = read32(ppat + 2);
    short dataOffset = read32(ppat + 6);

    // Validate the header
    if (type == 1 && mapOffset > 0 && dataOffset > 0) {
        // Read the pixmap
        void *map = ppat + mapOffset;

        unsigned short rowBytes = (unsigned short)read16(map + 4);
        QDRect bounds = {
            top: read16(map + 6),
            left: read16(map + 8),
            bottom: read16(map + 10),
            right: read16(map + 12),
        };
        bitmap->width = bounds.right - bounds.left;
        bitmap->height = bounds.bottom - bounds.top;
        short version = read16(map + 14);
        short packType = read16(map + 16);
        short depth = read16(map + 32);
        int colorTableOffset = read32(map + 42);

        // Validate the pixmap
        if ((rowBytes & 0xC000) == 0x8000 &&
            bitmap->width > 0 &&
            bitmap->height > 0 &&
            version == 0 &&
            packType == 0 &&
            (depth == 1 || depth == 2 || depth == 4 || depth == 8) &&
            colorTableOffset > 0) {
            // Read the pixel data - lower depths must be expanded to 8
            unsigned char *data = ppat + dataOffset;
            unsigned char *buffer = nv_Alloc(bitmap->width * bitmap->height);
            bitmap->buffer = buffer;
            bitmap->bytesPerRow = bitmap->width;
            bitmap->depth = 8;

            rowBytes &= 0x3FFF;
            int mod = 8 / depth;
            int mask = (1 << depth) - 1;
            int diff = 8 - depth;
            for (int y = 0; y < bitmap->height; y++) {
                int yOffset = y * rowBytes;
                for (int x = 0; x < bitmap->width; x++) {
                    unsigned char byte = data[yOffset + (x / mod)];
                    int byteShift = diff - ((x % mod) * depth);
                    *buffer++ = (byte >> byteShift) & mask;
                }
            }

            // Read the color table
            unsigned char *colorTable = ppat + colorTableOffset;
            void *palette = nv_Alloc(0x300);
            memset(palette, 0, 0x300);
            bitmap->palette = palette;
            
            short count = read16(colorTable + 6);
            colorTable += 8;
            for (int i = 0; i < count; i++) {
                short index = read16(colorTable);
                if (index < 0x100) {
                    unsigned char *rgb = palette + (index * 3);
                    rgb[0] = colorTable[3];
                    rgb[1] = colorTable[5];
                    rgb[2] = colorTable[7];
                }
                colorTable += 8;
            }

            // Decode successful - return 0
            return 0;
        }
    }

    // Decode failed - deallocate the bitmap and return 1
    ((void (*)(void*))0x004FDB90)(bitmap);
    return 1;
}
