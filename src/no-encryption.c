#include <windows.h>
#include "macros/patch.h"
#include "nova.h"

// Removes encryption of pilot files


// Intercept calls to decrypt
CALL(0x004CB2FD, _decryptIfNecessary);
CALL(0x004CB371, _decryptIfNecessary);
short decryptIfNecessary(unsigned int *data, unsigned int length, unsigned int key) {
    // Only perform decryption if data appears to be encrypted (max stellars = 2048)
    if ((unsigned short)data[0] >= 2048) {
        return ((short (*)(unsigned int*, unsigned int, unsigned int))0x0046F960)(data, length, key);
    }
    return 0;
}

// Clear calls to encrypt
CLEAR(0x004C9C11, 0x90, 0x004C9C11 + 5);
CLEAR(0x004C9C3F, 0x90, 0x004C9C3F + 5);
