#include <windows.h>
#include <d3d9.h>
#include "macros/patch.h"
#include "nova.h"

// Replace the original blitters with D3D9-based implementations.

// Nova implements a high-quality downscaler exclusively for 16-bit. It works well but is
// inefficient and results in significant lag on Apple Silicon. We can use D3D9 to achieve
// the same quality with better performance while also covering upscaling and 24-bit.


extern "C" {

    IDirect3D9 *d3d9;
    IDirect3DDevice9 *d3d9Device;
    void initDrawing() {
        if (!d3d9) {
            d3d9 = Direct3DCreate9(D3D_SDK_VERSION);
            D3DPRESENT_PARAMETERS d3dpp;
            ZeroMemory(&d3dpp, sizeof(d3dpp));
            d3dpp.Windowed   = TRUE;
            d3dpp.SwapEffect = D3DSWAPEFFECT_COPY;
            d3d9->CreateDevice(
                D3DADAPTER_DEFAULT,
                D3DDEVTYPE_HAL,
                GetDesktopWindow(),
                D3DCREATE_SOFTWARE_VERTEXPROCESSING,
                &d3dpp,
                &d3d9Device
            );
        }
    }

    D3DFORMAT getD3DFormat(int bitDepth, bool alpha) {
        switch (bitDepth) {
            case 16:
                return D3DFMT_X1R5G5B5;
            case 24:
                return D3DFMT_R8G8B8;
            default:
                return alpha ? D3DFMT_A8R8G8B8 : D3DFMT_X8R8G8B8;
        }
    }

    void copyBitsToSurface(NVBitmap *bitmap, IDirect3DSurface9 *surface) {
        D3DLOCKED_RECT lockedRect;
        surface->LockRect(&lockedRect, NULL, 0);
        BYTE *input = bitmap->raw.buffer;
        BYTE *output = (BYTE*)lockedRect.pBits;
        if (bitmap->raw.depth == 24) {
            for (int i = 0; i < bitmap->raw.height; i++) {
                for (int j = 0; j < bitmap->raw.width; j++) {
                    output[j * 3 + 0] = input[j * 3 + 2];
                    output[j * 3 + 1] = input[j * 3 + 1];
                    output[j * 3 + 2] = input[j * 3 + 0];
                }
                output += lockedRect.Pitch;
                input += bitmap->raw.bytesPerRow;
            }
        } else if (lockedRect.Pitch == bitmap->raw.bytesPerRow) {
            memcpy(output, input, bitmap->raw.bytesPerRow * bitmap->raw.height);
        } else {
            for (int i = 0; i < bitmap->raw.height; i++) {
                memcpy(output, input, bitmap->raw.bytesPerRow);
                output += lockedRect.Pitch;
                input += bitmap->raw.bytesPerRow;
            }
        }
        surface->UnlockRect();
    }

    IDirect3DSurface9* createSurface(NVBitmap *bitmap, bool alpha = false) {
        IDirect3DSurface9 *surface;
        d3d9Device->CreateOffscreenPlainSurface(
            bitmap->raw.width,
            bitmap->raw.height,
            getD3DFormat(bitmap->bitDepth, alpha),
            D3DPOOL_DEFAULT,
            &surface,
            NULL
        );
        copyBitsToSurface(bitmap, surface);
        return surface;
    }

    IDirect3DSurface9* createRenderTarget(NVBitmap *bitmap) {
        IDirect3DSurface9 *surface;
        d3d9Device->CreateRenderTarget(
            bitmap->raw.width,
            bitmap->raw.height,
            getD3DFormat(bitmap->bitDepth, true),
            D3DMULTISAMPLE_NONE,
            0,
            TRUE,
            &surface,
            NULL
        );
        D3DLOCKED_RECT lockedRect;
        surface->LockRect(&lockedRect, NULL, 0);
        memcpy(lockedRect.pBits, bitmap->raw.buffer, bitmap->raw.bytesPerRow * bitmap->raw.height);
        surface->UnlockRect();
        return surface;
    }

    void blit(NVBitmap *source, NVBitmap *dest, QDRect *srcRect, QDRect *destRect, bool alpha = false) {
        auto sSurface = createSurface(source, alpha);
        auto dSurface = createRenderTarget(dest);
        RECT sRect = {
            srcRect->left,
            srcRect->top,
            srcRect->right,
            srcRect->bottom,
        };
        RECT dRect = {
            destRect->left,
            destRect->top,
            destRect->right,
            destRect->bottom,
        };
        d3d9Device->StretchRect(
            sSurface,
            &sRect,
            dSurface,
            &dRect,
            D3DTEXF_LINEAR
        );
        sSurface->Release();
        D3DLOCKED_RECT lockedRect;
        dSurface->LockRect(&lockedRect, NULL, 0);
        memcpy(dest->raw.buffer, lockedRect.pBits, dest->raw.bytesPerRow * dest->raw.height);
        dSurface->UnlockRect();
        dSurface->Release();
    }

    // SETDWORD(0x00575B58, _blit16); // 16 to 16 - existing implementation is fine here
    SETDWORD(0x00575B60, _blit16); // 16 to 32
    SETDWORD(0x00575BBC, _blit16); // 16 to 16 stretch
    SETDWORD(0x00575BC4, _blit16); // 16 to 32 stretch
    void blit16(NVBitmap *source, NVBitmap *dest, QDRect *srcRect, QDRect *destRect) {
        initDrawing();
        blit(source, dest, srcRect, destRect);
    }

    SETDWORD(0x00575B6C, _blit24); // 24 to 16
    SETDWORD(0x00575B74, _blit24); // 24 to 32
    SETDWORD(0x00575BD0, _blit24); // 24 to 16 stretch
    SETDWORD(0x00575BD8, _blit24); // 24 to 32 stretch
    void blit24(NVBitmap *source, NVBitmap *dest, QDRect *srcRect, QDRect *destRect) {
        initDrawing();
        blit(source, dest, srcRect, destRect);
    }

    SETDWORD(0x00575B80, _blit32); // 32 to 16
    SETDWORD(0x00575B88, _blit32); // 32 to 32
    SETDWORD(0x00575BE4, _blit32); // 32 to 16 stretch
    SETDWORD(0x00575BEC, _blit32); // 32 to 32 stretch
    void blit32(NVBitmap *source, NVBitmap *dest, QDRect *srcRect, QDRect *destRect) {
        initDrawing();
        blit(source, dest, srcRect, destRect);
    }

    // Set button construction bitmaps to 32-bit to make masking easier
    SETINST(0x004A3111, "PUSH 32"); // Button parts
    CLEAR_NOP(0x004A3111 + 2, 0x004A3111 + 8);
    SETINST(0x004A312D, "PUSH 32"); // Button masks

    SETDWORD(0x00575D10, _blit32withMask); // 32 to 16
    SETDWORD(0x00575D18, _blit32withMask); // 32 to 32
    SETDWORD(0x00575D74, _blit32withMask); // 32 to 16 stretch
    SETDWORD(0x00575D7C, _blit32withMask); // 32 to 32 stretch
    void blit32withMask(NVBitmap *source, NVBitmap *mask, NVBitmap *dest, QDRect *srcRect, QDRect *maskRect, QDRect *destRect) {
        initDrawing();
        for (int y = 0; y < source->raw.height; y++) {
            for (int x = 0; x < source->raw.width; x++) {
                int sourceIndex = y * source->raw.bytesPerRow + x * 4;
                int maskIndex = y * mask->raw.bytesPerRow + x * 4;
                // Use the first channel of the mask as the alpha channel of the source
                source->raw.buffer[sourceIndex + 3] = ~mask->raw.buffer[maskIndex];
            }
        }
        blit(source, dest, srcRect, destRect, true);
    }

    // Disable brightness adjustment when loading picts.
    // This prevents a forced loss of bits which would preclude dithering of 24-bit sources.
    SETBYTE(0x004B9050 + 1, 0);
};
