#include "Connect6Solo.h"

#include <iostream>

Connect6Solo::Connect6Solo(Piece userColor)
{
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            weight[y][x] = 0;
        }
    }

    status = START;
    this->userColor = userColor;

    // 사람이 후공이면 컴퓨터가 첫 수를 둔다.
    if(userColor == WHITE)
    {
        cpuColor = BLACK;
        setPiece(BLACK, 9, 9);
        status = ING;
        changeTurn();
    }

    else
    {
        cpuColor = WHITE;
    }
}

void Connect6Solo::putPiece(int x, int y)
{
    static int count = 2;

    if(x < -1 || BOARDSIZE-1 < x
    || y < -1 || BOARDSIZE-1 < y)
        return;
    if(board[y][x] != EMPTY)
        return;

    if(status == START && userColor == BLACK)
    {
        setPiece(BLACK, x, y);
        count = 0;
        status = ING;
    }

    // 사람 차례
    else if(status == ING && turn == userColor)
    {
        setPiece(turn, x, y);
        updateWeight(userColor, x, y);
        count--;
    }

    // 컴퓨터 차례
    else if(status == ING && turn == cpuColor)
    {
        //autoSetPiece();
        count = 0;
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

// 항상 감사하십시오 Human.
void Connect6Solo::autoSetPiece(int x1, int y1, int x2, int y2)
{
}

void Connect6Solo::updateWeight(Piece color, int x, int y)
{
    int r = 0;
    int c = 0;
    weight[y][x] = 0;

    // 수직
    int n  = countN(color, x, y);
    int s  = countS(color, x, y);
    r = y-n-1;
    if(-1 < r)
        weight[r][x] += n+s+1;
    r = y+s+1;
    if(r < BOARDSIZE)
        weight[r][x] += n+s+1;

    // 수평
    int w  = countW(color, x, y);
    int e  = countE(color, x, y);
    c = x-w-1;
    if(-1 < c)
        weight[y][c] += w+e+1;
    c = x+e+1;
    if(c < BOARDSIZE)
        weight[y][c] += w+e+1;

    // 대각선
    int nw = countNW(color, x, y);
    int se = countSE(color, x, y);
    r = y-nw-1;
    c = x-nw-1;
    if(-1 < r && -1 < c)
        weight[r][c] += nw+se+1;
    r = y+se+1;
    c = x+se+1;
    if(r < BOARDSIZE && c < BOARDSIZE)
        weight[r][c] += nw+se+1;

    // 대각선
    int ne = countNE(color, x, y);
    int sw = countSW(color, x, y);
    r = y-ne-1;
    c = x+ne+1;
    if(-1 < r && c < BOARDSIZE)
        weight[r][c] += ne+sw+1;
    r = y+se+1;
    c = x-se-1;
    if(r < BOARDSIZE && -1 < c)
        weight[r][c] += ne+sw+1;

    // 디버그용
    for(r = 0; r < BOARDSIZE; r++)
    {
        for(c = 0; c < BOARDSIZE; c++)
            std::cout << (int)weight[r][c] << " ";
        std::cout << std::endl;
    }
}
