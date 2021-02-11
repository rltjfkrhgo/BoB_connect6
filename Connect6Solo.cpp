#include "Connect6Solo.h"
#include <stdio.h>

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
        updateWeight();
    }

    // 사람이 검은돌이고 검은돌 차례일 때
    else if(userColor == BLACK &&
            (status == BLACK1 || status == BLACK2) )
    {
        setPiece(BLACK, x, y);
        updateWeight();

        if(isEnd(BLACK, x, y))  status = BLACKWIN;
    }

    // 사람이 흰돌이고 흰돌 차례일 때
    else if(userColor == WHITE &&
            (status == WHITE1 || status == WHITE2) )
    {
        setPiece(WHITE, x, y);
        updateWeight();

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


void Connect6Solo::updateWeight()
{
    for(int y = 0; y < Connect6::BOARDSIZE; y++)
    {
        for(int x = 0; x < Connect6::BOARDSIZE; x++)
        {
            // 돌이 놓여진 칸은 볼 필요가 없다.
            if (board[y][x] != EMPTY)
            {
                weight[y][x] = 0;
                continue;
            }

            // 상대방 꺼
            int usermax = getRadialMax(userColor, x, y);
            if (usermax > 0)
                weight[y][x] = usermax + 4;
            // 내 꺼
            weight[y][x] += getRadialMax(cpuColor, x, y);
        }
    }

    char tempWeight[Connect6::BOARDSIZE][Connect6::BOARDSIZE] = {0, };
    // 2칸 떨어진 곳
    for(int y = 0; y < Connect6::BOARDSIZE; y++)
    {
        for(int x = 0; x < Connect6::BOARDSIZE; x++)
        {
            // 돌이 놓여진 칸은 볼 필요가 없다.
            if (board[y][x] != EMPTY)
                continue;
            else if (weight[y][x] == 0)
                tempWeight[y][x] = max(getRadialWeightMax(x, y)-1, 0);
        }
    }

    // temp와 합치기
    for(int y = 0; y < Connect6::BOARDSIZE; y++)
    {
        for(int x = 0; x < Connect6::BOARDSIZE; x++)
        {
            weight[y][x] += tempWeight[y][x];
        }
    }

    // 디버그 용
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
            printf("%2d ", weight[y][x]);
        printf("\n");
    }
    printf("\n");
}

// board[y][x]의 주위의 count 중 max 값
char Connect6Solo::getRadialMax(Piece color, int x, int y)
{
    int  n = countN(color, x, y);
    int  s = countS(color, x, y);
    int  w = countW(color, x, y);
    int  e = countE(color, x, y);
    int nw = countNW(color, x, y);
    int ne = countNE(color, x, y);
    int sw = countSW(color, x, y);
    int se = countSE(color, x, y);

    int  h = max(n, s);
    int  v = max(w, e);
    int rd = max(nw, se);
    int ld = max(ne, sw);

    return max( max(h, v), max(rd, ld) );
}


char Connect6Solo::getRadialWeightMax(int x, int y)
{
    int w[8] = {0, };

    if(0 < y)
        w[Connect6::N] = weight[y-1][x];
    if(0 < y && x < Connect6::BOARDSIZE-1)
        w[Connect6::NE] = weight[y-1][x+1];
    if(x < Connect6::BOARDSIZE-1)
        w[Connect6::E] = weight[y][x+1];
    if(y < Connect6::BOARDSIZE-1 && x < Connect6::BOARDSIZE-1)
        w[Connect6::SE] = weight[y+1][x+1];
    if(y < Connect6::BOARDSIZE-1)
        w[Connect6::S] = weight[y+1][x];
    if(y < Connect6::BOARDSIZE-1 && 0 < x)
        w[Connect6::SW] = weight[y+1][x-1];
    if(0 < x)
        w[Connect6::W] = weight[y][x-1];
    if(0 < y && 0 < x)
        w[Connect6::NW] = weight[y-1][x-1];

    int max = 0;
    for(int i = 0; i < 8; i++)
    {
        if(max < w[i])
            max = w[i];
    }

    return max;
}

int Connect6Solo::max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}

void Connect6Solo::swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
