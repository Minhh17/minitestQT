#include "fpgaserver.h"

#include <QDataStream>
#include <QDateTime>
#include <QDebug>

// static constexpr quint8 HDR = 'A';
// static constexpr quint8 FTR = 'B';
// static constexpr int    PKT = 8;

static quint8 Crc_Calulater(quint8 *data, int len)
{
    quint8 crc = 0;
    quint8 extract, sum;
    quint8 polynomial = 0x8C;
    qDebug() << "len = " << len << Qt::endl;
    for(int i = 0; i < len; i++) {
        extract = *data;
        for(int j = 8; j > 0; j--) {
            sum = (quint8)((crc ^ extract) & 0x01);
            crc >>= 1;
            if(sum != 0)
                crc ^= polynomial;
            extract >>= 1;
        }
        data++;
    }
    return crc;
}

FpgaServer::FpgaServer(QObject *parent)
    : QObject(parent)
{
    connect(&m_server, &QTcpServer::newConnection,
            this, &FpgaServer::onNewConnection);
}

FpgaServer::~FpgaServer()
{
    // Close all client sockets gracefully
    for (QTcpSocket *socket : std::as_const(m_clients)) {
        socket->disconnect(this);
        socket->disconnectFromHost();
        socket->deleteLater();
    }
    m_clients.clear();
    m_server.close();
}

bool FpgaServer::startListening(quint16 port)
{
    if (!m_server.listen(QHostAddress::Any, port)) {
        qCritical() << "Server failed to listen on port" << port
                    << ":" << m_server.errorString();
        return false;
    }
    qInfo() << "Server listening on" << m_server.serverAddress().toString()
            << ":" << m_server.serverPort();
    return true;
}

void FpgaServer::onNewConnection()
{
    // Accept all pending connections
    while (m_server.hasPendingConnections()) {
        QTcpSocket *socket = m_server.nextPendingConnection();
        if (!socket)
            continue;
        m_clients.append(socket);
        qInfo() << "New client connected from" << socket->peerAddress().toString()
                << ":" << socket->peerPort();
        // Connect signals to handle incoming data and cleanup
        connect(socket, &QTcpSocket::readyRead, this, &FpgaServer::onReadyRead);
        connect(socket, &QTcpSocket::disconnected, socket, &QObject::deleteLater);
        connect(socket, &QTcpSocket::disconnected, [this, socket]() {
            m_clients.removeAll(socket);
            qInfo() << "Client disconnected";
        });
    }
}

void FpgaServer::onReadyRead()
{
    qInfo() << "FpgaServer::onReadyRead() triggered";
    QTcpSocket *senderSocket = qobject_cast<QTcpSocket *>(sender());
    if (!senderSocket)
        return;

    static QByteArray buffer; // lưu dồn dữ liệu chưa xử lý

    buffer.append(senderSocket->readAll());
    qInfo() << "Raw data:" << buffer.toHex() << " sizeof(CommandStruct)"<< sizeof(CommandStruct);
    const int packetSize = sizeof(CommandStruct); // 8 bytes

    // Duyệt buffer tìm gói tin có header 'A' và footer 'B'
    while (buffer.size() >= packetSize)
    {
        // Tìm header 'A'
        int headerIndex = buffer.indexOf('A');
        if (headerIndex < 0)
        {
            buffer.clear(); // ko tìm thấy header, xóa buffer
            break;
        }

        // Xóa dữ liệu trước header
        if (headerIndex > 0)
            buffer.remove(0, headerIndex);

        if (buffer.size() < packetSize)
            break; // chưa đủ dữ liệu

        // Kiểm tra footer có đúng 'B'
        if (buffer.at(packetSize - 1) != 'B')
        {
            // footer sai, loại bỏ header này và tìm lại
            buffer.remove(0, 1);
            continue;
        }

        // Giải mã gói tin
        CommandStruct recvCmd;
        memcpy(&recvCmd, buffer.constData(), packetSize);

        // Tạo buffer tạm tính CRC
        quint8 crcBuf[5];
        memcpy(crcBuf, &recvCmd.command, 1);
        memcpy(crcBuf + 1, &recvCmd.data, 4);

        quint8 crcCalc = Crc_Calulater(crcBuf, 5);

        if (crcCalc != recvCmd.crc)
        {
            // CRC sai, loại gói tin
            qWarning() << "CRC check failed";
            buffer.remove(0, 1);
            continue;
        }

        // Đã nhận đúng gói, xử lý dữ liệu
        quint8 cmd = recvCmd.command;
        quint16 value1 = QRandomGenerator::global()->bounded(0x10000); // 16 bit ngẫu nhiên
        quint16 value2 = QRandomGenerator::global()->bounded(0x10000);
        quint32 responseData = (static_cast<quint32>(value1) << 16) | value2;

        // Chuẩn bị gói phản hồi
        CommandStruct responseCmd;
        responseCmd.header = 'A';
        responseCmd.command = cmd;
        responseCmd.data = responseData;
        // Tính crc trên command + data
        QByteArray crcArray;
        crcArray.append(char(responseCmd.command));
        crcArray.append(reinterpret_cast<const char*>(&responseCmd.data), 4);
        responseCmd.crc = Crc_Calulater(reinterpret_cast<quint8*>(crcArray.data()), crcArray.size());
        responseCmd.footer = 'B';

        QByteArray sendBa;
        sendBa.append(char(responseCmd.header));
        sendBa.append(char(responseCmd.command));
        sendBa.append(reinterpret_cast<const char*>(&responseCmd.data), 4);
        sendBa.append(char(responseCmd.crc));
        sendBa.append(char(responseCmd.footer));

        senderSocket->write(sendBa);
        senderSocket->flush();

        qInfo() << "Received cmd:" << cmd << "data:" << recvCmd.data
                << "Responded with val1:" << value1 << "val2:" << value2;

        // Xóa gói đã xử lý
        buffer.remove(0, packetSize);
    }
}
