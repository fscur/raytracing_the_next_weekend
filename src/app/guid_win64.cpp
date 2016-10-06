#include "guid.h"
#include <windows.h> 

guid guidGenerator::newGuid()
{
    GUID newId;
    CoCreateGuid(&newId);

    auto bytes = new byte[16];
    bytes[0] = (newId.Data1 >> 24) & 0xFF;
    bytes[1] = (newId.Data1 >> 16) & 0xFF;
    bytes[2] = (newId.Data1 >> 8) & 0xFF;
    bytes[3] = (newId.Data1) & 0xff;
    bytes[4] = (newId.Data2 >> 8) & 0xFF;
    bytes[5] = (newId.Data2) & 0xff;
    bytes[6] = (newId.Data3 >> 8) & 0xFF;
    bytes[7] = (newId.Data3) & 0xFF;
    bytes[8] = newId.Data4[0];
    bytes[9] = newId.Data4[1];
    bytes[10] = newId.Data4[2];
    bytes[11] = newId.Data4[3];
    bytes[12] = newId.Data4[4];
    bytes[13] = newId.Data4[5];
    bytes[14] = newId.Data4[6];
    bytes[15] = newId.Data4[7];

    return guid(bytes);
}