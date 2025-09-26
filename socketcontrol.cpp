#include "socketcontrol.h"

SocketControl::SocketControl(QObject *parent)
    : QObject{parent}
{

}

SocketControl::SocketControl(QString ip, int port)
{
    _socket = new QTcpSocket();
    _ip = ip;
    _port = port;
    _struct.header = 'A';
    _struct.footer = 'B';
    connect(_socket, &QTcpSocket::connected, this, &SocketControl::connected);
    connect(_socket, &QTcpSocket::disconnected, this, &SocketControl::disconnected);
    connect(_socket, &QTcpSocket::errorOccurred, this, &SocketControl::errorOccurred);
    connect(_socket, &QTcpSocket::stateChanged, this, &SocketControl::socket_stateChanged);
    connect(_socket, &QTcpSocket::readyRead, this, &SocketControl::socket_readyRead);
    connectToDevice(_ip, _port);
}

SocketControl::~SocketControl()
{
    delete _socket;
}

void SocketControl::connectToDevice(QString ip, int port)
{
    if (_socket->isOpen()) {
        if (ip == _ip && port == _port) {
            return;
        }
        _socket->close();
    }
    _ip = ip;
    _port = port;
    _socket->connectToHost(_ip, _port);
}

void SocketControl::disconnect()
{
    _socket->close();
}

QAbstractSocket::SocketState SocketControl::state()
{
    return _socket->state();
}

bool SocketControl::isConnected()
{
    return _socket->state() == QAbstractSocket::ConnectedState;
}

quint64 SocketControl::send(QByteArray data)
{
    if(!_socket->isOpen()) {
        return -1;
    }
    return _socket->write(data);
}

quint64 SocketControl::SendCommand(quint8 cmd, quint32 data)
{
    QByteArray ba;
    quint8* buff;
    _struct.command = cmd;
    _struct.data = data;
    ba.append(reinterpret_cast<const char*>(&_struct.header), sizeof(char));
    ba.append(reinterpret_cast<const char*>(&_struct.command), sizeof(char));
    ba.append(reinterpret_cast<const char*>(&_struct.data), sizeof(int));
    buff = reinterpret_cast<quint8*>(ba.data());
    _struct.crc = Crc_Calulater(buff, sizeof(buff) - 2);
    ba.append(reinterpret_cast<const char*>(&_struct.crc), sizeof(char));
    ba.append(reinterpret_cast<const char*>(&_struct.footer), sizeof(char));
    //    QByteArray ba(reinterpret_cast<char*>(&_struct), sizeof(CommandStruct));
    return _socket->write(ba);
}

quint8 SocketControl::Crc_Calulater(quint8 *data, int len)
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

void SocketControl::socket_stateChanged(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState) {
        _socket->close();
    }
    emit stateChanged(state);
}

void SocketControl::socket_readyRead()
{
    auto data = _socket->readAll();
    emit dataReady(data);
}
