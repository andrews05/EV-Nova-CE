#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Allows setting debug mode from cnc ddraw.ini


// Replace CALL to ReadEVNovaIni
CALL(0x0041615E, _ReadEVNovaIni);
void ReadEVNovaIni() {
    // Read debug mode from ddraw ini
    char buf[8];
    GetPrivateProfileStringA("EV Nova", "debug_mode", "false", buf, sizeof(buf), ".\\ddraw.ini");
    g_nv_debugMode = _stricmp(buf, "true") == 0  || _stricmp(buf, "1") == 0;
    
    // Original function call replaced by the patch
    ((void (*)())0x004BCFA0)();
}
