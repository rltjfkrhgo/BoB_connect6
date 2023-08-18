QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Bot.cpp \
    Connect6.cpp \
    Connect6Type.cpp \
    Controller.cpp \
    Net.cpp \
    RenderArea.cpp \
    Widget.cpp \
    main.cpp

HEADERS += \
    Bot.h \
    Connect6.h \
    Connect6Type.h \
    Controller.h \
    Net.h \
    RenderArea.h \
    Widget.h

RESOURCES += \
    connect6.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
