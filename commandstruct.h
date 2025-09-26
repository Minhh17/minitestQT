#ifndef COMMANDSTRUCT_H
#define COMMANDSTRUCT_H

#include "qglobal.h"

struct CommandStruct
{
    quint8 header;
    quint8 command;
    quint32 data;
    quint8 crc;
    quint8 footer;
};

#endif // COMMANDSTRUCT_H
