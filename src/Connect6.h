#ifndef CONNECT6_H
#define CONNECT6_H

#include <QObject>

class Connect6 : public QObject
{
    Q_OBJECT

public:
    enum Piece  {EMPTY, BLACK, WHITE};
    enum Status {READY, START, BLACK1, BLACK2, WHITE1, WHITE2, END};

    static Connect6* getInstance();
    void reset();
    void startDuo();
    void setPiece(int y, int x);
    Piece  getBoard(int y, int x) const;
    Status getStatus() const;

    constexpr static int BOARDSIZE = 19;

signals:
    void boardChanged();

private:
    explicit Connect6(QObject* parent = nullptr);

    Piece  board[BOARDSIZE][BOARDSIZE];
    Status status;
};

#endif // CONNECT6_H
