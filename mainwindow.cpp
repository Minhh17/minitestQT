#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ui->setupUi(this);
    LoadPort();
    //connect(&_port, &SerialPort::dataRecevie, this, &MainWindow::readData);
    connect(this, &MainWindow::connected, &fpga_dlg, &FpgaControlDialog::SerialPortConnected);
    connect(this, &MainWindow::socketconnected, &fpga_dlg, &FpgaControlDialog::SocketConnected);
}

MainWindow::~MainWindow()
{
    qDebug()<< "~MainWindow()";
    delete ui;
}

void MainWindow::LoadPort()
{
    ui->cmb_Name->clear(); //
    const auto ports = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : ports) {
        ui->cmb_Name->addItem(info.portName());
    }
    ui->cmb_Name->addItem("ttyV0");  // Cổng ảo dùng socat Qt tool ko detect được nên tự thêm tên vô
}

void MainWindow::setDeviceContoller()
{
    if(_socketcontroller) {
        auto *controller = _socketcontroller.get();
        connect(controller, &SocketControl::connected, this, &MainWindow::device_connected);
        connect(controller, &SocketControl::disconnected, this, &MainWindow::device_disconnected);
        connect(controller, &SocketControl::stateChanged, this, &MainWindow::device_stateChanged);
        connect(controller, &SocketControl::errorOccurred, this, &MainWindow::device_errorOccurred);
        connect(controller, &SocketControl::dataReady, this, &MainWindow::device_dataReady);
    }
    else {
        qDebug() << "socket is nullptr";
    }
}

void MainWindow::on_btn_Open_clicked()
{
    const QString portName = ui->cmb_Name->currentText();
    _device = std::make_unique<DeviceControl>(portName);

    const bool isConnect = _device->Connect();

    if(!isConnect) {
        _device.reset();
        QMessageBox::critical(this, "Error", "Connection Failed!!");
    }
    else {
        QMessageBox::information(this, "Reuslt", "Serial Port Opened");
        emit connected(_device.get());
        fpga_dlg.show();
        // test_dlg.show();
        // MainWindow::close();
    }
}

void MainWindow::on_btn_connect_clicked()
{
    // _socketcontroller = new SocketControl(ui->ln_Ip_Addr->text(), ui->spn_port->value());
    _socketcontroller = std::make_unique<SocketControl>(ui->ln_Ip_Addr->text(), ui->spn_port->value());
    setDeviceContoller();
}

void MainWindow::device_connected()
{
    qDebug() << "Connect to Decevie";
    const bool isConnect = _socketcontroller && _socketcontroller->isConnected();
    if(!isConnect) {
        QMessageBox::critical(this, "Error", "Connection Failed!!");
    }
    else {
        QMessageBox::information(this, "Reuslt", "Socket connected");
        emit socketconnected(_socketcontroller.get());
        fpga_dlg.show();
        //MainWindow::close();
        close();
    }
}

void MainWindow::device_disconnected()
{
    qDebug() << "Disconnected from Device";
}

void MainWindow::device_stateChanged(QAbstractSocket::SocketState state)
{
    const QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState>();
    qDebug() << metaEnum.valueToKey(state);
}

void MainWindow::device_errorOccurred(QAbstractSocket::SocketError error)
{
    const QMetaEnum metaEnum = QMetaEnum::fromType<QAbstractSocket::SocketState >();
    qDebug() << metaEnum.valueToKey(error);
}

void MainWindow::device_dataReady(QByteArray data)
{
    qDebug() << "Socket data - MainWindow::device_dataReady" << data.toHex();
}

