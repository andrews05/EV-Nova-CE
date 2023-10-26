#ifndef IMPORTS_H 
#define IMPORTS_H

// This header is used for patches
// This header will be split up as it becomes larger



// ### Variables ###


// ### types ###


// ### Functions ###

BOOL imports_init();

WINBASEAPI
HMODULE
WINAPI
LoadLibraryA_p(
    _In_ LPCSTR lpLibFileName
);

WINBASEAPI
FARPROC
WINAPI
GetProcAddress_p(
    _In_ HMODULE hModule,
    _In_ LPCSTR lpProcName
);

#endif
