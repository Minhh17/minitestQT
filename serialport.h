#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QString>
#include <QMessageBox>
#include <QByteArray>

class SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = nullptr);

    bool Connect(QString portname);
    bool Close();

    qint64 Write(QByteArray data);

    bool isOpen();

    ~SerialPort();
private:
    QSerialPort *_serialport;

private slots:
    void dataReady();

signals:
    void dataRecevie(QByteArray data);
    void disconnected();
};

#endif // SERIALPORT_H
