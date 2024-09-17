#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Increases map border draw area and improves border sizing

// Map borders are drawn in a fixed 512x512 area, which is comprised of a 256x256 grid of 2x2
// pixels. The data for each block is stored as a set of 4 values for up to 4 nearby systems that
// may influence the the block's colour. The govt with the highest influence value is used.


// Set the size of the border data to 860x512 which will allow us to draw up to 1720x1024.
// This is sufficient to cover the map if the dialog filled a 1920x1080 screen.
#define BORDERS_WIDTH 860
#define BORDERS_SHIFT 9 // Gives 512
#define BORDERS_HEIGHT (1 << BORDERS_SHIFT)

#define _SETWORD(address, val) SETWORD(address, val)
#define _SETBYTE(address, val) SETBYTE(address, val)
#define SETWIDTH(address) _SETWORD(address, BORDERS_WIDTH)
#define SETHEIGHT(address) _SETWORD(address, BORDERS_HEIGHT)
#define SETSHIFT(address) _SETBYTE(address, BORDERS_SHIFT)


// First we need to create a new, larger buffer to store the border data
unsigned char g_mapBordersInfl[BORDERS_WIDTH * BORDERS_HEIGHT * 4];
unsigned char g_mapBordersGovt[BORDERS_WIDTH * BORDERS_HEIGHT * 4];

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
SETWIDTH(0x004A3E14 + 2);
SETHEIGHT(0x004A3E1A + 3);
SETWIDTH(0x004A3E24 + 3);

SETWIDTH(0x004A7613 + 3);
SETWIDTH(0x004A7622 + 2);
SETHEIGHT(0x004A7628 + 3);

SETSHIFT(0x004A9D7A + 2);
SETHEIGHT(0x004A9DEA + 3);
SETWIDTH(0x004A9DFA + 3);

SETSHIFT(0x004A9ED1 + 2);
SETSHIFT(0x004A9F4E + 2);
SETHEIGHT(0x004AA001 + 5);
SETWIDTH(0x004AA021 + 5);

SETSHIFT(0x004AA2C4 + 2);

SETSHIFT(0x004AA67B + 2);
SETHEIGHT(0x004AA6BB + 5);
SETWIDTH(0x004AA6CF + 5);


// To improve performance when the actual map area is smaller, determine the size and use this to
// restrict the border calculations (see map-borders2.asm).
int g_mapBordersVisibleWidth = BORDERS_WIDTH;
int g_mapBordersVisibleHeight = BORDERS_HEIGHT;
CALL(0x004A9D3B, _constructMapBorders);
void constructMapBorders(short a, short b, short c, short d, QDRect *mapRect) {
    short mapWidth = (mapRect->right - mapRect->left) / 2;
    if (mapWidth < g_mapBordersVisibleWidth) {
        g_mapBordersVisibleWidth = mapWidth;
    }
    short mapHeight = (mapRect->bottom - mapRect->top) / 2;
    if (mapHeight < g_mapBordersVisibleHeight) {
        g_mapBordersVisibleHeight = mapHeight;
    }
    ((void (*)(short, short, short, short, QDRect*))0x004A9D50)(a, b, c, d, mapRect);
}


// Adjust the border sizing relative to the zoom level to make it more consistent.
// Do this by lower the scaling factor add then adding a little extra.
// Also allow the minor borders to be slightly more prominent than before.
SETDOUBLE(0x00575A38, 11); // minor border scale
SETINST(0x004AA1B6, "ADD ECX, 0x9");

SETDOUBLE(0x00575A40, 22); // major border scale
SETINST(0x004AA200, "ADD ECX, 0xC");


// Fix the proportions of the cyan dot marking the player's current system.
// The fillCircle function is slightly wrong. Rather than trying to find and fix the error, we can
// just follow it up with a call to frameCircle which does work correctly.
CALL(0x004A91F2, _markCurrentSystem);
void markCurrentSystem(QDRect *rect) {
    ((void (*)(QDRect*))0x004BB260)(rect);
    ((void (*)(QDRect*))0x004BA350)(rect);
}
