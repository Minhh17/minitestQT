#include "serialport.h"
#include <QDebug>

SerialPort::SerialPort(QObject *parent)
    : QObject{parent}
    , m_serialport(this)
{
    connect(&m_serialport, &QSerialPort::readyRead, this, &SerialPort::dataReady);
    connect(&m_serialport, &QSerialPort::errorOccurred, this, [this](QSerialPort::SerialPortError error) {
        if (error == QSerialPort::ResourceError) {
            emit disconnected();
            Close();
        }
    });
}

bool SerialPort::Connect(const QString &portname)
{
    if (m_serialport.isOpen()) {
        m_serialport.close();
    }

    m_serialport.setBaudRate(QSerialPort::Baud115200);
    m_serialport.setDataBits(QSerialPort::Data8);
    m_serialport.setParity(QSerialPort::NoParity);
    m_serialport.setStopBits(QSerialPort::OneStop);
    m_serialport.setPortName(portname);

    if (!m_serialport.open(QIODevice::ReadWrite)) {
        qWarning() << "Không thể mở cổng" << portname << ":" << m_serialport.errorString();
        return false;
    }
    return true;
}

bool SerialPort::Close()
{
    if (!m_serialport.isOpen()) {
        return true;
    }

    m_serialport.close();
    return !m_serialport.isOpen();
}

qint64 SerialPort::Write(const QByteArray &data)
{
    if(!m_serialport.isOpen()) {
        return -1;
    }
    return m_serialport.write(data);
}

bool SerialPort::isOpen() const
{
    return m_serialport.isOpen();
}

SerialPort::~SerialPort()
{
    Close();
}

void SerialPort::dataReady()
{
    if (m_serialport.isOpen()) {
        const QByteArray data = m_serialport.readAll();
        if (!data.isEmpty()) {
            emit dataRecevie(data);
        }
    }
}
