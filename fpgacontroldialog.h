#ifndef FPGACONTROLDIALOG_H
#define FPGACONTROLDIALOG_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QVBoxLayout>
#include <serialport.h>
#include <commandstruct.h>
#include <QString>
#include <DeviceControl.h>
#include <socketcontrol.h>

// PC side - UI Class

namespace Ui {
class FpgaControlDialog;
}

class FpgaControlDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FpgaControlDialog(QWidget *parent = nullptr);
    ~FpgaControlDialog();

    enum Index {
        Idx_PriMode         = 0,
        Idx_WfCtrl_MT       = 1,
        Idx_Rf_Tx_R3        = 2,
        Idx_Rf_Tx_R4        = '0',
        Idx_Threshold_LFM   = 3,
        Idx_Threshold_PC    = 4,
        Idx_LoopBack        = 5,
        Idx_Target_Range    = 6,
        Idx_Pulse1          = 7,
        Idx_Pulse2          = 8,
        Idx_Mod_KD_Range    = 9,
        Idx_Modulation_KD   = 10,
        Idx_Att_TX          = 11,
        Idx_Modulation_MT   = 12,
        Idx_Ratio_MT        = 13,
        Idx_Offset_Range    = 14,
        Idx_WfCtrl_TL       = 15,
        Idx_RF_TL_R3        = 16,
        Idx_RF_TL_R4        = '1',
        Idx_Modulation_TL   = 17,
        Idx_TL_Range        = 18,
        Idx_Att_TL          = 19,
        Idx_Ratio_TL        = 20,
        Idx_Offset_Att      = 21,
        Idx_Ratio_Noise     = 22,
        Idx_Noise_Width     = 23
    };
    Q_ENUM(Index)

    void ConvertLO(int, int&, int&);

public slots:
    void SerialPortConnected(DeviceControl*);

    void SocketConnected(SocketControl*);

    void ReadData(QByteArray);

    void Disconnect();

private slots:
    void on_btn_pri_mode_clicked();

    void on_btn_wf_ctrl_clicked();

    void on_btn_rf_tx_clicked();

    void on_btn_thres_lfm_clicked();

    void on_btn_thres_pc_clicked();

    void on_btn_loopback_clicked();

    void on_btn_target_range_clicked();

    void on_btn_pulse1_clicked();

    void on_btn_pulse2_clicked();

    void on_btn_mod_kd_range_clicked();

    void on_btn_mod_kd_clicked();

    void on_btn_att_tx_clicked();

    void on_btn_mod_mt_clicked();

    void on_btn_ratio_mt_clicked();

    void on_btn_offset_range_clicked();

    void on_btn_wf_ctrl_tl_clicked();

    void on_btn_rf_tl_clicked();

    void on_btn_mod_tl_clicked();

    void on_btn_tl_range_clicked();

    void on_btn_att_tl_clicked();

    void on_btn_ratio_tl_clicked();

    void on_btn_ratio_tl_2_clicked();

    void on_btn_noise_width_clicked();

    void on_btn_ratio_noise_clicked();

    void onSocketReadyRead();

private:
    Ui::FpgaControlDialog *ui;
    DeviceControl *fpga_device;
    CommandStruct _struct;
    SocketControl *socket_device;

    QByteArray m_rx;
    QChartView *m_chartView = nullptr;
    QChart     *m_chart     = nullptr;
    QScatterSeries *m_series = nullptr;
    QValueAxis *m_axX = nullptr, *m_axY = nullptr;
    void plotPoint(quint16 x, quint16 y);
};

#endif // FPGACONTROLDIALOG_H
