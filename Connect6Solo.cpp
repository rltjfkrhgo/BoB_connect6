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

    // 사람이 흰돌이면 컴퓨터는 흑돌이고 첫 수를 둔다.
    if(userColor == WHITE)
    {
        cpuColor = BLACK;
        setPiece(BLACK, 9, 9);
        changeTurn();
    }

    // 사람이 검은돌이면 컴퓨터는 흰돌
    else
    {
        cpuColor = WHITE;
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
    if(status == START && userColor == BLACK)
    {
        setPiece(BLACK, x, y);
        updateWeight(userColor, x, y);
    }

    // 사람이 검은돌이고 검은돌 차례일 때
    else if(userColor == BLACK &&
            (status == BLACK1 || status == BLACK2) )
    {
        setPiece(BLACK, x, y);
        updateWeight(userColor, x, y);

        if(isEnd(BLACK, x, y))  status = BLACKWIN;
    }

    // 사람이 흰돌이고 흰돌 차례일 때
    else if(userColor == WHITE &&
            (status == WHITE1 || status == WHITE2) )
    {
        setPiece(WHITE, x, y);
        updateWeight(userColor, x, y);

        if(isEnd(WHITE, x, y))  status = WHITEWIN;
    }

    changeTurn();

    // 사람이 다 뒀으면 컴퓨터가 둔다.
    if( (cpuColor == BLACK && status == BLACK1) ||
        (cpuColor == WHITE && status == WHITE1) )
    {
        autoSetPiece();
    }

}

// 항상 감사하십시오 Human.
void Connect6Solo::autoSetPiece()
{
    int maxX[2] = {0, 0};
    int maxY[2] = {0, 0};
    int firstWeight = 0;
    int secondWeight = 0;

    for(int r = 0; r < BOARDSIZE; r++)
    {
        for(int c = 0; c < BOARDSIZE; c++)
        {
            if (board[r][c] != EMPTY)
                continue;

            int curWeight = weight[r][c];
            if(curWeight < secondWeight)
                continue;

            // 2등보다 크면
            secondWeight = curWeight;
            maxX[0] = c;
            maxY[0] = r;

            if(secondWeight < firstWeight)
                continue;

            // 1등보다도 크면
            swap(&firstWeight, &secondWeight);
            swap(&maxX[0], &maxX[1]);
            swap(&maxY[0], &maxY[1]);
        }
    }

    // cpu가 둔것도 isEnd 시켜줘야 하므로
    setPiece(cpuColor, maxX[1], maxY[1]);
    changeTurn();
    if(isEnd(cpuColor, maxX[1], maxY[1]))
    {
        if(cpuColor == BLACK)
            status = BLACKWIN;
        else
            status = WHITEWIN;
    }

    setPiece(cpuColor, maxX[0], maxY[0]);
    changeTurn();
    if(isEnd(cpuColor, maxX[0], maxY[0]))
    {
        if(cpuColor == BLACK)
            status = BLACKWIN;
        else
            status = WHITEWIN;
    }
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
}

void Connect6Solo::swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
