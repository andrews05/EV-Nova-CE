#ifndef NOVA_H 
#define NOVA_H

#include <stdbool.h>

// This header works with sym.asm which defines the Vanilla symbols
// This header will be split up as it becomes larger

// ### Macros ###

#define SWAP16(val) (val >> 8 | val << 8)
#define ROUND(val) (int)((double)val + 0.5)

// ### Variables ###

extern void *g_nv_debugLog;
extern int g_nv_screenWidth;
extern int g_nv_screenHeight;
extern HWND g_nv_hwnd;
extern bool g_nv_runInAWindow;
extern bool g_nv_runInAWindowPref;

// ### types ###

typedef struct QDRect {
    short top;
    short left;
    short bottom;
    short right;
} QDRect;

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

#endif
