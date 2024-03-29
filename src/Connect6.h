#ifndef CONNECT6_H
#define CONNECT6_H

#include "Connect6Type.h"

class Connect6
{
public:
    Connect6();

    Piece  whoseTurn() const;
    Piece  getBoard(int y, int x) const;
    Status getStatus() const;
    bool   reset();
    bool   start();
    bool   setPiece(Piece color, int y, int x);

private:
    bool   isEnd(Piece color, int y, int x) const;
    Status nextStatus(Status status) const;

    Piece  board[BOARDSIZE][BOARDSIZE];
    Status status;
};

#endif // CONNECT6_H
