#ifndef FPGADIALOG_H
#define FPGADIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QTcpServer>
#include <QTcpSocket>
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

private slots:
    void on_btn_connect_clicked();

    void on_btn_Send_clicked();

    void readyRead(QByteArray);

private:
    Ui::FPGADialog *ui;
    SerialPort *_port;
    // QString _portName;
    CommandStruct _struct;
};

#endif // FPGADIALOG_H
