#include "fpgacontroldialog.h"
#include "ui_fpgacontroldialog.h"

FpgaControlDialog::FpgaControlDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FpgaControlDialog)
    , fpga_decevie(nullptr)
    , socket_decevie(nullptr)
{
    ui->setupUi(this);
}

FpgaControlDialog::~FpgaControlDialog()
{
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

void FpgaControlDialog::SerialPortConnected(DeceviesControl *_decevie)
{
    if(fpga_decevie != nullptr) {
        delete fpga_decevie;
    }
    fpga_decevie = _decevie;
    connect(fpga_decevie, &DeceviesControl::dataReady, this, &FpgaControlDialog::ReadData);
    auto isConnected = fpga_decevie->IsOpen();
    if(isConnected) {
        ui->lbl_serial_state->setText("Connected");
    } else {
        ui->lbl_serial_state->setText("Disconnection !!");
    }
}

void FpgaControlDialog::SocketConneced(SocketControl *_decevie)
{
    qDebug() << "new socket";
    if(socket_decevie != nullptr) {
        delete socket_decevie;
    }
    socket_decevie = _decevie;
    auto isConnected = socket_decevie->isConnected();
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
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_PriMode, pri_mode);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_PriMode, pri_mode);
}


void FpgaControlDialog::on_btn_wf_ctrl_clicked()
{
    int wf_ctrl = ui->ln_wf_ctrl_mt->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_WfCtrl_MT, wf_ctrl);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_WfCtrl_MT, wf_ctrl);
}


void FpgaControlDialog::on_btn_rf_tx_clicked()
{
    // gui 2 lan
    int f0 = ui->ln_rf_tx->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Rf_Tx_R3, f0);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Rf_Tx_R3, f0);
}


void FpgaControlDialog::on_btn_thres_lfm_clicked()
{
    int thres_lfm = ui->ln_Thres_lfm->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Threshold_LFM, thres_lfm);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Threshold_LFM, thres_lfm);
}


void FpgaControlDialog::on_btn_thres_pc_clicked()
{
    int thres_pc = ui->ln_Thres_pc->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Threshold_PC, thres_pc);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Threshold_PC, thres_pc);
}


void FpgaControlDialog::on_btn_loopback_clicked()
{
    int loopback = ui->ln_loopback->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_LoopBack, loopback);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_LoopBack, loopback);
}


void FpgaControlDialog::on_btn_target_range_clicked()
{
    int target_range = ui->ln_target_range->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Target_Range, target_range);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Target_Range, target_range);
}


void FpgaControlDialog::on_btn_pulse1_clicked()
{
    int pulse1 = ui->ln_pulse1_delay->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Pulse1, pulse1);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Pulse1, pulse1);
}


void FpgaControlDialog::on_btn_pulse2_clicked()
{
    int pulse2 = ui->ln_pulse2_delay->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Pulse2, pulse2);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Pulse2, pulse2);
}


void FpgaControlDialog::on_btn_mod_kd_range_clicked()
{
    int mod_kd_range = ui->ln_mod_kd_range->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Mod_KD_Range, mod_kd_range);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Mod_KD_Range, mod_kd_range);
}


void FpgaControlDialog::on_btn_mod_kd_clicked()
{
    int mod_kd = ui->ln_mod_kd_onOff->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Modulation_KD, mod_kd);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Modulation_KD, mod_kd);
}


void FpgaControlDialog::on_btn_att_tx_clicked()
{
    int att = ui->ln_att_tx->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Att_TX, att);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Att_TX, att);
}


void FpgaControlDialog::on_btn_mod_mt_clicked()
{
    int mod_mt = ui->ln_mod_mt->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Modulation_MT, mod_mt);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Modulation_MT, mod_mt);
}


void FpgaControlDialog::on_btn_ratio_mt_clicked()
{
    int ratio_mt = ui->ln_ratio_mt->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Ratio_MT, ratio_mt);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Ratio_MT, ratio_mt);
}


void FpgaControlDialog::on_btn_offset_range_clicked()
{
    int offset_range = ui->ln_offset_range->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Offset_Range, offset_range);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Offset_Range, offset_range);
}


void FpgaControlDialog::on_btn_wf_ctrl_tl_clicked()
{
    int wf_tl = ui->ln_wf_ctrl_tl->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_WfCtrl_TL, wf_tl);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_WfCtrl_TL, wf_tl);
}


void FpgaControlDialog::on_btn_rf_tl_clicked()
{
    // gui 2 lan
    int f0 = ui->ln_rf_tl->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_RF_TL_R3, f0);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_RF_TL_R3, f0);
    // int R3, R4;
    // FpgaControlDialog::ConvertLO(f0, R3, R4);
    // if(fpga_decevie != nullptr) {
    //     fpga_decevie->SendCommand(FpgaControlDialog::Idx_RF_TL_R3, R3);
    //     fpga_decevie->SendCommand(FpgaControlDialog::Idx_RF_TL_R4, R4);
    // }

    // if(socket_decevie != nullptr) {
    //     socket_decevie->SendCommand(FpgaControlDialog::Idx_RF_TL_R3, R3);
    //     socket_decevie->SendCommand(FpgaControlDialog::Idx_RF_TL_R4, R4);
    // }
}


void FpgaControlDialog::on_btn_mod_tl_clicked()
{
    int mod_tl = ui->ln_mod_tl->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Modulation_TL, mod_tl);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Modulation_TL, mod_tl);
}


void FpgaControlDialog::on_btn_tl_range_clicked()
{
    int tl_range = ui->ln_tl_range->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_TL_Range, tl_range);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_TL_Range, tl_range);
}


void FpgaControlDialog::on_btn_att_tl_clicked()
{
    int att_tl = ui->ln_att_tl->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Att_TL, att_tl);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Att_TL, att_tl);
}


void FpgaControlDialog::on_btn_ratio_tl_clicked()
{
    int ratio_tl = ui->ln_ratio_tl->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Ratio_TL, ratio_tl);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Ratio_TL, ratio_tl);
}


void FpgaControlDialog::on_btn_ratio_tl_2_clicked()
{
    int offset_att = ui->ln_offset_att->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Offset_Att, offset_att);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Offset_Att, offset_att);
}

void FpgaControlDialog::ReadData(QByteArray data)
{
//    ui->lst_Message->addItem(QString(data));
}

void FpgaControlDialog::Disconnect()
{

}


void FpgaControlDialog::on_btn_noise_width_clicked()
{
    int noise_width = ui->ln_noise_width->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Noise_Width, noise_width);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Noise_Width, noise_width);
}


void FpgaControlDialog::on_btn_ratio_noise_clicked()
{
    int ratio_noise = ui->ln_ratio_noise->text().toInt();
    if(fpga_decevie != nullptr) fpga_decevie->SendCommand(FpgaControlDialog::Idx_Ratio_Noise, ratio_noise);
    if(socket_decevie != nullptr) socket_decevie->SendCommand(FpgaControlDialog::Idx_Ratio_Noise, ratio_noise);
}

