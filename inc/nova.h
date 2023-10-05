#ifndef NOVA_H 
#define NOVA_H

// This header is used for patches
// This header will be split up as it becomes larger



// ### Variables ###


// ### types ###


// ### Functions ###

int APIENTRY nv_WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow);

void* nv_Alloc(size_t count);
void nv_Free(void *ptr);

#endif
