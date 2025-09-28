#include "FPGADialog.h"
#include "ui_FPGADialog.h"
#include <QSerialPortInfo>

// FPGA Device

FPGADialog::FPGADialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FPGADialog)
{
    qDebug() << "Available Serial Ports:";
    for (const QSerialPortInfo &info : QSerialPortInfo::availablePorts()) {
        qDebug() << "  Port Name:" << info.portName();
        qDebug() << "  System Location:" << info.systemLocation();
        qDebug() << "  Description:" << info.description();
        qDebug() << "  Manufacturer:" << info.manufacturer();
        qDebug() << "  Vendor Identifier:" << info.vendorIdentifier();
        qDebug() << "  Product Identifier:" << info.productIdentifier();
        // qDebug() << "  Is Busy:" << info.isBusy();
        qDebug() << "-----------------------------------";
    }
    ui->setupUi(this);
    connect(&_port, &SerialPort::dataRecevie, this, &FPGADialog::readyRead);
}

FPGADialog::~FPGADialog()
{
    qDebug()<< "~FPGADialog()";
    delete ui;
}

void FPGADialog::on_btn_connect_clicked()
{
    auto isConnect = _port.Connect("ttyV1");
    if(!isConnect) {
        QMessageBox::critical(this, "Error", "Connection Failed!!");
    }
    else {
        QMessageBox::information(this, "Reuslt", "Serial Port Opened");
    }
}

void FPGADialog::on_btn_Send_clicked()
{
    _port.Write(ui->ln_Message->text().toUtf8());
}

void FPGADialog::readyRead(QByteArray data)
{
    ui->lst_Message->addItem("Command Recevied...");
    CommandStruct command;
    memcpy(reinterpret_cast<char* >(&command), data.data(), data.size());
    if(command.command == 0) {
        ui->lst_Message->addItem("Idx_PriMode");
        ui->lbl_State->setNum(int(command.data));
    }
    else if (command.command == 1) {
        ui->lst_Message->addItem("Idx_PriMode");
        ui->lbl_decevie_state->setNum(double(command.data));
    }
    else if (command.command == 2) {
        ui->lbl_Speed->setNum(double(command.data));
    }
    else if (command.command == 3) {
        ui->lbl_decevie_speed->setNum(double(command.data));
    }
}

