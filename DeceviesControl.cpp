#include "DeceviesControl.h"

DeceviesControl::DeceviesControl(QObject *parent)
    : QObject{parent}
{

}

DeceviesControl::DeceviesControl(QString portname)
{
    _port = new SerialPort();
    _portName = portname;
    _struct.header = 'A';
    _struct.footer = 'B';
    connect(_port, &SerialPort::dataRecevie, this, &DeceviesControl::readData);
    connect(_port, &SerialPort::disconnected, this, &DeceviesControl::disconnected);
}

DeceviesControl::~DeceviesControl()
{
    delete _port;
}

void DeceviesControl::readData(QByteArray data)
{
    emit dataReady(data);
}

bool DeceviesControl::Connect()
{

    return _port->Connect(_portName);
}

qint64 DeceviesControl::SendCommand(quint8 cmd, quint32 data)
{
    QByteArray ba;
    quint8* buff;
    _struct.command = cmd;
    _struct.data = data;
    ba.append(reinterpret_cast<const char*>(&_struct.header), sizeof(char));
    ba.append(reinterpret_cast<const char*>(&_struct.command), sizeof(char));
    ba.append(reinterpret_cast<const char*>(&_struct.data), sizeof(int));
    buff = reinterpret_cast<quint8*>(ba.data());
    _struct.crc = Crc_Calulater(buff, sizeof(buff) - 2);
    ba.append(reinterpret_cast<const char*>(&_struct.crc), sizeof(char));
    ba.append(reinterpret_cast<const char*>(&_struct.footer), sizeof(char));
//    QByteArray ba(reinterpret_cast<char*>(&_struct), sizeof(CommandStruct));
    return _port->Write(ba);
}

QString DeceviesControl::GetPortName()
{
    return _portName;
}

void DeceviesControl::SetPortName(QString portname)
{
    _portName = portname;
}

bool DeceviesControl::IsOpen()
{
    return _port->IsOpend();
}

quint8 DeceviesControl::Crc_Calulater(quint8 *data, int len)
{
    quint8 crc = 0;
    quint8 extract, sum;
    quint8 polynomial = 0x8C;
    qDebug() << "len = " << len << Qt::endl;
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
