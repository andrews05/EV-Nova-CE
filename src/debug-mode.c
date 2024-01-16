#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Allows setting debug mode from cnc ddraw.ini


/*
Debug Mode Effects:
- Show ids/raw values in various dialogs
- Always have afterburner
- 50x faster armor regen
- Ignore capture odds (both player and AI)
- Skip combat rating requirement for domination

Debug Mode Hotkeys:
Alt+Home:      Enter debug mode
Hold Ctrl:     Show target debug info
Shift+4:       +50k credits
Alt+Shift+4:   -10k credits
Ins:           Spawn ship
Alt+Ins:       Spawn fleet 129 (Federation)
Alt+Ctrl+Ins:  Spawn fleet 135 (Pirates)
Alt+Shift+Ins: Spawn fleet 149 (Rebels)
Ctrl+Ins:      Spawn pers 641 (Hannah Chick)
Del:           Delete target
PageUp:        Cycle ship type forwards
PageDn:        Cycle ship type backwards
F6:            Restore stats and ammo, activate rank 147 (Hypergate Access)
Alt+F6:        Same as above, but empty fuel
F7:            Make target hostile
Alt+F7:        Make target neutral and leave system
F8:            Disable target
Alt+F8:        Assign target as hired escort
F9:            Destroy target
Shift+F9:      Destroy target as player (bear the consequences)
Alt+F9:        Disable player
F10:           Explore map
Alt+F10:       Unexplore map
Backspace:     Complete jump instantly
Home:          Restart after death (this works even when not in debug mode)
End:           Exit debug mode
*/


// Replace a CALL to KeyCheck
CALL(0x004507B6, _CheckEnableDebug);
int CheckEnableDebug(short scanCode) {
    // Enable debug with Alt+Home
    if (!g_nv_debugMode && (nv_KeyCheck(0x38) || nv_KeyCheck(0x6F)) && nv_KeyCheck(0x60)) {
        nv_PlaySound(g_nv_beep1, 1, g_nv_currentVolume, g_nv_currentVolume);
        g_nv_debugMode = true;
    }
    return nv_KeyCheck(scanCode);
}

// Fix NumberToString to handle negative values, as displayed in some places in debug mode
CALL(0x004BBCF4, _NumberToString);
int NumberToString(char *buffer, int value, int flags) {
    bool negative = value < 0;
    if (negative) {
        *buffer++ = '-';
        value *= -1;
    }
    // Proceed with original function call
    return negative + ((int (*)(char*, int, int))0x004FBFE0)(buffer, value, flags);
}


// Remap keys to be usable on modern keyboards, including laptops

// Explore map: F10 (was Numpad= on Mac)
SETBYTE(0x004507B4 + 1, 0x44);

// Exit debug: End (was F13 on Mac)
SETBYTE(0x004531D3 + 1, 0x65);

// Make target hostile: F7 (was Numpad/)
SETBYTE(0x00450A6B + 1, 0x41);

// Complete jump: Backspace (was Numpad.)
SETBYTE(0x00452B20 + 1, 0x0E);

// Spawn ship: Remove F6 alias
SETBYTE(0x00452D30 + 1, 0xFF);

// Spawn fleet modifier: Shift (was B, originally Cmd on Mac)
SETBYTE(0x00452BF5 + 1, 0x2A);

// Delete ship: Remove F7 and Numlock aliases
SETBYTE(0x00452D70 + 1, 0xFF);
SETBYTE(0x00452D80 + 1, 0xFF);

// Disable ship: Remove PageUp alias
SETWORD(0x004B450E + 7, 0xFF);

// Destory ship: Remove PageDn alias
SETWORD(0x004B4517 + 7, 0xFF);

// Restore stats: F6 (was Numpad*)
SETWORD(0x004B4520 + 7, 0x40);

// Cycle ship up: PageUp (was Numpad+)
SETWORD(0x004B453B + 7, 0x62);

// Cycle ship down: PageDn (was Numpad-)
SETWORD(0x004B4544 + 7, 0x67);
