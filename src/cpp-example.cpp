#include <windows.h>
#include "macros/patch.h"
#include <string>
#include <iostream>
#include <sstream>
#include <initializer_list>


CALL(0x004D2A93, _cpp_example);

EXTERN_C int cpp_example(int unknown)
{
    std::stringstream x;

    for (auto i : { 3735928559, 3131961357 })
    {
        x << std::uppercase << std::hex << i << " ";
    }

    std::string s = x.str();

    MessageBoxA(NULL, s.c_str(), "CPP TEST", MB_OK);
    
    // Original function call replaced by the patch
    return ((int (*)(int))0x004F9C00)(unknown);
}
