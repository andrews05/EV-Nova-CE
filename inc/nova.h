#ifndef NOVA_H 
#define NOVA_H

#include <stdbool.h>

// This header works with sym.asm which defines the Vanilla symbols
// This header will be split up as it becomes larger

// ### Variables ###

void *g_nv_debugLog;
int g_nv_screenWidth;
int g_nv_screenHeight;
HWND g_nv_hwnd;
bool g_nv_runInAWindow;

// ### types ###


// ### Functions ###

#define SWAP16(val) (val >> 8 | val << 8)

int APIENTRY nv_WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow);

void* nv_Alloc(size_t count);
void nv_Free(void *ptr);
int nv_SetupScreen(int width, int height, int depth, int flags);
void nv_WriteLogFormat(void *logFile, char *format, ...);
void nv_FlushLog(void *logFile);
int nv_ConfigureBitmap(void *ptr, int unknown1, int depth, short *bounds);

#endif
