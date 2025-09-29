#include "DeviceControl.h"
#include <QDebug>
#include "protocolutils.h"

DeviceControl::DeviceControl(QObject *parent)
    : QObject{parent}
    , _port(this)
{
    connect(&_port, &SerialPort::dataRecevie, this, &DeviceControl::readData);
    connect(&_port, &SerialPort::disconnected, this, &DeviceControl::disconnected);
}

DeviceControl::DeviceControl(const QString &portname, QObject *parent) : DeviceControl(parent)
{
    _portName = portname;
}

DeviceControl::~DeviceControl() {

}

void DeviceControl::readData(QByteArray data)
{
    emit dataReady(data);
}

void DeviceControl::disconnected()
{
    qDebug()<< "DeviceControl::disconnected()";
    _port.Close();
}

bool DeviceControl::Connect()
{
    if (_portName.isEmpty()) {
        qWarning() << "Chưa cấu hình tên cổng serial";
        return false;
    }
    return _port.Connect(_portName);
}

qint64 DeviceControl::SendCommand(quint8 cmd, quint32 data)
{
    return _port.Write(protocol::buildFrame(cmd, data));
}

QString DeviceControl::GetPortName() const
{
    return _portName;
}

void DeviceControl::SetPortName(const QString &portname)
{
    _portName = portname;
}

bool DeviceControl::isOpen() const
{
    return _port.isOpen();
}

