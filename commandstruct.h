#ifndef COMMANDSTRUCT_H
#define COMMANDSTRUCT_H

#include "qglobal.h"
// Struct của gói tin truyền nhận
#pragma pack(push,1)
struct CommandStruct {
    quint8 header;
    quint8 command;
    quint32 data;
    quint8 crc;
    quint8 footer;
};
#pragma pack(pop)

#endif // COMMANDSTRUCT_H
