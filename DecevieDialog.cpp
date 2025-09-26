#include "DecevieDialog.h"
#include "ui_DecevieDialog.h"

DecevieDialog::DecevieDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DecevieDialog)
{
    ui->setupUi(this);
    connect(&_port, &SerialPort::dataRecevie, this, &DecevieDialog::readyRead);
}

DecevieDialog::~DecevieDialog()
{
    delete ui;
}

void DecevieDialog::on_btn_connect_clicked()
{
    auto isConnect = _port.Connect("COM2");
    if(!isConnect) {
        QMessageBox::critical(this, "Error", "Connection Failed!!");
    }
    else {
        QMessageBox::information(this, "Reuslt", "Serial Port Opened");
    }
}


void DecevieDialog::on_btn_Send_clicked()
{
    _port.Write(ui->ln_Message->text().toUtf8());
}

void DecevieDialog::readyRead(QByteArray data)
{
    ui->lst_Message->addItem("Command Recevied...");
    CommandStruct command;
    memcpy(reinterpret_cast<char* >(&command), data.data(), data.size());
    if(command.command == 0) {
//        ui->lbl_State->setNum(command.data);
    }
    else if (command.command == 1) {
//        ui->lbl_decevie_state->setNum(command.data);
    }
    else if (command.command == 2) {
//        ui->lbl_Speed->setNum(command.data);
    }
    else if (command.command == 3) {
//        ui->lbl_decevie_speed->setNum(command.data);
    }
}

