#ifndef SOCKETCONTROL_H
#define SOCKETCONTROL_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include <commandstruct.h>

class SocketControl : public QObject
{
    Q_OBJECT

public:
    explicit SocketControl(QObject *parent = nullptr);
    SocketControl(const QString &ip, int port, QObject *parent = nullptr);
    ~SocketControl() override;
    void connectToDevice(const QString &ip, int port);
    void disconnectFromDevice();
    QAbstractSocket::SocketState state() const;
    bool isConnected() const;
    quint64 send(const QByteArray &);
    quint64 SendCommand(quint8 cmd, quint32 data);

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
    QTcpSocket m_socket;
    QString _ip;
    int _port;
};

#endif // SOCKETCONTROL_H
