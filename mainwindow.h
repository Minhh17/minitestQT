#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSerialPortInfo>
#include <QString>
#include "serialport.h"
#include <fpgacontroldialog.h>
#include <FPGADialog.h>
#include <DeviceControl.h>
#include "socketcontrol.h"
#include <QMetaEnum>
#include <memory>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void LoadPort();
    void setDeviceContoller();

private slots:
    void on_btn_Open_clicked();

    void on_btn_connect_clicked();

    // slots of socket
    void device_connected();
    void device_disconnected();
    void device_stateChanged(QAbstractSocket::SocketState);
    void device_errorOccurred(QAbstractSocket::SocketError);
    void device_dataReady(QByteArray data);

signals:
    void connected(DeviceControl*);
    void socketconnected(SocketControl*);

private:
    Ui::MainWindow *ui;
    // DeviceControl *_device;
    std::unique_ptr<DeviceControl> _device;
    // SerialPort *_port;
    FpgaControlDialog fpga_dlg;
    // FPGADialog test_dlg;
    // SocketControl *_socketcontroller;
    std::unique_ptr<SocketControl> _socketcontroller;

};
#endif // MAINWINDOW_H
