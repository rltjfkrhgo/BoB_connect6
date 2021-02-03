#include "Connect6AI.h"

Connect6AI::Connect6AI(Piece aiColor)
{
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            weight[y][x] = 0;
        }
    }

    status = START;

    if(aiColor == BLACK)
    {
        this->aiColor = BLACK;
        this->humanColor = WHITE;
    }
    else
    {
        this->aiColor = WHITE;
        this->humanColor = BLACK;
    }
}

void Connect6AI::putPiece(int x, int y)
{
    // 첫 수
    if(status == START)
    {
        setPiece(BLACK, x, y);
    }
    // 검정 차례
    else if(status == BLACK1 || status == BLACK2)
    {
        setPiece(BLACK, x, y);
    }
    // 흰색 차례
    else if(status == WHITE1 || status == WHITE2)
    {
        setPiece(WHITE, x, y);
    }

    changeTurn();
}

// 항상 감사하십시오 Human.
void Connect6AI::getNextPut(int *x1, int *y1, int* x2, int* y2)
{
    // max[0]이 2등, max[1]이 1등
    int maxX[2] = {0, 0};
    int maxY[2] = {0, 0};
    int firstWeight = 0;
    int secondWeight = 0;

    // 최대 weight를 찾음
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

    *x1 = maxX[1];
    *y1 = maxY[1];
    *x2 = maxX[0];
    *y2 = maxY[0];
}

// 사람이 x, y에 뒀을 때 wight를 갱신
void Connect6AI::updateWeight(int x, int y)
{
    int r = 0;
    int c = 0;
    weight[y][x] = 0;

    // 수직
    int n  = countN(humanColor, x, y);
    int s  = countS(humanColor, x, y);
    r = y-n-1;
    if(-1 < r)
        weight[r][x] += n+s+1;
    r = y+s+1;
    if(r < BOARDSIZE)
        weight[r][x] += n+s+1;

    // 수평
    int w  = countW(humanColor, x, y);
    int e  = countE(humanColor, x, y);
    c = x-w-1;
    if(-1 < c)
        weight[y][c] += w+e+1;
    c = x+e+1;
    if(c < BOARDSIZE)
        weight[y][c] += w+e+1;

    // 대각선
    int nw = countNW(humanColor, x, y);
    int se = countSE(humanColor, x, y);
    r = y-nw-1;
    c = x-nw-1;
    if(-1 < r && -1 < c)
        weight[r][c] += nw+se+1;
    r = y+se+1;
    c = x+se+1;
    if(r < BOARDSIZE && c < BOARDSIZE)
        weight[r][c] += nw+se+1;

    // 대각선
    int ne = countNE(humanColor, x, y);
    int sw = countSW(humanColor, x, y);
    r = y-ne-1;
    c = x+ne+1;
    if(-1 < r && c < BOARDSIZE)
        weight[r][c] += ne+sw+1;
    r = y+se+1;
    c = x-se-1;
    if(r < BOARDSIZE && -1 < c)
        weight[r][c] += ne+sw+1;
}

void Connect6AI::swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
