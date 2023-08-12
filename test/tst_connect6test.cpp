#include <QtTest>

#include "../src/Connect6.h"

class Connect6Test : public QObject
{
    Q_OBJECT

public:
    Connect6Test();
    ~Connect6Test();

private slots:
    void ctorTest();

};

Connect6Test::Connect6Test()
{

}

Connect6Test::~Connect6Test()
{

}

void Connect6Test::ctorTest()
{
    Connect6 connect6;

    QCOMPARE(connect6.getStatus(), READY);
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
            QCOMPARE(connect6.getBoard(y, x), EMPTY);
    }
}

QTEST_APPLESS_MAIN(Connect6Test)

#include "tst_connect6test.moc"
