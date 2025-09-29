#include "protocolutils.h"

#include <cstring>

namespace protocol
{
    quint8 calculateCrc(const quint8 *data, int length)
    {
        quint8 crc = 0;
        for (int i = 0; i < length; ++i) {
            quint8 extract = data[i];
            for (int bit = 0; bit < 8; ++bit) {
                const quint8 sum = (crc ^ extract) & 0x01;
                crc >>= 1;
                if (sum != 0) {
                    crc ^= kCrcPolynomial;
                }
                extract >>= 1;
            }
        }
        return crc;
    }

    quint8 calculateCrc(const QByteArray &payload)
    {
        return calculateCrc(reinterpret_cast<const quint8*>(payload.constData()), payload.size());
    }

    QByteArray buildFrame(quint8 command, quint32 data)
    {
        CommandStruct frame {};
        frame.header = kHeader;
        frame.command = command;
        frame.data = data;

        QByteArray crcPayload;
        crcPayload.append(char(frame.command));
        crcPayload.append(reinterpret_cast<const char*>(&frame.data), sizeof(frame.data));
        frame.crc = calculateCrc(crcPayload);
        frame.footer = kFooter;

        QByteArray serialized;
        serialized.resize(sizeof(CommandStruct));
        std::memcpy(serialized.data(), &frame, sizeof(CommandStruct));
        return serialized;
    }

    bool tryExtractFrame(QByteArray &buffer, CommandStruct &frame)
    {
        while (buffer.size() >= kFrameSize) {
            const int headerIndex = buffer.indexOf(char(kHeader));
            if (headerIndex < 0) {
                buffer.clear();
                return false;
            }

            if (headerIndex > 0) {
                buffer.remove(0, headerIndex);
            }

            if (buffer.size() < kFrameSize) {
                return false;
            }

            if (quint8(buffer.at(kFrameSize - 1)) != kFooter) {
                buffer.remove(0, 1);
                continue;
            }

            std::memcpy(&frame, buffer.constData(), sizeof(CommandStruct));

            QByteArray crcPayload;
            crcPayload.append(char(frame.command));
            crcPayload.append(reinterpret_cast<const char*>(&frame.data), sizeof(frame.data));
            if (calculateCrc(crcPayload) != frame.crc) {
                buffer.remove(0, 1);
                continue;
            }

            buffer.remove(0, kFrameSize);
            return true;
        }

        return false;
    }

} // Cho cái namespace protocol
