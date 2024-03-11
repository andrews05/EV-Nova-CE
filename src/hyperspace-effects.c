#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Allows the hyperspace effects preference to control the flash


// Clear call to hide the hyperspace effects checkbox
CLEAR(0x00488778, 0x90, 0x00488778 + 5);

// Replace calls to set the color of the flash
CALL(0x0044F729, _SetFlashColor); // Jump
CALL(0x00456767, _SetFlashColor); // Hypergate
CALL(0x00456F27, _SetFlashColor); // Wormhole
void SetFlashColor(QDColor *color) {
    // If no hyperspace effects, use black instead of the default white
    g_nv_currentContext->fgColor = g_nv_noHyperspaceEffects ? (QDColor){} : *color;
}
