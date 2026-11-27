#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Remove use of EVNova.ini and load strings only from STR# resources


// Remove call to loadStringFromIni from loadStringFromList
CLEAR_NOP(0x004B8CB5, 0x004B8CBA);

// Change other uses of loadStringFromIni to use loadStringFromList, with conversion to c-string
LJMP(0x004BD000, _loadStringFromIni);
void loadStringFromIni(char *out, int listID, int entry) {
    char pString[256];
    nv_loadStringFromList(pString, listID, entry);
    if (pString[0] != 0) {
        memcpy(out, pString+1, pString[0]);
        out[(int)pString[0]] = 0;
    }
}
