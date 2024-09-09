#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Change some paths to be relative to CWD instead of the exe
// This allows loading data from an alternate directory


bool g_novaFilesFallback = false;

// Clear call to create Nova Files folder
CLEAR(0x004BD221, 0x90, 0x004BD221 + 5);

// When Nova Files was not found in CWD, prepend "9:" to fallback to the exe dir
CALL(0x004BD233, _loadNovaFilesFallback);
int loadNovaFilesFallback(char *folderPath, char *extension, bool log) {
    g_novaFilesFallback = true;
    return nv_LoadFilesInFolder("9:Nova Files", extension, log);
}

// Ensure movies and music are loaded from CWD when appropriate
CALL(0x0049D8FA, _convertMacPathToWin); // Nova Files, shipyard movie
CALL(0x0049DBDF, _convertMacPathToWin); // Nova Files, desc movie
CALL(0x004AB6FA, _convertMacPathToWin); // Nova Files, music
void convertMacPathToWin(char *winPath, char *macPath) {
    if (!g_novaFilesFallback) {
        // Add 2 to the offset to skip the existing "9:" prefix
        macPath += 2;
    }
    nv_ConvertMacPathToWin(winPath, macPath);
}

// Skip existing "9:" prefix for plug-ins and pilots paths
SETDWORD(0x0049D85D + 1, 0x0056D1A0 + 2); // Nova Plug-Ins, shipyard movie
SETDWORD(0x0049DB42 + 1, 0x0056D1A0 + 2); // Nova Plug-Ins, desc movie
SETDWORD(0x004AB636 + 1, 0x0056D1F8 + 2); // Nova Plug-Ins, music
SETDWORD(0x004BD0f4 + 2, 0x0056DDC9 + 2); // Pilots
SETDWORD(0x004BD182 + 2, 0x0056DDC9 + 2); // Pilots

// Remove warning about missing music file
CLEAR(0x004D2B1E, 0x90, 0x004D2B1E + 5);
