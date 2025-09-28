#include "mainwindow.h"

#include <QApplication>
#include "FPGADialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    FPGADialog dlg;
    dlg.show();
    return a.exec();
}
