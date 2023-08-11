QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Bot.cpp \
    src/Connect6.cpp \
    src/RenderArea.cpp \
    src/Widget.cpp \
    src/main.cpp

HEADERS += \
    src/Bot.h \
    src/Connect6.h \
    src/RenderArea.h \
    src/Widget.h

RESOURCES += \
    connect6.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
