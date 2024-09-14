#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Increases map border draw area to 1024x1024

// Map borders are drawn in a fixed 512x512 area, which is comprised of a 256x256 grid of 2x2
// pixels. The data for each block is stored as a set of 4 values for up to 4 nearby systems that
// may influence the the block's colour. The govt with the highest influence value is used.


// First we need to create a new, larger buffer to store the border data
unsigned char g_mapBordersInfl[512 * 512 * 4];
unsigned char g_mapBordersGovt[512 * 512 * 4];

// Clearing the border data
SETDWORD(0x004A3DD5 + 3, _g_mapBordersGovt);
SETDWORD(0x004A3DDC + 3, _g_mapBordersInfl);

SETDWORD(0x004A75D5 + 3, _g_mapBordersGovt);
SETDWORD(0x004A75DE + 3, _g_mapBordersInfl);

SETDWORD(0x004A9D85 + 3, _g_mapBordersGovt);
SETDWORD(0x004A9D90 + 3, _g_mapBordersInfl);
SETDWORD(0x004A9D9B + 3, _g_mapBordersGovt);
SETDWORD(0x004A9Da7 + 3, _g_mapBordersInfl);
SETDWORD(0x004A9DB3 + 3, _g_mapBordersGovt);
SETDWORD(0x004A9DBF + 3, _g_mapBordersInfl);
SETDWORD(0x004A9DCB + 3, _g_mapBordersGovt);
SETDWORD(0x004A9Dd7 + 3, _g_mapBordersInfl);

// Replicating the 1/8th scale preview data?
SETDWORD(0x004A9F79 + 3, _g_mapBordersGovt);
SETDWORD(0x004A9F87 + 3, _g_mapBordersGovt);
SETDWORD(0x004A9F9C + 3, _g_mapBordersInfl);
SETDWORD(0x004A9FAA + 3, _g_mapBordersInfl);

// Constructing the border data
SETDWORD(0x004AA420 + 3, _g_mapBordersInfl);
SETDWORD(0x004AA450 + 3, _g_mapBordersInfl);
SETDWORD(0x004AA46E + 3, _g_mapBordersGovt);
SETDWORD(0x004AA4A9 + 3, _g_mapBordersInfl);
SETDWORD(0x004AA4D6 + 3, _g_mapBordersInfl);
SETDWORD(0x004AA4E6 + 3, _g_mapBordersGovt);
SETDWORD(0x004AA590 + 3, _g_mapBordersGovt);
SETDWORD(0x004AA5B7 + 3, _g_mapBordersInfl);
SETDWORD(0x004AA5D3 + 3, _g_mapBordersGovt);
SETDWORD(0x004AA5E4 + 3, _g_mapBordersInfl);
SETDWORD(0x004AA5F6 + 3, _g_mapBordersInfl);

// Drawing the border data
SETDWORD(0x004AA695 + 3, _g_mapBordersInfl);
SETDWORD(0x004AA7A4 + 3, _g_mapBordersInfl);
SETDWORD(0x004AA820 + 3, _g_mapBordersGovt);


// Increase the width and height
SETWORD(0x004A3E14 + 2, 512);
SETWORD(0x004A3E1A + 3, 512);
SETWORD(0x004A3E24 + 3, 512);

SETWORD(0x004A7613 + 3, 512);
SETWORD(0x004A7622 + 2, 512);
SETWORD(0x004A7628 + 3, 512);

SETBYTE(0x004A9D7A + 2, 9); // Left shift
SETWORD(0x004A9DEA + 3, 512);
SETWORD(0x004A9DFA + 3, 512);

SETBYTE(0x004A9ED1 + 2, 9);
SETBYTE(0x004A9F4E + 2, 9);
SETWORD(0x004A9F51 + 2, 512);
SETWORD(0x004A9F64 + 2, 512);
SETWORD(0x004AA001 + 5, 512);
SETWORD(0x004AA021 + 5, 512);

SETBYTE(0x004AA2C4 + 2, 9);
SETWORD(0x004AA2D3 + 5, 512);
SETWORD(0x004AA2EC + 5, 512);

SETBYTE(0x004AA67B + 2, 9);
SETWORD(0x004AA6BB + 5, 512);
SETWORD(0x004AA6CF + 5, 512);


// To improve performance when the actual map area is smaller, determine the width and use this to
// restrict the border calculations where possible.
short g_mapBordersWidth = 512;
CALL(0x004A9D3B, _constructMapBorders);
void constructMapBorders(short a, short b, short c, short d, QDRect *mapRect) {
    short mapWidth = (mapRect->right - mapRect->left) / 2;
    if (mapWidth < g_mapBordersWidth) {
        g_mapBordersWidth = mapWidth;
    }
    ((void (*)(short, short, short, short, QDRect*))0x004A9D50)(a, b, c, d, mapRect);
}
SETINST(0x004AA250, "ADD EBP, [_g_mapBordersWidth]");
