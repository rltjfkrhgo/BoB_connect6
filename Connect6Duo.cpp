#include "Connect6Duo.h"

Connect6Duo::Connect6Duo()
{
    status = START;
}

void Connect6Duo::putPiece(int x, int y)
{
    if(x < -1 || BOARDSIZE-1 < x
    || y < -1 || BOARDSIZE-1 < y)
        return;
    if(board[y][x] != EMPTY)
        return;

    // 첫 수 놓기
    if(status == START)
        setPiece(BLACK, x, y);

    // 검은돌 차례
    else if(status == BLACK1 ||
            status == BLACK2)
    {
        setPiece(BLACK, x, y);
        if(isEnd(BLACK, x, y))  status = BLACKWIN;
    }

    // 흰돌 차례
    else if(status == WHITE1 ||
            status == WHITE2)
    {
        setPiece(WHITE, x, y);
        if(isEnd(WHITE, x, y))  status = WHITEWIN;
    }

    changeTurn();
}
