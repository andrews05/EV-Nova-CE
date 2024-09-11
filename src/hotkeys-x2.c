#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Allows the x2 mode hotkey to be customised


int x2Hotkey;

// Get the x2 hotkey from the ini
CALL(0x004161ED, _readPrefs);
void readPrefs() {
    char buf[8];
    // The default value is 0x14 (caps lock)
    GetPrivateProfileStringA("EV Nova", "key_x2mode", "0x14", buf, sizeof buf, g_iniPath);
    x2Hotkey = strtol(buf, NULL, 0);
    // Proceed with original function call
    ((void (*)(void))0x004C7400)();
}

// Check our custom x2 hotkey instead of the hardcoded one
CALL_NOP(0x004184B2, _checkX2Hotkey);
short WINAPI checkX2Hotkey(int ignored) {
    return GetKeyState(x2Hotkey);
}
