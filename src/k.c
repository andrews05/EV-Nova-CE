#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Applies the HERETiC crack, with a different string when not registered


// Some kind of check in CreateRoid function that makes hector appear...
// Change a CMP with 0 to 1
SETBYTE(0x004218DD + 6, 0x01);

// Some kind of reg check function...
// Change a CMP with 0 to a MOV with 1
SETBYTE(0x004D44E4 + 0, 0xC6);
SETBYTE(0x004D44E4 + 1, 0x05);
SETBYTE(0x004D44E4 + 6, 0x01);
// Change a JLE to length 0 (no jump)
SETBYTE(0x004D44EB + 1, 0x00);

// Change the string shown by the <REG> tag when not registered
char regString[] = "EV Nova Community";
SETDWORD(0x004D45B4 + 1, _regString);
