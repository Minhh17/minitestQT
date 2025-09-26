#ifndef DECEVIESCONTROL_H
#define DECEVIESCONTROL_H

#include <QObject>
#include <serialport.h>
#include <commandstruct.h>

class DeceviesControl : public QObject
{
    Q_OBJECT
public:
    explicit DeceviesControl(QObject *parent = nullptr);

    DeceviesControl(QString);

    bool Connect();

    qint64 SendCommand(quint8, quint32);

    QString GetPortName();

    void SetPortName(QString);

    bool IsOpen();

    quint8 Crc_Calulater(quint8 *data, int len);

    ~DeceviesControl();

signals:

    void dataReady(QByteArray);

    void disconnected();

private slots:

    void readData(QByteArray);

private:
    SerialPort *_port;
    QString _portName;
    CommandStruct _struct;

};

#endif // DECEVIESCONTROL_H
