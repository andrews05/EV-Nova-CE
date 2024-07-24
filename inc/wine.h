#ifndef WINE_H
#define WINE_H

#ifdef __cplusplus
extern "C" {
#endif

#define IS_WINE (GetProcAddress(GetModuleHandleA("ntdll.dll"), "wine_get_version") != 0)

// ### types ###

// ### Variables ###

// ### Functions ###

BOOL wine_add_dll_overrides();
BOOL wine_add_dll_override(WCHAR* dll_name);

#ifdef __cplusplus
};
#endif

#endif
