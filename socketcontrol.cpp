#include "socketcontrol.h"
#include <QDebug>
#include "protocolutils.h"

SocketControl::SocketControl(QObject *parent)
    : QObject{parent}
    , m_socket(this)
{
    connect(&m_socket, &QTcpSocket::connected, this, &SocketControl::connected);
    connect(&m_socket, &QTcpSocket::disconnected, this, &SocketControl::disconnected);
    connect(&m_socket, &QTcpSocket::errorOccurred, this, &SocketControl::errorOccurred);
    connect(&m_socket, &QTcpSocket::stateChanged, this, &SocketControl::socket_stateChanged);
    connect(&m_socket, &QTcpSocket::readyRead, this, &SocketControl::socket_readyRead);
}

SocketControl::SocketControl(const QString &ip, int port, QObject *parent)
    : SocketControl(parent)
{
    connectToDevice(ip, port);
}

SocketControl::~SocketControl()
{
    disconnectFromDevice();
}

void SocketControl::connectToDevice(const QString &ip, int port)
{
    if (m_socket.isOpen()) {
        if (ip == _ip && port == _port) {
            return;
        }
        m_socket.close();
    }

    _ip = ip;
    _port = port;
    m_socket.connectToHost(_ip, _port);
}

void SocketControl::disconnectFromDevice()
{
    if (m_socket.isOpen()) {
        m_socket.disconnectFromHost();
        if (m_socket.state() != QAbstractSocket::UnconnectedState) {
            m_socket.waitForDisconnected(100);
        }
    }
}

QAbstractSocket::SocketState SocketControl::state() const
{
    return m_socket.state();
}

bool SocketControl::isConnected() const
{
    return m_socket.state() == QAbstractSocket::ConnectedState;
}

quint64 SocketControl::send(const QByteArray &data)
{
    if(!m_socket.isOpen()) {
        return -1;
    }
    return m_socket.write(data);
}

quint64 SocketControl::SendCommand(quint8 cmd, quint32 data)
{
    qDebug() << "SocketControl::SendCommand" << cmd << data;
    return send(protocol::buildFrame(cmd, data));
}

void SocketControl::socket_stateChanged(QAbstractSocket::SocketState state)
{
    if (state == QAbstractSocket::UnconnectedState) {
        m_socket.close();
    }
    emit stateChanged(state);
}

void SocketControl::socket_readyRead()
{
    const QByteArray data = m_socket.readAll();
    if (!data.isEmpty()) {
        emit dataReady(data);
    }
    qDebug() << "socket_readyRead:" << data;
}
