/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QLabel *label;
    QPushButton *btn_Open;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *cmb_Name;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_2;
    QLabel *label_2;
    QLineEdit *ln_Ip_Addr;
    QLabel *label_3;
    QSpinBox *spn_port;
    QPushButton *btn_connect;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(373, 216);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 10, 314, 148));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName("groupBox");
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName("formLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        btn_Open = new QPushButton(groupBox);
        btn_Open->setObjectName("btn_Open");

        formLayout->setWidget(2, QFormLayout::LabelRole, btn_Open);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");

        formLayout->setLayout(3, QFormLayout::LabelRole, horizontalLayout_2);

        cmb_Name = new QComboBox(groupBox);
        cmb_Name->setObjectName("cmb_Name");

        formLayout->setWidget(1, QFormLayout::SpanningRole, cmb_Name);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName("groupBox_2");
        formLayout_2 = new QFormLayout(groupBox_2);
        formLayout_2->setObjectName("formLayout_2");
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName("label_2");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_2);

        ln_Ip_Addr = new QLineEdit(groupBox_2);
        ln_Ip_Addr->setObjectName("ln_Ip_Addr");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, ln_Ip_Addr);

        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");

        formLayout_2->setWidget(2, QFormLayout::LabelRole, label_3);

        spn_port = new QSpinBox(groupBox_2);
        spn_port->setObjectName("spn_port");
        spn_port->setMaximum(65536);
        spn_port->setValue(4000);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, spn_port);

        btn_connect = new QPushButton(groupBox_2);
        btn_connect->setObjectName("btn_connect");

        formLayout_2->setWidget(5, QFormLayout::FieldRole, btn_connect);


        gridLayout->addWidget(groupBox_2, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 373, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Serial", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Name", nullptr));
        btn_Open->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Ip Address:", nullptr));
        ln_Ip_Addr->setText(QCoreApplication::translate("MainWindow", "192.168.0.15", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        btn_connect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
