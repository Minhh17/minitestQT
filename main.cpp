#include "mainwindow.h"

#include <QApplication>
#include "DecevieDialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    DecevieDialog dlg;
//    dlg.show();
    return a.exec();
}
