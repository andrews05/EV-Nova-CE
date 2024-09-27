#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Change some paths to be relative to CWD instead of the exe
// This allows loading data from an alternate directory


bool g_novaFilesFallback = false;
bool g_pluginsFallback = false;

// Clear call to create Nova Files folder
CLEAR(0x004BD221, 0x90, 0x004BD221 + 5);

// When Nova Files was not found in CWD, prepend "9:" to fallback to the exe dir
CALL(0x004BD233, _loadNovaFilesFallback);
int loadNovaFilesFallback(char *folderPath, char *extension, bool log) {
    g_novaFilesFallback = true;
    return nv_LoadFilesInFolder("9:Nova Files", extension, log);
}

// When Nova Plug-ins was not found in CWD, remove "Nova " prefix and try again
// This matches the name in Mac Nova and is helpful for compatibility
CALL(0x004BD2D6, _loadNovaPluginsFallback);
int loadNovaPluginsFallback(char *folderPath, char *extension, bool log) {
    int error = nv_LoadFilesInFolder(folderPath, extension, log);
    if (error) {
        error = nv_LoadFilesInFolder(folderPath + 5, extension, log);
        g_pluginsFallback = !error;
        // If still not found, the game will create "Nova Plug-Ins" and try again
    }
    return error;
}

// Ensure movies and music are loaded from appropriate nova files dir
CALL(0x0049D8FA, _convertMacFilesPath); // Nova Files, shipyard movie
CALL(0x0049DBDF, _convertMacFilesPath); // Nova Files, desc movie
CALL(0x004AB6FA, _convertMacFilesPath); // Nova Files, music
void convertMacFilesPath(char *winPath, char *macPath) {
    if (!g_novaFilesFallback) {
        // Skip the existing "9:" prefix
        macPath += 2;
    }
    nv_ConvertMacPathToWin(winPath, macPath);
}

// Ensure movies and music are loaded from appropriate plug-ins dir
CALL(0x0049D87D, _convertMacPluginsPath); // Nova Plug-ins, shipyard movie
CALL(0x0049DB62, _convertMacPluginsPath); // Nova Plug-ins, desc movie
CALL(0x004AB656, _convertMacPluginsPath); // Nova Plug-ins, music
void convertMacPluginsPath(char *winPath, char *macPath) {
    // Skip the existing "9:" prefix, as well as "Nova " when appropriate
    macPath += g_pluginsFallback ? 7 : 2;
    nv_ConvertMacPathToWin(winPath, macPath);
}

// Skip existing "9:" prefix for pilots paths
SETDWORD(0x004BD0F4 + 2, 0x0056DDC9 + 2); // Pilots
SETDWORD(0x004BD182 + 2, 0x0056DDC9 + 2); // Pilots

// Remove warning about missing music file
CLEAR(0x004D2B1E, 0x90, 0x004D2B1E + 5);
