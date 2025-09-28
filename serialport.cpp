#include "serialport.h"

SerialPort::SerialPort(QObject *parent)
    : QObject{parent}
    , _serialport(nullptr)
{

}

bool SerialPort::Connect(QString portname)
{
    if(_serialport != nullptr) {
        _serialport->close();
        delete _serialport;
    }
    _serialport = new QSerialPort(this);
    _serialport->setBaudRate(QSerialPort::Baud115200);
    _serialport->setDataBits(QSerialPort::Data8);
    _serialport->setParity(QSerialPort::NoParity);
    _serialport->setStopBits(QSerialPort::OneStop);
    _serialport->setPortName(portname);

    if(_serialport->open(QIODevice::ReadWrite)) {
        connect(_serialport, &QSerialPort::readyRead, this, &SerialPort::dataReady);
//        connect(_serialport, &QSerialPort::disconnect, this, &SerialPort::Disconnect);
    }
    return _serialport->isOpen();
}

bool SerialPort::Close()
{
    if(_serialport != nullptr) {
        _serialport->close();
        delete _serialport;
    }
}

qint64 SerialPort::Write(QByteArray data)
{
    if(!_serialport->isOpen()) {
        return -1;
    }
    return _serialport->write(data);
}

bool SerialPort::isOpen()
{
    return _serialport->isOpen();
}

SerialPort::~SerialPort()
{
    if(_serialport != nullptr) {
        qDebug()<< "~SerialPort()";
        _serialport->close();
        delete _serialport;
    }
}

void SerialPort::dataReady()
{
    if(_serialport->isOpen()) {
        auto data = _serialport->readAll();
        emit dataRecevie(data);
    }
}

void SerialPort::Disconnect()
{
    if(_serialport->isOpen()) {
        _serialport->close();
        emit disconnected();
    }
}
