QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_connect6test.cpp

CONFIG(debug, debug|release) {
    LIBS += -L$${OUT_PWD}/../src/debug/
} else {
    LIBS += -L$${OUT_PWD}/../src/release/
}
LIBS += Connect6.o
