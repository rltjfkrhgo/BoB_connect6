#ifndef GOBOARD_H
#define GOBOARD_H

class GoBoard
{
public:
    const static int BOARDSIZE = 19;
    enum Piece{EMPTY, BLACK, WHITE};

    GoBoard();
    void resetBoard();

    bool isEmpty(int x, int y);

    int setPiece(Piece color, int x, int y);
    void setPiece(int x, int y);
    Piece getPiece(int x, int y);

    void changeTurn();
    Piece getTurn();

    bool checkGameOver(Piece color, int x, int y);

private:
    Piece board[BOARDSIZE][BOARDSIZE];
    Piece turn;
    Piece lastColor;
    int lastX1;
    int lastY1;
    int lastX2;
    int lastY2;
    int count;

    int countN(Piece color, int x, int y);
    int countS(Piece color, int x, int y);
    int countE(Piece color, int x, int y);
    int countW(Piece color, int x, int y);
    int countNW(Piece color, int x, int y);
    int countNE(Piece color, int x, int y);
    int countSW(Piece color, int x, int y);
    int countSE(Piece color, int x, int y);

public:
    int countH(Piece color, int x, int y);
    int countV(Piece color, int x, int y);
    int countRD(Piece color, int x, int y);
    int countLD(Piece color, int x, int y);
};

#endif // GOBOARD_H
