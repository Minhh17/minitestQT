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

    bool Connect(const QString &portname);
    bool Close();

    qint64 Write(const QByteArray &data);

    bool isOpen() const;

    ~SerialPort() override;
private:
    QSerialPort m_serialport;

private slots:
    void dataReady();

signals:
    void dataRecevie(QByteArray data);
    void disconnected();
};

#endif // SERIALPORT_H
