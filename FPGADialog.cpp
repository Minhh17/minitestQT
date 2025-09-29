#include "FPGADialog.h"
#include "ui_FPGADialog.h"
#include "serialport.h"
#include <QSerialPortInfo>

// FPGA Device

static quint8 Crc_Calulater(quint8 *data, int len)
{
    quint8 crc = 0;
    quint8 extract, sum;
    quint8 polynomial = 0x8C;
    qDebug() << "len = " << len << Qt::endl;
    for(int i = 0; i < len; i++) {
        extract = *data;
        for(int j = 8; j > 0; j--) {
            sum = (quint8)((crc ^ extract) & 0x01);
            crc >>= 1;
            if(sum != 0)
                crc ^= polynomial;
            extract >>= 1;
        }
        data++;
    }
    return crc;
}

FPGADialog::FPGADialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FPGADialog)
{
    _port = new SerialPort();
    // _portName = "ttyV1";
    _struct.header = 'A';
    _struct.footer = 'B';
    connect(_port, &SerialPort::dataRecevie, this, &FPGADialog::readyRead);
    ui->setupUi(this);
}

FPGADialog::~FPGADialog()
{
    qDebug()<< "~FPGADialog()";
    delete ui;
}

void FPGADialog::on_btn_connect_clicked()
{
    auto isConnect = _port->Connect("ttyV1");
    if(!isConnect) {
        QMessageBox::critical(this, "Error", "Connection Failed!!");
    }
    else {
        QMessageBox::information(this, "Reuslt", "Serial Port Opened");
    }
}

void FPGADialog::on_btn_Send_clicked()
{
    _port->Write(ui->ln_Message->text().toUtf8());
}

void FPGADialog::readyRead(QByteArray data)
{
    static QByteArray buffer;
    buffer.append(data);
    qInfo() << "Raw data:" << buffer.toHex() << " sizeof(CommandStruct)"<< sizeof(CommandStruct);

    ui->lst_Message->addItem("Command Recevied...");
    // Duyệt buffer tìm gói tin có header 'A' và footer 'B'
    while (buffer.size() >= sizeof(CommandStruct))
    {
        // Tìm header 'A'
        int headerIndex = buffer.indexOf('A');
        if (headerIndex < 0)
        {
            buffer.clear(); // ko tìm thấy header, xóa buffer
            break;
        }

        // Xóa dữ liệu trước header
        if (headerIndex > 0)
            buffer.remove(0, headerIndex);

        if (buffer.size() < sizeof(CommandStruct))
            break; // chưa đủ dữ liệu

        // Kiểm tra footer
        if (buffer.at(sizeof(CommandStruct) - 1) != 'B')
        {
            // footer sai, loại bỏ header này và tìm lại
            buffer.remove(0, 1);
            continue;
        }

        // Giải mã gói tin
        CommandStruct recvCmd;
        memcpy(&recvCmd, buffer.constData(), sizeof(CommandStruct));

        // Tạo buffer tạm tính CRC
        quint8 crcBuf[5];
        memcpy(crcBuf, &recvCmd.command, 1);
        memcpy(crcBuf + 1, &recvCmd.data, 4);

        quint8 crcCalc = Crc_Calulater(crcBuf, 5);

        if (crcCalc != recvCmd.crc)
        {
            // CRC sai, loại gói tin
            qWarning() << "CRC check failed";
            buffer.remove(0, 1);
            continue;
        }

        // Đã nhận đúng gói, xử lý dữ liệu
        quint8 cmd = recvCmd.command;
        if(cmd == 0) {
            ui->lst_Message->addItem("Idx_PriMode");
            ui->lbl_State->setNum(int(cmd));
        }
        else if (cmd == 1) {
            ui->lst_Message->addItem("Idx_WfCtrl_MT");
            ui->lbl_decevie_state->setNum(double(recvCmd.data));
        }
        else if (cmd == 2) {
            ui->lst_Message->addItem("Idx_Rf_Tx_R3");
            ui->lbl_Speed->setNum(double(recvCmd.data));
        }
        else if (cmd == 3) {
            ui->lbl_decevie_speed->setNum(double(recvCmd.data));
        }

        // Chuẩn bị gói phản hồi
        quint16 value1 = QRandomGenerator::global()->bounded(0x10000); // 16 bit ngẫu nhiên
        quint16 value2 = QRandomGenerator::global()->bounded(0x10000);
        quint32 responseData = (static_cast<quint32>(value1) << 16) | value2;

        CommandStruct responseCmd;
        responseCmd.header = 'A';
        responseCmd.command = cmd;
        responseCmd.data = responseData;
        QByteArray crcArray;
        crcArray.append(char(responseCmd.command));
        crcArray.append(reinterpret_cast<const char*>(&responseCmd.data), 4);
        responseCmd.crc = Crc_Calulater(reinterpret_cast<quint8*>(crcArray.data()), crcArray.size());
        responseCmd.footer = 'B';

        QByteArray sendBa;
        sendBa.append(char(responseCmd.header));
        sendBa.append(char(responseCmd.command));
        sendBa.append(reinterpret_cast<const char*>(&responseCmd.data), 4);
        sendBa.append(char(responseCmd.crc));
        sendBa.append(char(responseCmd.footer));

        _port->Write(sendBa);
        // senderSocket->write(sendBa);
        // senderSocket->flush();

        qInfo() << "Received cmd:" << cmd << "data:" << recvCmd.data
                << "Responded with val1:" << value1 << "val2:" << value2;

        // Xóa gói đã xử lý
        buffer.remove(0, sizeof(CommandStruct));
    }
}


