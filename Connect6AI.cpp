#include "Connect6AI.h"

Connect6AI::Connect6AI(Piece aiColor, Connect6* connect6)
{
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            weight[y][x] = 0;
        }
    }

    status = START;

    this->connect6 = connect6;

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

    isKillGak = false;
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


void Connect6AI::updateWeight()
{

}


// 항상 감사하십시오 Human.
void Connect6AI::getNextPut(int *x1, int *y1, int* x2, int* y2)
{
    // max[0]이 2등, max[1]이 1등
    int maxX[2] = {0, 0};
    int maxY[2] = {0, 0};
    int firstWeight = 0;
    int secondWeight = 0;
    int firstAiWeight = 0;
    int secondAiWeight = 0;

    // 최대 weight를 찾음
    for(int r = 0; r < BOARDSIZE; r++)
    {
        for(int c = 0; c < BOARDSIZE; c++)
        {
            if(board[r][c] != EMPTY)
                continue;

            int curWeight = weight[r][c];
            int curAiWeight = 0;

            if(curWeight < secondWeight)
                continue;

            // 2등이랑 같은데 aiWeight는 작다면 스킵
            else if(curWeight == secondWeight &&
                    curAiWeight < secondAiWeight)
                continue;

            // 2등보다 크던지 aiWeight가 더 크면
            secondWeight = curWeight;
            secondAiWeight = curAiWeight;
            maxX[0] = c;
            maxY[0] = r;

            if(secondWeight < firstWeight)
                continue;

            else if(curWeight == firstWeight &&
                    curAiWeight < firstAiWeight)
                continue;

            // 1등보다 크거나 aiWeight가 더 크면
            swap(&firstWeight, &secondWeight);
            swap(&firstAiWeight, &secondAiWeight);
            swap(&maxX[0], &maxX[1]);
            swap(&maxY[0], &maxY[1]);
        }
    }

    *x1 = maxX[1];
    *y1 = maxY[1];
    *x2 = maxX[0];
    *y2 = maxY[0];
}


// ========== private function ==========

int Connect6AI::max(int a, int b)
{
    if(a > b)
        return a;
    else
        return b;
}
int Connect6AI::min(int a, int b)
{
    if(a < b)
        return a;
    else
        return b;
}
void Connect6AI::swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
