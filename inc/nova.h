#ifndef NOVA_H 
#define NOVA_H

#include <stdbool.h>

// This header works with sym.asm which defines the Vanilla symbols
// This header will be split up as it becomes larger

// ### Macros ###

#define SWAP16(val) (val >> 8 | val << 8)
#define SWAP32(val) (val >> 24 | (val & 0xff0000) >> 8 | (val & 0xff00) << 8 | val << 24)
#define ROUND(val) (int)((double)val + (val >= 0 ? 0.5 : -0.5))

// ### types ###

typedef struct QDRect {
    short top;
    short left;
    short bottom;
    short right;
} QDRect;

typedef struct QDColor {
    short red;
    short green;
    short blue;
} QDColor;

typedef struct NVRawBitmap {
    void *buffer;
    void *palette;
    int unknown;
    int width;
    int height;
    int bytesPerRow;
    int depth;
} NVRawBitmap;

typedef struct NVBitmap {
    QDRect bounds;
    int bitDepth;
    NVRawBitmap raw;
} NVBitmap;

typedef struct NVContext {
    int active;
    NVBitmap bitmap;
    HDC hdc;
    HBITMAP hbitmap;
    QDColor fgColor;
    QDColor bgColor;
    short posY;
    short posX;
    short penWidth;
    short penHeight;
    short fontFace;
    short fontStyle;
    short fontSize;
    short unknown;
} NVContext;

typedef struct NVCanvas {
    NVContext *context;
    QDRect bounds;
} NVCanvas;

typedef struct NVDialog {
    NVCanvas canvas;
    QDRect bounds;
    QDRect boundsZeroed;
    // Incomplete...
} NVDialog;

// ### Variables ###

extern void *g_nv_debugLog;
extern void *g_nv_beep1;
extern int g_nv_screenWidth;
extern int g_nv_screenHeight;
extern HWND g_nv_hwnd;
extern bool g_nv_runInAWindow;
extern bool g_nv_runInAWindowPref;
extern bool g_nv_debugMode;
extern short g_nv_currentVolume;
extern QDRect g_nv_statusBarAreas[8];
extern NVDialog *g_nv_activeDialog;
extern NVDialog *g_nv_newsDialog;
extern NVDialog *g_nv_commsDialog;
extern NVDialog *g_nv_plunderDialog;
extern NVDialog *g_nv_outfitterDialog;
extern NVDialog *g_nv_shipyardDialog;
extern NVDialog *g_nv_shipInfoDialog;
extern NVDialog *g_nv_playerInfoDialog;
extern NVDialog *g_nv_mapDialog;
extern NVContext *g_nv_mainContext;
extern NVContext *g_nv_currentContext;
extern NVCanvas g_nv_buttonCanvas;
extern NVCanvas g_nv_mainBufferCanvas;

// ### Functions ###

int APIENTRY nv_WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow);

void *nv_Alloc(size_t count);
void nv_Free(void *ptr);
int nv_SetupScreen(int width, int height, int depth, int flags);
void nv_WriteLogFormat(void *logFile, char *format, ...);
void nv_FlushLog(void *logFile);
int nv_ConfigureBitmap(void *ptr, int unknown1, int depth, QDRect *bounds);
int *nv_ProcessDitlEntry(int itemType, int resourceId, int unknown1, int unknown2,
    QDRect *boundsRect, char *text, int textLength, void *output);
void nv_DrawPict(void *pict, QDRect *frame);
void nv_GetDialogItemAndBounds(void *dialog, int num, int *type, void *item, QDRect *bounds);
QDRect *nv_GetDialogBounds(void *dialog);
void nv_ShiftRect(QDRect *frame, short x, short y);
void *nv_FindLoadedFont(void *name, int size, int style);
void *nv_LoadFont(void *name, int size, int style);
void nv_PlaySound(void *sound, int unknown, short vol1, short vol2);
int nv_KeyCheck(short scanCode);

#endif
