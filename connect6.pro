QT       += core gui network

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
    Connect6.cpp \
    Connect6AI.cpp \
    Connect6CpuNet.cpp \
    Connect6Duo.cpp \
    Connect6Socket.cpp \
    Connect6Solo.cpp \
    Connect6_count.cpp \
    main.cpp \
    widget.cpp

HEADERS += \
    Connect6.h \
    Connect6AI.h \
    Connect6CpuNet.h \
    Connect6Duo.h \
    Connect6Socket.h \
    Connect6Solo.h \
    connect6_protocol.h \
    widget.h

FORMS += \
    widget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lconnect6_protocol
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lconnect6_protocol
else:unix: LIBS += -L$$PWD/lib/ -lconnect6_protocol

INCLUDEPATH += $$PWD/lib
DEPENDPATH += $$PWD/lib

DISTFILES += \
    lib/connect6_protocol.lib
