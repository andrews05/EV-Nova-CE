#ifndef NOVA_H
#define NOVA_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

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
    BYTE *buffer;
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

typedef struct NVScrollList {
    NVDialog *dialog;
    QDRect rect1;
    QDRect rect2;
    int unknown;
    short height;
    short width;
    // Incomplete...
} NVScrollList;

// ### Variables ###

extern char g_iniPath[MAX_PATH];

extern int g_nv_argc;
extern LPSTR *g_nv_argv;
extern void *g_nv_debugLog;
extern void *g_nv_beep1;
extern int g_nv_screenWidth;
extern int g_nv_screenHeight;
extern HWND g_nv_hwnd;
extern bool g_nv_runInAWindow;
extern bool g_nv_runInAWindowPref;
extern bool g_nv_noHyperspaceEffects;
extern bool g_nv_debugMode;
extern short g_nv_currentVolume;
extern short g_nv_mainFontFace;
extern char g_nv_promptResult[256];
extern QDRect g_nv_statusBarAreas[8];
extern QDRect g_nv_gridThumbBounds[0x80];
extern QDRect g_nv_gridCellBounds[20];
extern QDRect g_nv_gridCellImageBounds[20];
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
extern HCURSOR g_nv_cursor;

// ### Functions ###

int OriginalCRTStartup(void);

void *nv_Alloc(size_t count);
void nv_Free(void *ptr);
int nv_SetupScreen(int width, int height, int depth, int flags);
void nv_WriteLogFormat(void *logFile, char *format, ...);
void nv_FlushLog(void *logFile);
int *nv_ProcessDitlEntry(int itemType, int resourceId, int unknown1, int unknown2,
    QDRect *boundsRect, char *text, int textLength, void *output);
void nv_DrawPict(void *pict, QDRect *frame);
void nv_DrawPStringCentered(char *pString, short left, short right, short top);
void nv_DrawText(char *text, int length, QDRect *frame, bool block, short lineHeight);
void nv_GetDialogItemAndBounds(void *dialog, int num, int *type, void *item, QDRect *bounds);
QDRect *nv_GetDialogBounds(void *dialog);
void nv_ShiftRect(QDRect *frame, short x, short y);
void nv_SetFontSize(short size);
void nv_PlaySound(void *sound, int unknown, short vol1, short vol2);
int nv_KeyCheck(short scanCode);
void nv_ShowAlert(char *message);
bool nv_ShowPrompt(char *message, char *defaultValue, short selectionRange);
void nv_ExecuteNCBSetExpression(char *expression);
bool nv_EvaluteNCBTestExpression(char *expression);
void nv_ConvertMacPathToWin(char *winPath, char *macPath);
int nv_LoadFilesInFolder(char *folderPath, char *extension, bool log);
LRESULT CALLBACK nv_Wndproc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#ifdef __cplusplus
};
#endif

#endif
