#include "FPGADialog.h"
#include "ui_FPGADialog.h"
#include "serialport.h"
#include "protocolutils.h"
#include <QDebug>
#include <string>

// FPGA Simu Device

FPGADialog::FPGADialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FPGADialog)
{
    ui->setupUi(this);
    connect(&m_serialPort, &SerialPort::dataRecevie, this, &FPGADialog::readyRead);
    connect(&m_server, &QTcpServer::newConnection, this, &FPGADialog::onNewTcpConnection);

    const quint16 port = 12345;
    if (m_server.listen(QHostAddress::Any, port)) {
        ui->lst_Message->addItem(tr("Listening on TCP port %1").arg(port));
        qInfo() << "Server listening on" << m_server.serverAddress().toString()
                << ":" << m_server.serverPort();
    } else {
        ui->lst_Message->addItem(tr("Server failed: %1").arg(m_server.errorString()));
        qCritical() << "Server failed to listen on port" << port
                    << ":" << m_server.errorString();
        // return false;
    }
}

FPGADialog::~FPGADialog()
{
    qDebug()<< "~FPGADialog()";
    delete ui;
}

void FPGADialog::on_btn_connect_clicked()
{
    const bool isConnect = m_serialPort.Connect("ttyV1");
    if(!isConnect) {
        QMessageBox::critical(this, "Error", "Connection Failed!!");
    }
    else {
        QMessageBox::information(this, "Reuslt", "Serial Port Opened");
    }
}

void FPGADialog::on_btn_Send_clicked()
{
    // Thêm chống lỗi cho Serial
    QByteArray payload = ui->ln_Message->text().toUtf8();
    if (m_serialPort.isOpen()) {
        m_serialPort.Write(payload);
    }

    for (QTcpSocket *socket : m_clients) {
        if (socket && socket->state() == QAbstractSocket::ConnectedState) {
            socket->write(payload);
            socket->flush();
        }
    }
}

void FPGADialog::readyRead(QByteArray data)
{
    m_serialBuffer.append(data);

    ui->lst_Message->addItem("Command Recevied...");

    CommandStruct frame {};
    while (protocol::tryExtractFrame(m_serialBuffer, frame))
    {
        const quint8 cmd = frame.command;
        const quint32 data = frame.data;
        if(cmd == 0) {
            ui->lst_Message->addItem(QString("Idx_PriMode: %1").arg(data));
            ui->lbl_State->setNum(int(cmd));
        }
        else if (cmd == 1) {
            ui->lst_Message->addItem(QString("Idx_WfCtrl_MT: %1").arg(data));
            ui->lbl_decevie_state->setNum(double(frame.data));
        }
        else if (cmd == 2) {
            // ui->lst_Message->addItem("Idx_Rf_Tx_R3");
            ui->lst_Message->addItem(QString("Idx_Rf_Tx_R3: %1").arg(data));
            ui->lbl_Speed->setNum(double(frame.data));
        }
        else if (cmd == 3) {
            ui->lbl_decevie_speed->setNum(double(frame.data));
        }

        const quint16 value1 = QRandomGenerator::global()->bounded(0x10000); // 16 bit ngẫu nhiên
        const quint16 value2 = QRandomGenerator::global()->bounded(0x10000);
        const quint32 responseData = (static_cast<quint32>(value1) << 16) | value2;

        const QByteArray response = protocol::buildFrame(cmd, responseData);

        m_serialPort.Write(response);

        qInfo() << "Received cmd:" << cmd << "data:" << frame.data
                << "Responded with val1:" << value1 << "val2:" << value2;
    }
}

void FPGADialog::onSocketReadyRead()
{
    auto *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket)
        return;

    QByteArray &buffer = m_socketBuffers[socket];
    buffer.append(socket->readAll());
    qInfo() << "Socket raw data:" << buffer.toHex() << " sizeof(CommandStruct)"<< sizeof(CommandStruct);

    ui->lst_Message->addItem(tr("Socket command received from %1:%2")
                                 .arg(socket->peerAddress().toString())
                                 .arg(socket->peerPort()));

    CommandStruct frame {};
    while (protocol::tryExtractFrame(buffer, frame))
    {
        const quint8 cmd = frame.command;
        const quint32 data = frame.data;

        if(cmd == 0) {
            ui->lst_Message->addItem(QString("Idx_PriMode: %1").arg(data));
            ui->lbl_State->setNum(int(cmd));
        }
        else if (cmd == 1) {
            // ui->lst_Message->addItem("Idx_WfCtrl_MT");
            ui->lst_Message->addItem(QString("Idx_WfCtrl_MT: %1").arg(data));
            ui->lbl_decevie_state->setNum(double(frame.data));
        }
        else if (cmd == 2) {
            // ui->lst_Message->addItem("Idx_Rf_Tx_R3");
            ui->lst_Message->addItem(QString("Idx_Rf_Tx_R3: %1").arg(data));
            ui->lbl_Speed->setNum(double(frame.data));
        }
        else if (cmd == 3) {
            ui->lbl_decevie_speed->setNum(double(frame.data));
        }

        const quint16 value1 = QRandomGenerator::global()->bounded(0x10000);
        const quint16 value2 = QRandomGenerator::global()->bounded(0x10000);
        const quint32 responseData = (static_cast<quint32>(value1) << 16) | value2;

        const QByteArray response = protocol::buildFrame(cmd, responseData);

        socket->write(response);
        socket->flush();

        qInfo() << "Received cmd:" << cmd << "data:" << frame.data
                << "Responded with val1:" << value1 << "val2:" << value2;

    }
}

void FPGADialog::onNewTcpConnection()
{
    while (m_server.hasPendingConnections()) {
        QTcpSocket *socket = m_server.nextPendingConnection();
        if (!socket)
            continue;

        m_clients.append(socket);
        m_socketBuffers.insert(socket, QByteArray());

        ui->lst_Message->addItem(tr("Socket client connected: %1:%2")
                                     .arg(socket->peerAddress().toString())
                                     .arg(socket->peerPort()));

        connect(socket, &QTcpSocket::readyRead, this, &FPGADialog::onSocketReadyRead);
        connect(socket, &QTcpSocket::disconnected, this, &FPGADialog::onSocketDisconnected);
    }
}

void FPGADialog::onSocketDisconnected()
{
    auto *socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket)
        return;

    ui->lst_Message->addItem(tr("Socket client disconnected"));
    m_socketBuffers.remove(socket);
    m_clients.removeAll(socket);
    socket->deleteLater();
}



