#include <QtTest>

// add necessary includes here

class Connect6Test : public QObject
{
    Q_OBJECT

public:
    Connect6Test();
    ~Connect6Test();

private slots:
    void test_case1();

};

Connect6Test::Connect6Test()
{

}

Connect6Test::~Connect6Test()
{

}

void Connect6Test::test_case1()
{

}

QTEST_APPLESS_MAIN(Connect6Test)

#include "tst_connect6test.moc"
