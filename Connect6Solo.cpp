#include "Connect6Solo.h"
#include <stdio.h>

Connect6Solo::Connect6Solo(Piece userColor)
{
    status = START;
    this->humanColor = userColor;

    // 사람이 흰돌이면 컴퓨터는 흑돌이고 첫 수를 둔다.
    if(userColor == WHITE)
    {
        ai = new Connect6AI(BLACK, this);
        aiColor = BLACK;
        setPiece(BLACK, 9, 9);
        changeTurn();
    }

    // 사람이 검은돌이면 컴퓨터는 흰돌
    else
    {
        ai = new Connect6AI(WHITE, this);
        aiColor = WHITE;
    }
}

void Connect6Solo::putPiece(int x, int y)
{
    if(x < -1 || BOARDSIZE-1 < x
    || y < -1 || BOARDSIZE-1 < y)
        return;
    if(board[y][x] != EMPTY)
        return;

    // 사람이 검은돌이고 첫 수를 둘 때
    if(status == START && humanColor == BLACK)
    {
        setPiece(BLACK, x, y);
    }

    // 사람이 검은돌이고 검은돌 차례일 때
    else if(humanColor == BLACK &&
            (status == BLACK1 || status == BLACK2) )
    {
        setPiece(BLACK, x, y);
        if(isEnd(BLACK, x, y))  status = BLACKWIN;
    }

    // 사람이 흰돌이고 흰돌 차례일 때
    else if(humanColor == WHITE &&
            (status == WHITE1 || status == WHITE2) )
    {
        setPiece(WHITE, x, y);
        if(isEnd(WHITE, x, y))  status = WHITEWIN;
    }

    changeTurn();

    // 사람이 다 뒀으면 컴퓨터가 둔다.
    if( (aiColor == BLACK && status == BLACK1) ||
        (aiColor == WHITE && status == WHITE1) )
    {
        autoSetPiece();
    }

}

// 항상 감사하십시오 Human.
void Connect6Solo::autoSetPiece()
{
    ai->updateWeight();  // 갱신

    int x1, y1, x2, y2;
    ai->getNextPut(&x1, &y1, &x2, &y2);

    // cpu가 둔것도 isEnd 시켜줘야 하므로
    setPiece(aiColor, x1, y1);
    changeTurn();
    if(isEnd(aiColor, x1, y1))
    {
        if(aiColor == BLACK)
            status = BLACKWIN;
        else
            status = WHITEWIN;
    }

    setPiece(aiColor, x2, y2);
    changeTurn();
    if(isEnd(aiColor, x2, y2))
    {
        if(aiColor == BLACK)
            status = BLACKWIN;
        else
            status = WHITEWIN;
    }
}
