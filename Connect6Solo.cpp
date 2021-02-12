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
    this->humanColor = userColor;
    isKillGak = false;

    // 사람이 흰돌이면 컴퓨터는 흑돌이고 첫 수를 둔다.
    if(userColor == WHITE)
    {
        aiColor = BLACK;
        setPiece(BLACK, 9, 9);
        changeTurn();
    }

    // 사람이 검은돌이면 컴퓨터는 흰돌
    else
    {
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
        updateWeight();
    }

    // 사람이 검은돌이고 검은돌 차례일 때
    else if(humanColor == BLACK &&
            (status == BLACK1 || status == BLACK2) )
    {
        setPiece(BLACK, x, y);
        updateWeight();

        if(isEnd(BLACK, x, y))  status = BLACKWIN;
    }

    // 사람이 흰돌이고 흰돌 차례일 때
    else if(humanColor == WHITE &&
            (status == WHITE1 || status == WHITE2) )
    {
        setPiece(WHITE, x, y);
        updateWeight();

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
    setPiece(aiColor, maxX[1], maxY[1]);
    changeTurn();
    if(isEnd(aiColor, maxX[1], maxY[1]))
    {
        if(aiColor == BLACK)
            status = BLACKWIN;
        else
            status = WHITEWIN;
    }

    setPiece(aiColor, maxX[0], maxY[0]);
    changeTurn();
    if(isEnd(aiColor, maxX[0], maxY[0]))
    {
        if(aiColor == BLACK)
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
            // 반경 1칸 내의 상대방의 count
            int humanMax = getRadialMax(humanColor, x, y);
            if (humanMax > 0)
                weight[y][x] = humanMax;
            else
                weight[y][x] = 0;

            // 내 꺼
            //weight[y][x] += getRadialMax(cpuColor, x, y);
        }
    }

    char tempWeight[Connect6::BOARDSIZE][Connect6::BOARDSIZE] = {{0}, };
    // 반경 2칸
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


// 한 줄만 가져오자...
// [y][x]를 지나가는 각 방향으로 boardLine에 복사.
// len은 유효 길이.
void Connect6Solo::getBoardLineH(int x, int y, Connect6::Piece boardLine[], int* len)
{
    for(int c = 0; c < BOARDSIZE; c++)
        boardLine[c] = board[y][c];
    *len = BOARDSIZE;
}
void Connect6Solo::getBoardLineV(int x, int y, Connect6::Piece boardLine[], int* len)
{
    for(int r = 0; r < BOARDSIZE; r++)
        boardLine[r] = board[r][x];
    *len = BOARDSIZE;
}
void Connect6Solo::getBoardLineRD(int x, int y, Connect6::Piece boardLine[], int* len)
{
    int idx = 0;
    for(int r = y - min(x, y), c = x - min(x, y);
        r < Connect6::BOARDSIZE && c < Connect6::BOARDSIZE;
        r++, c++)
    {
        boardLine[idx] = board[r][c];
        idx++;
    }
    *len = idx;
}
void Connect6Solo::getBoardLineLD(int x, int y, Connect6::Piece boardLine[], int* len)
{
    int idx = 0;
    for(int r = max(y-(Connect6::BOARDSIZE-1-x), 0), c = min(x+y, Connect6::BOARDSIZE-1);
        r < Connect6::BOARDSIZE && -1 < c;
        r++, c--)
    {
        boardLine[idx] = board[r][c];
        idx++;
    }
    *len = idx;
}

// 한 줄만 보자...
void Connect6Solo::updateLineWeight(Connect6::Piece boardLine[], char weightLine[], int len)
{
    int  emptyIdx[BOARDSIZE] = {0, };  // 비어있는 칸 인덱스
    int  numOfEmpty = 0;  // 비어있는 칸 개수
    int  numOfai = 0;     // AI 돌 개수
    for(int i = 0; i < len; i++)
    {
        if(boardLine[i] == Connect6::EMPTY)  // 비어있다면
        {
            emptyIdx[numOfEmpty] = i;
            numOfEmpty++;
        }
        else if(boardLine[i] == aiColor)  // 나의 돌이라면
            numOfai++;
    }

    // 놓을 칸이 없으면 리턴
    if(numOfEmpty == 0)
        return;

    // 1칸 이상 비어있고 4개 이상 내 돌이 있으면
    // 킬각을 살핀다.
    if(0 < numOfEmpty && 4 <= numOfai)
    {
        for(int a = 0; a < numOfEmpty; a++)
        {
            int idxA = emptyIdx[a];  // 빈 칸 중 하나
            for(int b = a; b < numOfEmpty; b++)
            {
                int idxB = emptyIdx[b];  // 빈 칸 중 다른 하나
                // 놓아본다.
                boardLine[idxA] = aiColor;
                boardLine[idxB] = aiColor;
                // 이겼나 확인해본다.
                int count = 0;
                for(int i = 0; i < len; i++)
                {
                    if(boardLine[i] == aiColor)
                        count++;
                    else
                        count = 0;
                    if(count == 6)
                        break;
                }
                // 해치웠나?
                if(count == 6)
                {
                    weightLine[idxA] = 127;
                    weightLine[idxB] = 127;
                    isKillGak = true;
                    break;
                }
                // 놓았던거 다시 원복
                else
                {
                    boardLine[idxA] = Connect6::EMPTY;
                    boardLine[idxB] = Connect6::EMPTY;
                }
            }
            if(isKillGak)
                break;
        }
    }

    if(isKillGak)
        return;

    // 상대방 돌에 따라 weight 업데이트
    for(int i = 0; i < len; i++)
    {
        // 돌이 놓여진 곳은 0
        if(boardLine[i] != EMPTY)
            weightLine[i] = 0;
        else
        {
            // 왼쪽
            int left = 0;
            for(int idx = i-1; idx > -1; idx--)
            {
                if(boardLine[idx] == humanColor)
                    left++;
                else
                    break;
            }
            // 오른쪽
            int right = 0;
            for(int idx = i+1; idx < len; idx++)
            {
                if(boardLine[idx] == humanColor)
                    right++;
                else
                    break;
            }
            weightLine[i] = max(left, right);
        }
    }
}

int Connect6Solo::max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}
int Connect6Solo::min(int a, int b)
{
    if(a < b)
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
