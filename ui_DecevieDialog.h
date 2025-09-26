/********************************************************************************
** Form generated from reading UI file 'DecevieDialog.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DECEVIEDIALOG_H
#define UI_DECEVIEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DecevieDialog
{
public:
    QPushButton *btn_connect;
    QListWidget *lst_Message;
    QLineEdit *ln_Message;
    QPushButton *btn_Send;
    QLabel *lbl_State;
    QLabel *lbl_decevie_state;
    QLabel *lbl_decevie_speed;
    QLabel *lbl_Speed;

    void setupUi(QDialog *DecevieDialog)
    {
        if (DecevieDialog->objectName().isEmpty())
            DecevieDialog->setObjectName("DecevieDialog");
        DecevieDialog->resize(397, 312);
        btn_connect = new QPushButton(DecevieDialog);
        btn_connect->setObjectName("btn_connect");
        btn_connect->setGeometry(QRect(284, 12, 80, 24));
        lst_Message = new QListWidget(DecevieDialog);
        lst_Message->setObjectName("lst_Message");
        lst_Message->setGeometry(QRect(21, 11, 256, 271));
        ln_Message = new QLineEdit(DecevieDialog);
        ln_Message->setObjectName("ln_Message");
        ln_Message->setGeometry(QRect(284, 42, 108, 24));
        btn_Send = new QPushButton(DecevieDialog);
        btn_Send->setObjectName("btn_Send");
        btn_Send->setGeometry(QRect(284, 72, 80, 24));
        lbl_State = new QLabel(DecevieDialog);
        lbl_State->setObjectName("lbl_State");
        lbl_State->setGeometry(QRect(284, 102, 91, 16));
        lbl_decevie_state = new QLabel(DecevieDialog);
        lbl_decevie_state->setObjectName("lbl_decevie_state");
        lbl_decevie_state->setGeometry(QRect(284, 124, 49, 16));
        lbl_decevie_speed = new QLabel(DecevieDialog);
        lbl_decevie_speed->setObjectName("lbl_decevie_speed");
        lbl_decevie_speed->setGeometry(QRect(284, 168, 49, 16));
        lbl_Speed = new QLabel(DecevieDialog);
        lbl_Speed->setObjectName("lbl_Speed");
        lbl_Speed->setGeometry(QRect(284, 146, 81, 16));

        retranslateUi(DecevieDialog);

        QMetaObject::connectSlotsByName(DecevieDialog);
    } // setupUi

    void retranslateUi(QDialog *DecevieDialog)
    {
        DecevieDialog->setWindowTitle(QCoreApplication::translate("DecevieDialog", "Dialog", nullptr));
        btn_connect->setText(QCoreApplication::translate("DecevieDialog", "Connect", nullptr));
        btn_Send->setText(QCoreApplication::translate("DecevieDialog", "Send", nullptr));
        lbl_State->setText(QCoreApplication::translate("DecevieDialog", "Decevie State:", nullptr));
        lbl_decevie_state->setText(QCoreApplication::translate("DecevieDialog", "..........", nullptr));
        lbl_decevie_speed->setText(QCoreApplication::translate("DecevieDialog", "..........", nullptr));
        lbl_Speed->setText(QCoreApplication::translate("DecevieDialog", "Decevie Speed:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DecevieDialog: public Ui_DecevieDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DECEVIEDIALOG_H
