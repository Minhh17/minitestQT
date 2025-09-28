#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
// , _port(nullptr)
{
    ui->setupUi(this);
    LoadPort();
    //connect(&_port, &SerialPort::dataRecevie, this, &MainWindow::readData);
    connect(this, &MainWindow::connected, &fpga_dlg, &FpgaControlDialog::SerialPortConnected);
    connect(this, &MainWindow::socketconnected, &fpga_dlg, &FpgaControlDialog::SocketConneced);
}

MainWindow::~MainWindow()
{
    qDebug()<< "~MainWindow()";
    delete ui;
}

void MainWindow::LoadPort()
{
    foreach (auto &port_, QSerialPortInfo::availablePorts()) {
        ui->cmb_Name->addItem(port_.portName());
    }
    //ui->cmb_Name->addItem("ttyV0");
}

void MainWindow::setDeviceContoller()
{
    if(_socketcontroller != nullptr) {
        connect(_socketcontroller, &SocketControl::connected, this, &MainWindow::device_connected);
        connect(_socketcontroller, &SocketControl::disconnected, this, &MainWindow::device_disconnected);
        connect(_socketcontroller, &SocketControl::stateChanged, this, &MainWindow::device_stateChanged);
        connect(_socketcontroller, &SocketControl::errorOccurred, this, &MainWindow::device_errorOccurred);
        connect(_socketcontroller, &SocketControl::dataReady, this, &MainWindow::device_dataReady);
    }
    else {
        qDebug() << "socket is nullptr";
    }
}

void MainWindow::on_btn_Open_clicked()
{
    // _decevie = new DeviceControl(ui->cmb_Name->currentText());
    _decevie = new DeviceControl("ttyV0");
    auto isConnect = _decevie->Connect();
    qDebug() << _decevie->isOpen();
    if(!isConnect) {
        QMessageBox::critical(this, "Error", "Connection Failed!!");
    }
    else {
        QMessageBox::information(this, "Reuslt", "Serial Port Opened");
        emit connected(_decevie);
        fpga_dlg.show();
        //        test_dlg.show();
        MainWindow::close();
    }
}

void MainWindow::on_btn_connect_clicked()
{
    _socketcontroller = new SocketControl(ui->ln_Ip_Addr->text(), ui->spn_port->value());
    setDeviceContoller();
}

void MainWindow::device_connected()
{
    qDebug() << "Connect to Decevie";
    auto isConnect = _socketcontroller->isConnected();
    if(!isConnect) {
        QMessageBox::critical(this, "Error", "Connection Failed!!");
    }
    else {
        QMessageBox::information(this, "Reuslt", "Socket connected");
        emit socketconnected(_socketcontroller);
        fpga_dlg.show();
        MainWindow::close();
    }
}

void MainWindow::device_disconnected()
{
    qDebug() << "Disconnected from Device";
}

void MainWindow::device_stateChanged(QAbstractSocket::SocketState state)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState >();
    qDebug() << metaEnum.valueToKey(state);
}

void MainWindow::device_errorOccurred(QAbstractSocket::SocketError error)
{
    QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState >();
    qDebug() << metaEnum.valueToKey(error);
}

void MainWindow::device_dataReady(QByteArray data)
{

}

