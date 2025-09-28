#ifndef FPGADIALOG_H
#define FPGADIALOG_H

#include <QDialog>
#include "serialport.h"
#include <QMessageBox>
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
    SerialPort _port;
};

#endif // FPGADIALOG_H
