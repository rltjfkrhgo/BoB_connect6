#include "Connect6.h"

Connect6::Connect6()
{
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            board[y][x] = EMPTY;
        }
    }

    status = READY;
}

Connect6::Piece Connect6::getPiece(int x, int y)
{
    return board[y][x];
}

Connect6::Status Connect6::getStatus()
{
    return status;
}

/* ================ protected ================ */

// x, y에 color 돌을 놓는다.
// 바둑판 벗어나면 -1
// 이미 돌이 놓여져 있으면 -1
// 돌을 놓으면 0
int Connect6::setPiece(Piece color, int x, int y)
{
    if(x < -1 || BOARDSIZE-1 < x
    || y < -1 || BOARDSIZE-1 < y)
        return -1;
    if(board[y][x] != EMPTY)
        return -1;

    board[y][x] = color;
    return 0;
}

void Connect6::changeTurn()
{
    if(status == START)
        status = WHITE1;
    else if(status == WHITE1)
        status = WHITE2;
    else if(status == WHITE2)
        status = BLACK1;
    else if(status == BLACK1)
        status = BLACK2;
    else if(status == BLACK2)
        status = WHITE1;
}

bool Connect6::isEnd(Piece color, int x, int y)
{
    if(countH (color, x, y) == 6 ||
       countV (color, x, y) == 6 ||
       countRD(color, x, y) == 6 ||
       countLD(color, x, y) == 6)
        return true;
    else
        return false;
}
