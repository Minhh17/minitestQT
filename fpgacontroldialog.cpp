#include "fpgacontroldialog.h"
#include "ui_fpgacontroldialog.h"

// ==== Protocol: [ 'A' ][ cmd ][ data(4 bytes) ][ crc ][ 'B' ] ====
// data là 4 byte native-endian, CRC-8 poly 0x8C (LSB-first) tính trên [cmd + 4 byte data]
static constexpr quint8 H = 'A';
static constexpr quint8 F = 'B';
static constexpr int  PKT_SZ = 8;

static quint8 crc8_8C(const quint8* data, int len) {
    quint8 crc = 0;
    quint8 extract, sum;
    quint8 polynomial = 0x8C;
    qDebug() << "len in = crc8_8C" << len << Qt::endl;
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

// Tách 1 gói hợp lệ từ đầu buffer (không đổi endian)
static bool tryExtract(QByteArray &buf, quint8 &cmd, quint32 &data) {
    int pos = buf.indexOf(char(H));
    if (pos < 0) { buf.clear(); return false; }
    if (pos > 0)  buf.remove(0, pos);
    if (buf.size() < PKT_SZ) return false;
    if (quint8(buf[7]) != F) { buf.remove(0,1); return false; }

    cmd = quint8(buf[1]);
    memcpy(&data, buf.constData()+2, 4);      // native-endian đúng với phía gửi

    quint8 tmp[5]; tmp[0] = cmd; memcpy(tmp+1, &data, 4);
    quint8 crcCalc = crc8_8C(tmp, 5);
    if (quint8(buf[6]) != crcCalc) { buf.remove(0, PKT_SZ); return false; }

    buf.remove(0, PKT_SZ);
    return true;
}

FpgaControlDialog::FpgaControlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FpgaControlDialog)
    , fpga_device(nullptr)
    , socket_device(nullptr)
{
    ui->setupUi(this);

    // Setup chart
    m_chart = new QChart();
    m_series = new QScatterSeries();
    m_series->setMarkerSize(6.0);
    m_chart->addSeries(m_series);

    m_axX = new QValueAxis(); m_axY = new QValueAxis();
    m_axX->setTitleText("X"); m_axY->setTitleText("Y");
    m_axX->setRange(0, 20); m_axY->setRange(0, 20);
    m_chart->addAxis(m_axX, Qt::AlignBottom);
    m_chart->addAxis(m_axY, Qt::AlignLeft);
    m_series->attachAxis(m_axX);
    m_series->attachAxis(m_axY);

    m_chartView = new QChartView(m_chart);
    m_chartView->setRenderHint(QPainter::Antialiasing);

    auto lay = new QVBoxLayout(ui->plotContainer);
    lay->setContentsMargins(0,0,0,0);
    lay->addWidget(m_chartView);
}

FpgaControlDialog::~FpgaControlDialog()
{
    qDebug()<< "~FpgaControlDialog()";
    delete ui;
}

void FpgaControlDialog::ConvertLO(int f0, int &LO_R3, int &LO_R4)
{
    if((f0>9700) | (f0<9000)){
        printf("error: out of range\n");
    }
    else{
        f0 -=1280;
    }

    double fpd = 50;
    int Ni = (int)(floor(f0/(2*fpd)));
    int Nf = (int)(round(((f0/(2*fpd))-Ni)*pow(2,24)));
    double R3deca = 3*pow(2, 25);//2^25;
    double R3decd = Ni*2;
    double R3dec = R3deca + R3decd;
    //double R3 = dec2hex(R3dec);
    double R4deca = 4*std::pow(2,25);//2^25;
    double R4decd = Nf*2;
    double R4dec = R4deca + R4decd;
    LO_R3 = (quint32)R3dec;
    LO_R4 = (quint32)R4dec;
}

void FpgaControlDialog::SerialPortConnected(DeviceControl *_decevie)
{
    if(fpga_device != nullptr) {
        delete fpga_device;
    }
    fpga_device = _decevie;
    connect(fpga_device, &DeviceControl::dataReady, this, &FpgaControlDialog::ReadData);
    auto isConnected = fpga_device->isOpen();
    if(isConnected) {
        ui->lbl_serial_state->setText("Connected");
    } else {
        ui->lbl_serial_state->setText("Disconnection !!");
    }
}

void FpgaControlDialog::SocketConnected(SocketControl *_decevie)
{
    qDebug() << "new socket";
    if(socket_device != nullptr) {
        delete socket_device;
    }
    socket_device = _decevie;

    connect(socket_device, &SocketControl::dataReady, this, &FpgaControlDialog::ReadData);

    auto isConnected = socket_device->isConnected();
    if(isConnected) {
        ui->lbl_serial_state->setText("Connected");
    }
    else {
        ui->lbl_serial_state->setText("Disconnection !!");
    }
}

void FpgaControlDialog::on_btn_pri_mode_clicked()
{
    int pri_mode = ui->ln_priMode->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_PriMode, pri_mode);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_PriMode, pri_mode);
}

void FpgaControlDialog::on_btn_wf_ctrl_clicked()
{
    int wf_ctrl = ui->ln_wf_ctrl_mt->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_WfCtrl_MT, wf_ctrl);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_WfCtrl_MT, wf_ctrl);
}

void FpgaControlDialog::on_btn_rf_tx_clicked()
{
    // gui 2 lan
    int f0 = ui->ln_rf_tx->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Rf_Tx_R3, f0);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Rf_Tx_R3, f0);
}

void FpgaControlDialog::on_btn_thres_lfm_clicked()
{
    int thres_lfm = ui->ln_Thres_lfm->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Threshold_LFM, thres_lfm);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Threshold_LFM, thres_lfm);
}

void FpgaControlDialog::on_btn_thres_pc_clicked()
{
    int thres_pc = ui->ln_Thres_pc->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Threshold_PC, thres_pc);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Threshold_PC, thres_pc);
}

void FpgaControlDialog::on_btn_loopback_clicked()
{
    int loopback = ui->ln_loopback->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_LoopBack, loopback);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_LoopBack, loopback);
}

void FpgaControlDialog::on_btn_target_range_clicked()
{
    int target_range = ui->ln_target_range->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Target_Range, target_range);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Target_Range, target_range);
}

void FpgaControlDialog::on_btn_pulse1_clicked()
{
    int pulse1 = ui->ln_pulse1_delay->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Pulse1, pulse1);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Pulse1, pulse1);
}

void FpgaControlDialog::on_btn_pulse2_clicked()
{
    int pulse2 = ui->ln_pulse2_delay->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Pulse2, pulse2);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Pulse2, pulse2);
}

void FpgaControlDialog::on_btn_mod_kd_range_clicked()
{
    int mod_kd_range = ui->ln_mod_kd_range->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Mod_KD_Range, mod_kd_range);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Mod_KD_Range, mod_kd_range);
}

void FpgaControlDialog::on_btn_mod_kd_clicked()
{
    int mod_kd = ui->ln_mod_kd_onOff->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Modulation_KD, mod_kd);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Modulation_KD, mod_kd);
}

void FpgaControlDialog::on_btn_att_tx_clicked()
{
    int att = ui->ln_att_tx->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Att_TX, att);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Att_TX, att);
}

void FpgaControlDialog::on_btn_mod_mt_clicked()
{
    int mod_mt = ui->ln_mod_mt->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Modulation_MT, mod_mt);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Modulation_MT, mod_mt);
}

void FpgaControlDialog::on_btn_ratio_mt_clicked()
{
    int ratio_mt = ui->ln_ratio_mt->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Ratio_MT, ratio_mt);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Ratio_MT, ratio_mt);
}

void FpgaControlDialog::on_btn_offset_range_clicked()
{
    int offset_range = ui->ln_offset_range->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Offset_Range, offset_range);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Offset_Range, offset_range);
}

void FpgaControlDialog::on_btn_wf_ctrl_tl_clicked()
{
    int wf_tl = ui->ln_wf_ctrl_tl->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_WfCtrl_TL, wf_tl);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_WfCtrl_TL, wf_tl);
}

void FpgaControlDialog::on_btn_rf_tl_clicked()
{
    // gui 2 lan
    int f0 = ui->ln_rf_tl->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_RF_TL_R3, f0);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_RF_TL_R3, f0);
    // int R3, R4;
    // FpgaControlDialog::ConvertLO(f0, R3, R4);
    // if(fpga_device != nullptr) {
    //     fpga_device->SendCommand(FpgaControlDialog::Idx_RF_TL_R3, R3);
    //     fpga_device->SendCommand(FpgaControlDialog::Idx_RF_TL_R4, R4);
    // }

    // if(socket_device != nullptr) {
    //     socket_device->SendCommand(FpgaControlDialog::Idx_RF_TL_R3, R3);
    //     socket_device->SendCommand(FpgaControlDialog::Idx_RF_TL_R4, R4);
    // }
}

void FpgaControlDialog::on_btn_mod_tl_clicked()
{
    int mod_tl = ui->ln_mod_tl->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Modulation_TL, mod_tl);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Modulation_TL, mod_tl);
}

void FpgaControlDialog::on_btn_tl_range_clicked()
{
    int tl_range = ui->ln_tl_range->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_TL_Range, tl_range);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_TL_Range, tl_range);
}

void FpgaControlDialog::on_btn_att_tl_clicked()
{
    int att_tl = ui->ln_att_tl->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Att_TL, att_tl);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Att_TL, att_tl);
}

void FpgaControlDialog::on_btn_ratio_tl_clicked()
{
    int ratio_tl = ui->ln_ratio_tl->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Ratio_TL, ratio_tl);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Ratio_TL, ratio_tl);
}

void FpgaControlDialog::on_btn_ratio_tl_2_clicked()
{
    int offset_att = ui->ln_offset_att->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Offset_Att, offset_att);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Offset_Att, offset_att);
}

void FpgaControlDialog::ReadData(QByteArray chunk)
{
//    ui->lst_Message->addItem(QString(data));
    m_rx += chunk;
    qDebug()<<"ReadData(QByteArray chunk)" << chunk;

    quint8 cmd; quint32 data;
    qDebug()<<"in here 0" << m_rx.size();
    while (m_rx.size() >= PKT_SZ) {
        qDebug()<<"in here 1";
        if (!tryExtract(m_rx, cmd, data)) {
            if (m_rx.size() < PKT_SZ) break;
            continue;
        }
        // Tách 2 tham số 16-bit: x = high16, y = low16
        quint16 x = quint16((data >> 16) & 0xFFFF);
        quint16 y = quint16(data & 0xFFFF);
        plotPoint(x, y);
        qInfo() << "RX cmd " << int(cmd) << "x=" << x << "y=" << y;
    }
}

void FpgaControlDialog::Disconnect()
{

}

void FpgaControlDialog::on_btn_noise_width_clicked()
{
    int noise_width = ui->ln_noise_width->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Noise_Width, noise_width);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Noise_Width, noise_width);
}

void FpgaControlDialog::on_btn_ratio_noise_clicked()
{
    int ratio_noise = ui->ln_ratio_noise->text().toInt();
    if(fpga_device != nullptr) fpga_device->SendCommand(FpgaControlDialog::Idx_Ratio_Noise, ratio_noise);
    if(socket_device != nullptr) socket_device->SendCommand(FpgaControlDialog::Idx_Ratio_Noise, ratio_noise);
}

void FpgaControlDialog::onSocketReadyRead() {
    auto *sock = qobject_cast<QTcpSocket*>(sender());
    if (!sock) return;
    m_rx += sock->readAll();

    quint8 cmd; quint32 data;
    while (m_rx.size() >= PKT_SZ) {
        if (!tryExtract(m_rx, cmd, data)) {
            if (m_rx.size() < PKT_SZ) break;
            continue;
        }
        // Tách 2 param 16-bit (big-endian: x là high-16, y là low-16)
        quint16 x = quint16((data >> 16) & 0xFFFF);
        quint16 y = quint16(data & 0xFFFF);
        plotPoint(x, y);
    }
}

void FpgaControlDialog::plotPoint(quint16 x, quint16 y) {
    m_series->append(double(x), double(y));
    // Tùy chọn: auto-scale nếu vượt biên
    if (x > m_axX->max()) m_axX->setMax(x);
    if (y > m_axY->max()) m_axY->setMax(y);
    if (x < m_axX->min()) m_axX->setMin(x);
    if (y < m_axY->min()) m_axY->setMin(y);

    // Giới hạn số điểm để không nặng UI
    static const int MAX_POINTS = 500;
    if (m_series->count() > MAX_POINTS) {
        // xóa bớt điểm đầu: QScatterSeries không có pop-front nhanh,
        // cách đơn giản: rebuild nhẹ khi quá ngưỡng
        QVector<QPointF> pts = m_series->pointsVector();
        pts.remove(0, pts.size() - MAX_POINTS);
        m_series->replace(pts);
    }
}

