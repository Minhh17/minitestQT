#ifndef FPGA_SERVER_H
#define FPGA_SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QRandomGenerator>

#pragma pack(push,1)
struct CommandStruct {
    quint8 header;
    quint8 command;
    quint32 data;
    quint8 crc;
    quint8 footer;
};
#pragma pack(pop)

class FpgaServer : public QObject
{
    Q_OBJECT
public:
    explicit FpgaServer(QObject *parent = nullptr);
    ~FpgaServer() override;

    bool startListening(quint16 port);

private slots:
    void onNewConnection();
    void onReadyRead();

private:
    QTcpServer m_server;
    QByteArray m_rx;  // buffer stream cho socket
    // Each new connection is appended to this list
    QList<QTcpSocket *> m_clients;
};

#endif // FPGA_SERVER_H
