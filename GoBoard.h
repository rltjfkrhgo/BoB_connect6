#ifndef GOBOARD_H
#define GOBOARD_H

class GoBoard
{
public:
    enum Piece{EMPTY, BLACK, WHITE};

    GoBoard();
    void initBoard();
    void setPiece(Piece color, int x, int y);
    void setPiece(int x, int y);
    Piece getPiece(int x, int y);
    Piece getTurn();

private:
    Piece board[19][19];
    Piece turn;
};

#endif // GOBOARD_H
