QT += core gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    DeviceControl.cpp \
    FPGADialog.cpp \
    fpgacontroldialog.cpp \
    main.cpp \
    mainwindow.cpp \
    serialport.cpp \
    socketcontrol.cpp

HEADERS += \
    DeviceControl.h \
    FPGADialog.h \
    commandstruct.h \
    fpgacontroldialog.h \
    mainwindow.h \
    serialport.h \
    socketcontrol.h

FORMS += \
    FPGADialog.ui \
    fpgacontroldialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
