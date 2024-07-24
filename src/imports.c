#include <windows.h>
#include <stdio.h>
#include "imports.h"
#include "wine.h"

extern char _p_idata_start__, _image_base__;

BOOL __attribute__((optimize("O0"))) imports_init()
{
    char* failed_mod = NULL;
    char* failed_func = NULL;

    PIMAGE_IMPORT_DESCRIPTOR import_desc = (void*)&_p_idata_start__;

    while (import_desc->FirstThunk)
    {
        if (import_desc->Name)
        {
            char* mod_name = (char*)((DWORD)&_image_base__ + import_desc->Name);

            HMODULE mod = LoadLibraryA_p(mod_name);

            if (mod)
            {
                PIMAGE_THUNK_DATA first_thunk = (void*)((DWORD)&_image_base__ + import_desc->FirstThunk);

                while (first_thunk->u1.AddressOfData)
                {
                    if ((first_thunk->u1.Ordinal & IMAGE_ORDINAL_FLAG) == 0)
                    {
                        PIMAGE_IMPORT_BY_NAME func = (void*)((DWORD)&_image_base__ + first_thunk->u1.AddressOfData);

                        first_thunk->u1.Function = (DWORD)GetProcAddress_p(mod, (const char*)func->Name);

                        if (!first_thunk->u1.Function)
                        {
                            failed_mod = mod_name;
                            failed_func = (char*)func->Name;
                        }
                    }
                    else
                    {
                        int ordinal = (first_thunk->u1.Ordinal & ~IMAGE_ORDINAL_FLAG32) & 0xffff;

                        first_thunk->u1.Function = (DWORD)GetProcAddress_p(mod, MAKEINTRESOURCEA(ordinal));

                        if (!first_thunk->u1.Function)
                        {
                            failed_mod = mod_name;
                            failed_func = "Unknown Ordinal";
                        }
                    }

                    first_thunk++;
                }
            }
            else if (!failed_mod)
            {
                failed_mod = mod_name;
            }
        }

        import_desc++;
    }

    if (wine_add_dll_overrides()) {
        // Newly added dll overrides only work after a restart
        char exePath[MAX_PATH];
        GetModuleFileName(NULL, exePath, sizeof(exePath));
        ShellExecuteA(NULL, "open", exePath, NULL, NULL, 0);
        return 0;
    }

    if (failed_func)
    {
        char msg[256];
        _snprintf(
            msg,
            sizeof msg,
            "The procedure entry point %s could not be located in the dynamic link library %s.",
            failed_func,
            failed_mod);

        MessageBoxA(NULL, msg, NULL, MB_OK);

        return FALSE;
    }

    if (failed_mod)
    {
        char msg[256];
        _snprintf(
            msg,
            sizeof msg,
            "The program can't start because %s is missing from your computer. "
                "Try reinstalling the program to fix this problem.",
            failed_mod);

        MessageBoxA(NULL, msg, NULL, MB_OK);

        return FALSE;
    }

    return TRUE;
}
