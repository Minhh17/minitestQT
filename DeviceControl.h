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
    explicit DeviceControl(const QString &portName, QObject *parent = nullptr);

    bool Connect();
    qint64 SendCommand(quint8, quint32);

    QString GetPortName() const;
    void SetPortName(const QString &);
    bool isOpen() const;
    ~DeviceControl() override;

signals:
    void dataReady(QByteArray);
    // void disconnected();

private slots:
    void readData(QByteArray);
    void disconnected();

private:
    SerialPort _port;
    QString _portName;

};

#endif // DEVICECONTROL_H
