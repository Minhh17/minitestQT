#ifndef DEVICECONTROL_H
#define DEVICECONTROL_H

#include <QObject>
#include <serialport.h>
#include <commandstruct.h>

// PC Side

class DeviceControl : public QObject
{
    Q_OBJECT
public:
    explicit DeviceControl(QObject *parent = nullptr);

    DeviceControl(QString);
    bool Connect();
    qint64 SendCommand(quint8, quint32);
    QString GetPortName();
    void SetPortName(QString);
    bool isOpen();
    quint8 Crc_Calulater(quint8 *data, int len);
    ~DeviceControl();

signals:
    void dataReady(QByteArray);
    // void disconnected();

private slots:
    void readData(QByteArray);
    void disconnected();

private:
    SerialPort *_port;
    QString _portName;
    CommandStruct _struct;

};

#endif // DEVICECONTROL_H
