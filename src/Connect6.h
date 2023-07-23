#ifndef CONNECT6_H
#define CONNECT6_H

class Connect6
{
public:
    enum Piece {EMPTY, BLACK, WHITE};

    static Connect6* getInstance();
    void resetBoard();
    void setPiece(Piece color, int y, int x);
    Piece getBoard(int y, int x) const;

    constexpr static int BOARDSIZE = 19;

private:
    Connect6();
    Piece board[BOARDSIZE][BOARDSIZE];
};

#endif // CONNECT6_H
