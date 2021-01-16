#ifndef CONNECT6_H
#define CONNECT6_H


class Connect6
{
public:
    enum Piece{EMPTY, BLACK, WHITE};
    enum Status{READY, START, ING, END};
    const static int BOARDSIZE = 19;

    Connect6();

    Piece  getPiece(int x, int y);
    Piece  whosTurn();
    Status getStatus();
    virtual void putPiece(int x, int y) = 0;

protected:
    Piece   board[BOARDSIZE][BOARDSIZE];
    Piece   turn;    // 현재 차례
    Status  status;  // 현재 상태

    int  setPiece(Piece color, int x, int y);
    void changeTurn();
    bool isEnd(Piece color, int x, int y);

    int countN(Piece color, int x, int y);
    int countS(Piece color, int x, int y);
    int countE(Piece color, int x, int y);
    int countW(Piece color, int x, int y);
    int countNW(Piece color, int x, int y);
    int countNE(Piece color, int x, int y);
    int countSW(Piece color, int x, int y);
    int countSE(Piece color, int x, int y);

    int countH(Piece color, int x, int y);
    int countV(Piece color, int x, int y);
    int countRD(Piece color, int x, int y);
    int countLD(Piece color, int x, int y);
};

#endif // CONNECT6_H
