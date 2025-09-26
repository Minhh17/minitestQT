#ifndef DECEVIEDIALOG_H
#define DECEVIEDIALOG_H

#include <QDialog>
#include "serialport.h"
#include <QMessageBox>
#include "commandstruct.h"

namespace Ui {
class DecevieDialog;
}

class DecevieDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DecevieDialog(QWidget *parent = nullptr);
    ~DecevieDialog();

private slots:
    void on_btn_connect_clicked();

    void on_btn_Send_clicked();

    void readyRead(QByteArray);

private:
    Ui::DecevieDialog *ui;
    SerialPort _port;
};

#endif // DECEVIEDIALOG_H
