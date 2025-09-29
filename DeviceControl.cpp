#include "DeviceControl.h"

DeviceControl::DeviceControl(QObject *parent)
    : QObject{parent}
{

}

DeviceControl::DeviceControl(QString portname)
{
    _port = new SerialPort();
    _portName = portname;
    _struct.header = 'A';
    _struct.footer = 'B';
    connect(_port, &SerialPort::dataRecevie, this, &DeviceControl::readData);
    connect(_port, &SerialPort::disconnected, this, &DeviceControl::disconnected);
}

DeviceControl::~DeviceControl()
{
    if (_port != nullptr && _port->isOpen()) {
        qDebug()<< "~DeviceControl() close";
        _port->disconnect();
        _port->Close();
    }
    delete _port;
}

void DeviceControl::readData(QByteArray data)
{
    emit dataReady(data);
}

void DeviceControl::disconnected()
{
    qDebug()<< "DeviceControl::disconnected()";
    if (_port != nullptr && _port->isOpen()) {
        _port->disconnect();
    }
}

bool DeviceControl::Connect()
{
    return _port->Connect(_portName);
}

qint64 DeviceControl::SendCommand(quint8 cmd, quint32 data)
{
    _struct.header  = 'A';
    _struct.footer  = 'B';
    _struct.command = cmd;
    _struct.data    = data;

    QByteArray ba;
    ba.reserve(8);
    ba.append(char(_struct.header));
    ba.append(char(_struct.command));
    ba.append(reinterpret_cast<const char*>(&_struct.data), 4); // native-endian

    // CRC trên [cmd(1) + data(4)]
    const quint8 *p = reinterpret_cast<const quint8*>(ba.constData()) + 1;
    _struct.crc = Crc_Calulater(const_cast<quint8*>(p), 5);

    ba.append(char(_struct.crc));
    ba.append(char(_struct.footer));
    return _port->Write(ba);
}

QString DeviceControl::GetPortName()
{
    return _portName;
}

void DeviceControl::SetPortName(QString portname)
{
    _portName = portname;
}

bool DeviceControl::isOpen()
{
    return _port->isOpen();
}

quint8 DeviceControl::Crc_Calulater(quint8 *data, int len)
{
    quint8 crc = 0;
    quint8 extract, sum;
    quint8 polynomial = 0x8C;
    qDebug() << "len in Crc_Calulater= " << len << Qt::endl;
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
