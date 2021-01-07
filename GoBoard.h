#ifndef GOBOARD_H
#define GOBOARD_H

class GoBoard
{
public:
    enum Piece{EMPTY, BLACK, WHITE};

    GoBoard();
    void setPiece(Piece color, int x, int y);
    Piece getPiece(int x, int y);

private:
    Piece board[19][19];
};

#endif // GOBOARD_H
