QT       += core gui    axcontainer

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    GUI/MainWindow/maniWindow.cpp \
    GUI/QCustomPlot/myQCustomPlot.cpp \
    GUI/Settings/settings.cpp \
    GUI/Settings/zoomSettings.cpp \
    GUI/Size/customize.cpp \
    Library/QCustomPlot/qcustomplot.cpp \
    Process/Encryption/simplecrypt.cpp \
    Process/Process.cpp \
    main.cpp

HEADERS += \
    GUI/MainWindow/maniWindow.h \
    GUI/QCustomPlot/myQCustomPlot.h \
    GUI/Settings/settings.h \
    GUI/Settings/zoomSettings.h \
    GUI/Size/customize.h \
    Library/QCustomPlot/qcustomplot.h \
    Process/Encryption/simplecrypt.h \
    Process/Process.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Icon.qrc
