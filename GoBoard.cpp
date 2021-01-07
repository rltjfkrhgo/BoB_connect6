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

    turn = BLACK;
}

void GoBoard::initBoard()
{
    for(int y = 0; y < 19; y++)
    {
        for(int x = 0; x < 19; x++)
        {
            board[y][x] = EMPTY;
        }
    }

    turn = BLACK;
}

void GoBoard::setPiece(Piece color, int x, int y)
{
    board[y][x] = color;
}

void GoBoard::setPiece(int x, int y)
{
    board[y][x] = turn;

    switch(turn)
    {
    case BLACK:
        turn = WHITE;
        break;
    case WHITE:
        turn = BLACK;
        break;
    default:
        break;
    }
}

GoBoard::Piece GoBoard::getPiece(int x, int y)
{
    return board[y][x];
}
