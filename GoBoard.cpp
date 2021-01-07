#include "GoBoard.h"

GoBoard::GoBoard()
{
    for(int y = 0; y < 19; y++)
    {
        for(int x = 0; x < 19; x++)
        {
            board[y][x] = EMPTY;
        }
    }
}

void GoBoard::setPiece(Piece color, int x, int y)
{
    board[y][x] = color;
}

GoBoard::Piece GoBoard::getPiece(int x, int y)
{
    return board[y][x];
}
