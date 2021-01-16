#include "Connect6Duo.h"

Connect6Duo::Connect6Duo()
{
    status = START;
}

void Connect6Duo::putPiece(int x, int y)
{
    static int count = 2;

    if(x < -1 || BOARDSIZE-1 < x
    || y < -1 || BOARDSIZE-1 < y)
        return;
    if(board[y][x] != EMPTY)
        return;

    if(status == START)
    {
        setPiece(BLACK, x, y);
        count = 0;
        status = ING;
    }

    else if(status == ING)
    {
        setPiece(turn, x, y);
        count--;
    }

    if(isEnd(turn, x, y))
    {
        status = END;
    }

    if(count == 0)
    {
        changeTurn();
        count = 2;
    }
}
