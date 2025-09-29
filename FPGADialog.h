#ifndef FPGADIALOG_H
#define FPGADIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QHash>
#include <QList>
#include <QRandomGenerator>

#include "serialport.h"
#include "commandstruct.h"

namespace Ui {
class FPGADialog;
}

class FPGADialog : public QDialog
{
    Q_OBJECT

public:
    explicit FPGADialog(QWidget *parent = nullptr);
    ~FPGADialog();

signals:
    void onSocketReceive(QByteArray);

private slots:
    void on_btn_connect_clicked();

    void on_btn_Send_clicked();

    void readyRead(QByteArray);

    void onNewTcpConnection();
    void onSocketReadyRead();

    void onSocketDisconnected();

private:
    Ui::FPGADialog *ui;
    SerialPort m_serialPort;
    // QString _portName;

    QTcpServer m_server;
    QList<QTcpSocket*> m_clients;
    QHash<QTcpSocket*, QByteArray> m_socketBuffers;
    QByteArray m_serialBuffer;

};

#endif // FPGADIALOG_H
