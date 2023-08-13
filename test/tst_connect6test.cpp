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
    void resetTest();
    void startTest();
    void setPieceTest();
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

void Connect6Test::resetTest()
{
    Connect6 connect6;
    connect6.start();
    connect6.setPiece(BLACK, 9, 9);
    connect6.reset();

    QCOMPARE(connect6.getStatus(), READY);
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
            QCOMPARE(connect6.getBoard(y, x), EMPTY);
    }
}

void Connect6Test::startTest()
{
    Connect6 connect6;
    connect6.start();

    QCOMPARE(connect6.getStatus(), START);
    QCOMPARE(connect6.setPiece(WHITE, 9, 9), START);
    QCOMPARE(connect6.getBoard(9, 9), EMPTY);
    QCOMPARE(connect6.setPiece(BLACK, 9, 9), WHITE1);
    QCOMPARE(connect6.getBoard(9, 9), BLACK);
}

void Connect6Test::setPieceTest()
{
    Connect6 connect6;
    QCOMPARE(connect6.setPiece(BLACK, 9, 9), READY);

    connect6.start();
    QCOMPARE(connect6.setPiece(BLACK, 9, 9), WHITE1);
    QCOMPARE(connect6.setPiece(WHITE, BOARDSIZE, BOARDSIZE), WHITE1);
    QCOMPARE(connect6.setPiece(WHITE, -1, -1), WHITE1);
    QCOMPARE(connect6.setPiece(WHITE, 9, 9), WHITE1);

    QCOMPARE(connect6.setPiece(WHITE, 0, 0), WHITE2);
    QCOMPARE(connect6.setPiece(WHITE, 0, 1), BLACK1);
    QCOMPARE(connect6.setPiece(BLACK, 9, 10), BLACK2);
    QCOMPARE(connect6.setPiece(BLACK, 9, 11), WHITE1);
    QCOMPARE(connect6.setPiece(WHITE, 0, 2), WHITE2);
    QCOMPARE(connect6.setPiece(WHITE, 0, 3), BLACK1);
    QCOMPARE(connect6.setPiece(BLACK, 9, 12), BLACK2);
    QCOMPARE(connect6.setPiece(BLACK, 9, 13), WHITE1);
    QCOMPARE(connect6.setPiece(WHITE, 0, 4), WHITE2);
    QCOMPARE(connect6.setPiece(WHITE, 0, 5), WHITEWIN);
}

QTEST_APPLESS_MAIN(Connect6Test)

#include "tst_connect6test.moc"
