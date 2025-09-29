#ifndef PROTOCOLUTILS_H
#define PROTOCOLUTILS_H

#include <QByteArray>
#include "commandstruct.h"

namespace protocol
{
constexpr quint8 kHeader = 'A';
constexpr quint8 kFooter = 'B';
constexpr qsizetype kFrameSize = sizeof(CommandStruct);
constexpr quint8 kCrcPolynomial = 0x8C;

quint8 calculateCrc(const quint8 *data, int length);
quint8 calculateCrc(const QByteArray &payload);
QByteArray buildFrame(quint8 command, quint32 data);
bool tryExtractFrame(QByteArray &buffer, CommandStruct &frame);
}

#endif // PROTOCOLUTILS_H
