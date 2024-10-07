#include <windows.h>
#include <stdio.h>
#include <shlobj.h>
#include "macros/patch.h"
#include "nova.h"

// Change some paths to be relative to CWD to allow loading data from an alternate directory
// This also configures the ".nplay" file extension to open EV Nova using the directory of the file


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


// Convenience function to set a registry value
void setRegValue(const char *name, const char *valueName, const char *value) {
    HKEY newKey;
    RegCreateKeyExA(HKEY_CURRENT_USER, name, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &newKey, NULL);
    RegSetValueExA(newKey, valueName, 0, REG_SZ, (BYTE *)value, strlen(value) + 1);
    RegCloseKey(newKey);
}

// Handle opening of .nplay files
CALL(0x00503F99, _parseCommandLine);
void parseCommandLine() {
    // Get path to exe
    char exePath[MAX_PATH];
    GetModuleFileName(NULL, exePath, sizeof(exePath));

    // Store the app path in the registry to allow scripts to locate EV Nova
    setRegValue("Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\EV Nova.exe", NULL, exePath);

    // Configure the .nplay file association
    char temp[MAX_PATH + 7];
    setRegValue("Software\\Classes\\.nplay", NULL, "EVNova.Play.1");
    setRegValue("Software\\Classes\\EVNova.Play.1", NULL, "Play EV Nova");
    sprintf(temp, "\"%s\" \"%%1\"", exePath);
    setRegValue("Software\\Classes\\EVNova.Play.1\\shell\\open\\command", NULL, temp);
    sprintf(temp, "\"%s\",-203", exePath); // See res.rc
    setRegValue("Software\\Classes\\EVNova.Play.1\\DefaultIcon", NULL, temp);
    SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);

    // Call the original function to parse command line arguments
    ((void (*)())0x00508880)();

    // Change working directory to first argument (the .nplay file) if provided
    if (g_nv_argc > 1) {
        SetCurrentDirectory(g_nv_argv[1]);
    }
}
