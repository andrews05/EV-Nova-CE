#ifndef NOVA_H 
#define NOVA_H

// This header works with sym.asm which defines the Vanilla symbols
// This header will be split up as it becomes larger

// ### Variables ###


// ### types ###


// ### Functions ###

int APIENTRY nv_WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow);

void* nv_Alloc(size_t count);
void nv_Free(void *ptr);
int nv_SetupScreen(int width, int height, int depth, int flags);

#endif
