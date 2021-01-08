#ifndef CONNECT6_H
#define CONNECT6_H

class Connect6
{
public:
    const static int BOARDSIZE = 19;
    enum Mode{NOT, SOLO, DUO, CPUNET};
    enum Status{READY, START, ING, END};
    enum Piece{EMPTY, BLACK, WHITE};

    Connect6();
    void reset();

    Mode getMode();
    Status getStatus();

    void setPiece(int x, int y);
    Piece getPiece(int x, int y);

    void changeTurn();
    Piece whosTurn();

    void startDuo();

private:
    Mode mode;
    Status status;
    Piece board[BOARDSIZE][BOARDSIZE];
    Piece turn;  // 현재 차례
    int setCount;
    int numOfPiece;

    int setPiece(Piece color, int x, int y);

    int countN(Piece color, int x, int y);
    int countS(Piece color, int x, int y);
    int countE(Piece color, int x, int y);
    int countW(Piece color, int x, int y);
    int countNW(Piece color, int x, int y);
    int countNE(Piece color, int x, int y);
    int countSW(Piece color, int x, int y);
    int countSE(Piece color, int x, int y);
};

#endif
