#ifndef SOCKETCONTROL_H
#define SOCKETCONTROL_H

#include <QObject>
#include <QTcpSocket>
#include <commandstruct.h>

class SocketControl : public QObject
{
    Q_OBJECT
public:
    explicit SocketControl(QObject *parent = nullptr);
    SocketControl(QString ip, int port);
    ~SocketControl();
    void connectToDevice(QString ip, int port);
    void disconnect();
    QAbstractSocket::SocketState state();
    bool isConnected();
    quint64 send(QByteArray);
    quint64 SendCommand(quint8 cmd, quint32 data);
    quint8 Crc_Calulater(quint8 *data, int len);
signals:
    void connected();
    void disconnected();
    void stateChanged(QAbstractSocket::SocketState);
    void errorOccurred(QAbstractSocket::SocketError);
    void dataReady(QByteArray);

private slots:
    void socket_stateChanged(QAbstractSocket::SocketState state);
    void socket_readyRead();

private:
    QTcpSocket *_socket;
    QString _ip;
    int _port;
    CommandStruct _struct;
};

#endif // SOCKETCONTROL_H
