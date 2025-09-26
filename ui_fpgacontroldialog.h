/********************************************************************************
** Form generated from reading UI file 'fpgacontroldialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FPGACONTROLDIALOG_H
#define UI_FPGACONTROLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_FpgaControlDialog
{
public:
    QLabel *label;
    QLineEdit *ln_priMode;
    QPushButton *btn_pri_mode;
    QGroupBox *groupBox;
    QLabel *label_17;
    QPushButton *btn_rf_tl;
    QLineEdit *ln_rf_tl;
    QLabel *label_20;
    QLineEdit *ln_mod_tl;
    QPushButton *btn_mod_tl;
    QPushButton *btn_wf_ctrl_tl;
    QLabel *label_18;
    QLineEdit *ln_wf_ctrl_tl;
    QPushButton *btn_tl_range;
    QLabel *label_19;
    QLineEdit *ln_tl_range;
    QLabel *label_11;
    QLineEdit *ln_ratio_tl;
    QPushButton *btn_ratio_tl;
    QPushButton *btn_att_tl;
    QLabel *label_10;
    QLineEdit *ln_att_tl;
    QLabel *label_22;
    QLineEdit *ln_offset_att;
    QPushButton *btn_ratio_tl_2;
    QPushButton *btn_noise_width;
    QLineEdit *ln_noise_width;
    QLabel *label_23;
    QPushButton *btn_ratio_noise;
    QLineEdit *ln_ratio_noise;
    QLabel *label_24;
    QLabel *lbl_serial_state;
    QLabel *label_2;
    QLineEdit *ln_wf_ctrl_mt;
    QPushButton *btn_wf_ctrl;
    QPushButton *btn_rf_tx;
    QLineEdit *ln_rf_tx;
    QLabel *label_3;
    QLineEdit *ln_att_tx;
    QPushButton *btn_att_tx;
    QLabel *label_15;
    QLabel *label_14;
    QLineEdit *ln_pulse2_delay;
    QPushButton *btn_pulse2;
    QLabel *label_8;
    QLineEdit *ln_loopback;
    QPushButton *btn_loopback;
    QLabel *label_9;
    QLineEdit *ln_ratio_mt;
    QPushButton *btn_ratio_mt;
    QLineEdit *ln_target_range;
    QLabel *label_5;
    QPushButton *btn_target_range;
    QLabel *label_12;
    QLineEdit *ln_mod_kd_onOff;
    QPushButton *btn_mod_kd;
    QLabel *label_16;
    QPushButton *btn_mod_kd_range;
    QLineEdit *ln_mod_kd_range;
    QPushButton *btn_pulse1;
    QLabel *label_7;
    QLineEdit *ln_pulse1_delay;
    QLabel *label_13;
    QLineEdit *ln_mod_mt;
    QPushButton *btn_mod_mt;
    QLabel *label_6;
    QLineEdit *ln_Thres_pc;
    QPushButton *btn_thres_pc;
    QLabel *label_4;
    QLineEdit *ln_Thres_lfm;
    QPushButton *btn_thres_lfm;
    QPushButton *btn_offset_range;
    QLabel *label_21;
    QLineEdit *ln_offset_range;

    void setupUi(QDialog *FpgaControlDialog)
    {
        if (FpgaControlDialog->objectName().isEmpty())
            FpgaControlDialog->setObjectName("FpgaControlDialog");
        FpgaControlDialog->resize(800, 489);
        label = new QLabel(FpgaControlDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(41, 31, 81, 16));
        ln_priMode = new QLineEdit(FpgaControlDialog);
        ln_priMode->setObjectName("ln_priMode");
        ln_priMode->setGeometry(QRect(150, 30, 108, 24));
        btn_pri_mode = new QPushButton(FpgaControlDialog);
        btn_pri_mode->setObjectName("btn_pri_mode");
        btn_pri_mode->setGeometry(QRect(300, 31, 80, 24));
        groupBox = new QGroupBox(FpgaControlDialog);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(410, 10, 371, 321));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName("label_17");
        label_17->setGeometry(QRect(11, 71, 81, 16));
        btn_rf_tl = new QPushButton(groupBox);
        btn_rf_tl->setObjectName("btn_rf_tl");
        btn_rf_tl->setGeometry(QRect(270, 71, 80, 24));
        ln_rf_tl = new QLineEdit(groupBox);
        ln_rf_tl->setObjectName("ln_rf_tl");
        ln_rf_tl->setGeometry(QRect(120, 71, 108, 24));
        label_20 = new QLabel(groupBox);
        label_20->setObjectName("label_20");
        label_20->setGeometry(QRect(11, 101, 81, 16));
        ln_mod_tl = new QLineEdit(groupBox);
        ln_mod_tl->setObjectName("ln_mod_tl");
        ln_mod_tl->setGeometry(QRect(120, 101, 108, 24));
        btn_mod_tl = new QPushButton(groupBox);
        btn_mod_tl->setObjectName("btn_mod_tl");
        btn_mod_tl->setGeometry(QRect(270, 101, 80, 24));
        btn_wf_ctrl_tl = new QPushButton(groupBox);
        btn_wf_ctrl_tl->setObjectName("btn_wf_ctrl_tl");
        btn_wf_ctrl_tl->setGeometry(QRect(270, 41, 80, 24));
        label_18 = new QLabel(groupBox);
        label_18->setObjectName("label_18");
        label_18->setGeometry(QRect(11, 41, 91, 16));
        ln_wf_ctrl_tl = new QLineEdit(groupBox);
        ln_wf_ctrl_tl->setObjectName("ln_wf_ctrl_tl");
        ln_wf_ctrl_tl->setGeometry(QRect(120, 41, 108, 24));
        btn_tl_range = new QPushButton(groupBox);
        btn_tl_range->setObjectName("btn_tl_range");
        btn_tl_range->setGeometry(QRect(270, 131, 80, 24));
        label_19 = new QLabel(groupBox);
        label_19->setObjectName("label_19");
        label_19->setGeometry(QRect(11, 131, 91, 16));
        ln_tl_range = new QLineEdit(groupBox);
        ln_tl_range->setObjectName("ln_tl_range");
        ln_tl_range->setGeometry(QRect(120, 131, 108, 24));
        label_11 = new QLabel(groupBox);
        label_11->setObjectName("label_11");
        label_11->setGeometry(QRect(11, 191, 91, 16));
        ln_ratio_tl = new QLineEdit(groupBox);
        ln_ratio_tl->setObjectName("ln_ratio_tl");
        ln_ratio_tl->setGeometry(QRect(120, 191, 108, 24));
        btn_ratio_tl = new QPushButton(groupBox);
        btn_ratio_tl->setObjectName("btn_ratio_tl");
        btn_ratio_tl->setGeometry(QRect(270, 191, 80, 24));
        btn_att_tl = new QPushButton(groupBox);
        btn_att_tl->setObjectName("btn_att_tl");
        btn_att_tl->setGeometry(QRect(270, 161, 80, 24));
        label_10 = new QLabel(groupBox);
        label_10->setObjectName("label_10");
        label_10->setGeometry(QRect(11, 161, 91, 16));
        ln_att_tl = new QLineEdit(groupBox);
        ln_att_tl->setObjectName("ln_att_tl");
        ln_att_tl->setGeometry(QRect(120, 161, 108, 24));
        label_22 = new QLabel(groupBox);
        label_22->setObjectName("label_22");
        label_22->setGeometry(QRect(11, 220, 91, 16));
        ln_offset_att = new QLineEdit(groupBox);
        ln_offset_att->setObjectName("ln_offset_att");
        ln_offset_att->setGeometry(QRect(120, 220, 108, 24));
        btn_ratio_tl_2 = new QPushButton(groupBox);
        btn_ratio_tl_2->setObjectName("btn_ratio_tl_2");
        btn_ratio_tl_2->setGeometry(QRect(270, 220, 80, 24));
        btn_noise_width = new QPushButton(groupBox);
        btn_noise_width->setObjectName("btn_noise_width");
        btn_noise_width->setGeometry(QRect(270, 250, 80, 24));
        ln_noise_width = new QLineEdit(groupBox);
        ln_noise_width->setObjectName("ln_noise_width");
        ln_noise_width->setGeometry(QRect(120, 250, 108, 24));
        label_23 = new QLabel(groupBox);
        label_23->setObjectName("label_23");
        label_23->setGeometry(QRect(11, 250, 91, 16));
        btn_ratio_noise = new QPushButton(groupBox);
        btn_ratio_noise->setObjectName("btn_ratio_noise");
        btn_ratio_noise->setGeometry(QRect(270, 280, 80, 24));
        ln_ratio_noise = new QLineEdit(groupBox);
        ln_ratio_noise->setObjectName("ln_ratio_noise");
        ln_ratio_noise->setGeometry(QRect(120, 280, 108, 24));
        label_24 = new QLabel(groupBox);
        label_24->setObjectName("label_24");
        label_24->setGeometry(QRect(11, 280, 91, 16));
        lbl_serial_state = new QLabel(FpgaControlDialog);
        lbl_serial_state->setObjectName("lbl_serial_state");
        lbl_serial_state->setGeometry(QRect(400, 320, 251, 81));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        lbl_serial_state->setFont(font);
        label_2 = new QLabel(FpgaControlDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(41, 61, 71, 16));
        ln_wf_ctrl_mt = new QLineEdit(FpgaControlDialog);
        ln_wf_ctrl_mt->setObjectName("ln_wf_ctrl_mt");
        ln_wf_ctrl_mt->setGeometry(QRect(150, 61, 108, 24));
        btn_wf_ctrl = new QPushButton(FpgaControlDialog);
        btn_wf_ctrl->setObjectName("btn_wf_ctrl");
        btn_wf_ctrl->setGeometry(QRect(300, 61, 80, 24));
        btn_rf_tx = new QPushButton(FpgaControlDialog);
        btn_rf_tx->setObjectName("btn_rf_tx");
        btn_rf_tx->setGeometry(QRect(300, 91, 80, 24));
        ln_rf_tx = new QLineEdit(FpgaControlDialog);
        ln_rf_tx->setObjectName("ln_rf_tx");
        ln_rf_tx->setGeometry(QRect(150, 91, 108, 24));
        label_3 = new QLabel(FpgaControlDialog);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(41, 91, 71, 16));
        ln_att_tx = new QLineEdit(FpgaControlDialog);
        ln_att_tx->setObjectName("ln_att_tx");
        ln_att_tx->setGeometry(QRect(150, 361, 108, 24));
        btn_att_tx = new QPushButton(FpgaControlDialog);
        btn_att_tx->setObjectName("btn_att_tx");
        btn_att_tx->setGeometry(QRect(300, 361, 80, 24));
        label_15 = new QLabel(FpgaControlDialog);
        label_15->setObjectName("label_15");
        label_15->setGeometry(QRect(41, 361, 81, 16));
        label_14 = new QLabel(FpgaControlDialog);
        label_14->setObjectName("label_14");
        label_14->setGeometry(QRect(41, 271, 81, 16));
        ln_pulse2_delay = new QLineEdit(FpgaControlDialog);
        ln_pulse2_delay->setObjectName("ln_pulse2_delay");
        ln_pulse2_delay->setGeometry(QRect(150, 271, 108, 24));
        btn_pulse2 = new QPushButton(FpgaControlDialog);
        btn_pulse2->setObjectName("btn_pulse2");
        btn_pulse2->setGeometry(QRect(300, 271, 80, 24));
        label_8 = new QLabel(FpgaControlDialog);
        label_8->setObjectName("label_8");
        label_8->setGeometry(QRect(41, 181, 81, 16));
        ln_loopback = new QLineEdit(FpgaControlDialog);
        ln_loopback->setObjectName("ln_loopback");
        ln_loopback->setGeometry(QRect(150, 181, 108, 24));
        btn_loopback = new QPushButton(FpgaControlDialog);
        btn_loopback->setObjectName("btn_loopback");
        btn_loopback->setGeometry(QRect(300, 181, 80, 24));
        label_9 = new QLabel(FpgaControlDialog);
        label_9->setObjectName("label_9");
        label_9->setGeometry(QRect(41, 421, 91, 16));
        ln_ratio_mt = new QLineEdit(FpgaControlDialog);
        ln_ratio_mt->setObjectName("ln_ratio_mt");
        ln_ratio_mt->setGeometry(QRect(150, 421, 108, 24));
        btn_ratio_mt = new QPushButton(FpgaControlDialog);
        btn_ratio_mt->setObjectName("btn_ratio_mt");
        btn_ratio_mt->setGeometry(QRect(300, 421, 80, 24));
        ln_target_range = new QLineEdit(FpgaControlDialog);
        ln_target_range->setObjectName("ln_target_range");
        ln_target_range->setGeometry(QRect(150, 211, 108, 24));
        label_5 = new QLabel(FpgaControlDialog);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(41, 211, 71, 16));
        btn_target_range = new QPushButton(FpgaControlDialog);
        btn_target_range->setObjectName("btn_target_range");
        btn_target_range->setGeometry(QRect(300, 211, 80, 24));
        label_12 = new QLabel(FpgaControlDialog);
        label_12->setObjectName("label_12");
        label_12->setGeometry(QRect(41, 331, 91, 16));
        ln_mod_kd_onOff = new QLineEdit(FpgaControlDialog);
        ln_mod_kd_onOff->setObjectName("ln_mod_kd_onOff");
        ln_mod_kd_onOff->setGeometry(QRect(150, 331, 108, 24));
        btn_mod_kd = new QPushButton(FpgaControlDialog);
        btn_mod_kd->setObjectName("btn_mod_kd");
        btn_mod_kd->setGeometry(QRect(300, 331, 80, 24));
        label_16 = new QLabel(FpgaControlDialog);
        label_16->setObjectName("label_16");
        label_16->setGeometry(QRect(41, 301, 81, 16));
        btn_mod_kd_range = new QPushButton(FpgaControlDialog);
        btn_mod_kd_range->setObjectName("btn_mod_kd_range");
        btn_mod_kd_range->setGeometry(QRect(300, 301, 80, 24));
        ln_mod_kd_range = new QLineEdit(FpgaControlDialog);
        ln_mod_kd_range->setObjectName("ln_mod_kd_range");
        ln_mod_kd_range->setGeometry(QRect(150, 301, 108, 24));
        btn_pulse1 = new QPushButton(FpgaControlDialog);
        btn_pulse1->setObjectName("btn_pulse1");
        btn_pulse1->setGeometry(QRect(300, 241, 80, 24));
        label_7 = new QLabel(FpgaControlDialog);
        label_7->setObjectName("label_7");
        label_7->setGeometry(QRect(41, 241, 81, 16));
        ln_pulse1_delay = new QLineEdit(FpgaControlDialog);
        ln_pulse1_delay->setObjectName("ln_pulse1_delay");
        ln_pulse1_delay->setGeometry(QRect(150, 241, 108, 24));
        label_13 = new QLabel(FpgaControlDialog);
        label_13->setObjectName("label_13");
        label_13->setGeometry(QRect(41, 391, 91, 16));
        ln_mod_mt = new QLineEdit(FpgaControlDialog);
        ln_mod_mt->setObjectName("ln_mod_mt");
        ln_mod_mt->setGeometry(QRect(150, 391, 108, 24));
        btn_mod_mt = new QPushButton(FpgaControlDialog);
        btn_mod_mt->setObjectName("btn_mod_mt");
        btn_mod_mt->setGeometry(QRect(300, 391, 80, 24));
        label_6 = new QLabel(FpgaControlDialog);
        label_6->setObjectName("label_6");
        label_6->setGeometry(QRect(41, 151, 81, 16));
        ln_Thres_pc = new QLineEdit(FpgaControlDialog);
        ln_Thres_pc->setObjectName("ln_Thres_pc");
        ln_Thres_pc->setGeometry(QRect(150, 151, 108, 24));
        btn_thres_pc = new QPushButton(FpgaControlDialog);
        btn_thres_pc->setObjectName("btn_thres_pc");
        btn_thres_pc->setGeometry(QRect(300, 151, 80, 24));
        label_4 = new QLabel(FpgaControlDialog);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(41, 121, 91, 16));
        ln_Thres_lfm = new QLineEdit(FpgaControlDialog);
        ln_Thres_lfm->setObjectName("ln_Thres_lfm");
        ln_Thres_lfm->setGeometry(QRect(150, 121, 108, 24));
        btn_thres_lfm = new QPushButton(FpgaControlDialog);
        btn_thres_lfm->setObjectName("btn_thres_lfm");
        btn_thres_lfm->setGeometry(QRect(300, 121, 80, 24));
        btn_offset_range = new QPushButton(FpgaControlDialog);
        btn_offset_range->setObjectName("btn_offset_range");
        btn_offset_range->setGeometry(QRect(300, 450, 80, 24));
        label_21 = new QLabel(FpgaControlDialog);
        label_21->setObjectName("label_21");
        label_21->setGeometry(QRect(41, 450, 91, 16));
        ln_offset_range = new QLineEdit(FpgaControlDialog);
        ln_offset_range->setObjectName("ln_offset_range");
        ln_offset_range->setGeometry(QRect(150, 450, 108, 24));

        retranslateUi(FpgaControlDialog);

        QMetaObject::connectSlotsByName(FpgaControlDialog);
    } // setupUi

    void retranslateUi(QDialog *FpgaControlDialog)
    {
        FpgaControlDialog->setWindowTitle(QCoreApplication::translate("FpgaControlDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("FpgaControlDialog", "PRI_Mode", nullptr));
        btn_pri_mode->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FpgaControlDialog", "TL", nullptr));
        label_17->setText(QCoreApplication::translate("FpgaControlDialog", "RF_TL", nullptr));
        btn_rf_tl->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_20->setText(QCoreApplication::translate("FpgaControlDialog", "Modulation TL", nullptr));
        btn_mod_tl->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        btn_wf_ctrl_tl->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_18->setText(QCoreApplication::translate("FpgaControlDialog", "WF_Ctrl", nullptr));
        btn_tl_range->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_19->setText(QCoreApplication::translate("FpgaControlDialog", "TL Range", nullptr));
        label_11->setText(QCoreApplication::translate("FpgaControlDialog", "Ratio TL", nullptr));
        btn_ratio_tl->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        btn_att_tl->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_10->setText(QCoreApplication::translate("FpgaControlDialog", "Att TL", nullptr));
        label_22->setText(QCoreApplication::translate("FpgaControlDialog", "Offset Att", nullptr));
        btn_ratio_tl_2->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        btn_noise_width->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_23->setText(QCoreApplication::translate("FpgaControlDialog", "Noise Width", nullptr));
        btn_ratio_noise->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_24->setText(QCoreApplication::translate("FpgaControlDialog", "Ratio Noise", nullptr));
        lbl_serial_state->setText(QCoreApplication::translate("FpgaControlDialog", "TextLabel", nullptr));
        label_2->setText(QCoreApplication::translate("FpgaControlDialog", "WF_Ctrl", nullptr));
        btn_wf_ctrl->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        btn_rf_tx->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_3->setText(QCoreApplication::translate("FpgaControlDialog", "RF_TX", nullptr));
        btn_att_tx->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_15->setText(QCoreApplication::translate("FpgaControlDialog", "Att TX", nullptr));
        label_14->setText(QCoreApplication::translate("FpgaControlDialog", "Pulse 2 Delay", nullptr));
        btn_pulse2->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_8->setText(QCoreApplication::translate("FpgaControlDialog", "Loop Back", nullptr));
        btn_loopback->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_9->setText(QCoreApplication::translate("FpgaControlDialog", "Ratio MT", nullptr));
        btn_ratio_mt->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_5->setText(QCoreApplication::translate("FpgaControlDialog", "Target Range", nullptr));
        btn_target_range->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_12->setText(QCoreApplication::translate("FpgaControlDialog", "Modulation KD", nullptr));
        btn_mod_kd->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_16->setText(QCoreApplication::translate("FpgaControlDialog", "Mod KD Range", nullptr));
        btn_mod_kd_range->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        btn_pulse1->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_7->setText(QCoreApplication::translate("FpgaControlDialog", "Pulse 1 Delay", nullptr));
        label_13->setText(QCoreApplication::translate("FpgaControlDialog", "Modulation MT", nullptr));
        btn_mod_mt->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_6->setText(QCoreApplication::translate("FpgaControlDialog", "Threshold_PC", nullptr));
        btn_thres_pc->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_4->setText(QCoreApplication::translate("FpgaControlDialog", "Threshold_LFM", nullptr));
        btn_thres_lfm->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        btn_offset_range->setText(QCoreApplication::translate("FpgaControlDialog", "Send", nullptr));
        label_21->setText(QCoreApplication::translate("FpgaControlDialog", "Offset Range", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FpgaControlDialog: public Ui_FpgaControlDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FPGACONTROLDIALOG_H
