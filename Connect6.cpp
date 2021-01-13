#include "Connect6.h"

Connect6::Connect6()
{
    for(int y = 0; y < BOARDSIZE;y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            board[y][x] = EMPTY;
        }
    }

    mode = NOT;
    status = READY;
    turn = BLACK;
}

void Connect6::reset()
{
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            board[y][x] = EMPTY;
        }
    }

    mode = NOT;
    status = READY;
    turn = BLACK;
}

Connect6::Mode Connect6::getMode()
{
    return mode;
}

Connect6::Status Connect6::getStatus()
{
    return status;
}

// 핵심 함수
// 현재 모드에 따라서 돌 놓는것이 바뀐다.
void Connect6::setPiece(int x, int y)
{
    static int count = 2;

    if(x < -1 || x > BOARDSIZE
    || y < -1 || y > BOARDSIZE)
        return;
    if(board[y][x] != EMPTY)
        return;

    switch(mode)
    {
    case DUO:
        // 첫수
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
        break;

    default:
        break;
    }

    // 게임 끝났나?
    if(isEnd(turn, x, y))
    {
        status = END;
    }

    // 2개 놓으면 색깔 바뀌고 카운트 초기화
    if(count == 0)
    {
        changeTurn();
        count = 2;
    }
}

// x, y에 color 돌을 놓는다.
// 바둑판 벗어나면 -1
// 이미 돌이 놓여져 있으면 -1
// 돌을 놓으면 0
int Connect6::setPiece(Piece color, int x, int y)
{
    if(x < -1 || x > BOARDSIZE
    || y < -1 || y > BOARDSIZE)
        return -1;
    if(board[y][x] != EMPTY)
        return -1;

    board[y][x] = color;
    return 0;
}

Connect6::Piece Connect6::getPiece(int x, int y)
{
    return board[y][x];
}

void Connect6::changeTurn()
{
    if(turn == BLACK)
        turn = WHITE;
    else if(turn == WHITE)
        turn = BLACK;
}

Connect6::Piece Connect6::whosTurn()
{
    return turn;
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

// 둘이서 시작
void Connect6::startDuo()
{
    mode = DUO;
    status = START;
}
