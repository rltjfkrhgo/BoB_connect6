QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_connect6test.cpp

CONFIG(debug, debug|release) {
    LIBS += $${OUT_PWD}/../src/debug/Connect6.o
} else {
    LIBS += $${OUT_PWD}/../src/release/Connect6.o
}
