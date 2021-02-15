#include "Connect6AI.h"
#include <vector>
#include <stdio.h>
#include <qDebug>

Connect6AI::Connect6AI(Piece aiColor, Connect6* connect6)
{
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            weight[y][x] = 0;
        }
    }

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

    isAiKillGak = false;
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

/*
void Connect6AI::updateWeight()
{
    // 초기화
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
            weight[y][x] = 0;
    }

    // 가로 줄
    for(int y = 0; y < BOARDSIZE; y++)
    {
        Connect6::Piece boardLine[BOARDSIZE] = {Connect6::EMPTY, };
        int len = 0;
        copyBoardLineH(0, y, boardLine, &len);  // 가로 1줄 복사
        char weightLine[BOARDSIZE] = {0, };
        updateLineWeight(boardLine, weightLine, len);  // weight 계산
        pasteWeightLineH(0, y, weightLine);  // 전체 weight에 반영
    }

    // 세로 줄
    for(int x = 0; x < BOARDSIZE; x++)
    {
        Connect6::Piece boardLine[BOARDSIZE] = {Connect6::EMPTY, };
        int len = 0;
        copyBoardLineV(x, 0, boardLine, &len);  // 세로 1줄 복사
        char weightLine[BOARDSIZE] = {0, };
        updateLineWeight(boardLine, weightLine, len);  // weight 계산
        pasteWeightLineV(x, 0, weightLine);  // 전체 weight에 반영
    }

    // RD 대각선
    for(int x = BOARDSIZE-1; -1 < x; x--)
    {
        Connect6::Piece boardLine[BOARDSIZE] = {Connect6::EMPTY, };
        int len = 0;
        copyBoardLineRD(x, 0, boardLine, &len);  // RD 대각선 1줄 복사
        char weightLine[BOARDSIZE] = {0, };
        updateLineWeight(boardLine, weightLine, len);  // weight 계산
        pasteWeightLineRD(x, 0, weightLine);  // 전체 weight에 반영
    }
    for(int y = 1; y < Connect6::BOARDSIZE; y++)
    {
        Connect6::Piece boardLine[BOARDSIZE] = {Connect6::EMPTY, };
        int len = 0;
        copyBoardLineRD(0, y, boardLine, &len);  // RD 대각선 1줄 복사
        char weightLine[BOARDSIZE] = {0, };
        updateLineWeight(boardLine, weightLine, len);  // weight 계산
        pasteWeightLineRD(0, y, weightLine);  // 전체 weight에 반영
    }

    // LD 대각선
    for(int x = 0;x < BOARDSIZE; x++)
    {
        Connect6::Piece boardLine[BOARDSIZE] = {Connect6::EMPTY, };
        int len = 0;
        copyBoardLineLD(x, 0, boardLine, &len);  // LD 대각선 1줄 복사
        char weightLine[BOARDSIZE] = {0, };
        updateLineWeight(boardLine, weightLine, len);  // weight 계산
        pasteWeightLineLD(x, 0, weightLine);  // 전체 weight에 반영
    }
    for(int y = 1; y < BOARDSIZE; y++)
    {
        Connect6::Piece boardLine[BOARDSIZE] = {Connect6::EMPTY, };
        int len = 0;
        copyBoardLineLD(BOARDSIZE-1, y, boardLine, &len);  // LD 대각선 1줄 복사
        char weightLine[BOARDSIZE] = {0, };
        updateLineWeight(boardLine, weightLine, len);  // weight 계산
        pasteWeightLineLD(BOARDSIZE-1, y, weightLine);  // 전체 weight에 반영
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
*/

void Connect6AI::updateWeight()
{
    std::vector<int> emptyX;  // EMPTY인 X좌표들
    std::vector<int> emptyY;  // EMPTY인 Y좌표들  그냥 구조체 쓸걸 ㅅㅂ

    // 보드판 복사, weight 초기화, 빈칸 조사
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            board[y][x] = connect6->board[y][x];
            weight[y][x] = -1;
            if(EMPTY == connect6->board[y][x])
            {
                weight[y][x] = 0;
                emptyX.push_back(x);
                emptyY.push_back(y);
            }
        }
    }

    // 내 킬각 재기
    // 각나오면 가중치 최대로 주고 리턴
    for(int idx1 = 0; idx1 < emptyX.size(); idx1++)
    {
        int x1 = emptyX[idx1];
        int y1 = emptyY[idx1];
        for(int idx2 = 0; idx2 < emptyX.size(); idx2++)
        {
            int x2 = emptyX[idx2];
            int y2 = emptyY[idx2];  // 빈칸 중 다른 하나

            // 놓아본다.
            setPiece(aiColor, x1, y1);
            setPiece(aiColor, x2, y2);

            // 이겼나 확인해본다.
            bool ret1 = isEnd(aiColor, x1, y1);
            bool ret2 = isEnd(aiColor, x2, y2);

            // 킬 각 나왔으면
            if(ret1 || ret2)
            {
                weight[y1][x1] = ONE_COM;
                weight[y2][x2] = ONE_COM;
                return;
            }

            // 아니면 원복
            board[y2][x2] = EMPTY;
            board[y1][x1] = EMPTY;
        }
    }


    int count = 2;
    // 상대가 1개만으로 끝낼 수 있는지 확인
    for(int idx = 0; idx < emptyX.size(); idx++)
    {
        int x = emptyX[idx];
        int y = emptyY[idx];  // 빈칸 중 하나
        setPiece(humanColor, x, y);  // 놓아본다.
        if(isEnd(humanColor, x, y))  // 끝났나?
        {
            weight[y][x] = ONE_COM;
            count--;
        }
        else
            board[y][x] = EMPTY;  // 원복
    }

    if(count > 1)
    {
        // 상대가 2개만으로 끝낼 수 있는지 확인
        for(int idx1 = 0; idx1 < emptyX.size(); idx1++)
        {
            int x1 = emptyX[idx1];
            int y1 = emptyY[idx1];
            for(int idx2 = 0; idx2 < emptyX.size(); idx2++)
            {
                int x2 = emptyX[idx2];
                int y2 = emptyY[idx2];  // 빈칸 중 다른 하나

                // 놓아본다.
                setPiece(humanColor, x1, y1);
                setPiece(humanColor, x2, y2);

                // 이겼나 확인해본다.
                bool ret1 = isEnd(humanColor, x1, y1);
                bool ret2 = isEnd(humanColor, x2, y2);

                // 킬 각 나왔으면
                if(ret1 || ret2)
                {
                    if(weight[y1][x1] != ONE_COM)
                        weight[y1][x1] += 15;
                    if(weight[y2][x2] != ONE_COM)
                        weight[y2][x2] += 15;
                }

                // 다시 원복
                board[y2][x2] = EMPTY;
                board[y1][x1] = EMPTY;
            }
        }
    }

    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            int count[8] = {0, };
            count[0] = countN(humanColor, x, y);
            count[1] = countNE(humanColor, x, y);
            count[2] = countE(humanColor, x, y);
            count[3] = countSE(humanColor, x, y);
            count[4] = countS(humanColor, x, y);
            count[5] = countSW(humanColor, x, y);
            count[6] = countW(humanColor, x, y);
            count[7] = countNW(humanColor, x, y);
            for(int i = 0; i < 8; i++)
            {
                weight[y][x] += count[i];
            }
        }
    }
}

// board[y][x]의 주위의 count 중 max 값
char Connect6AI::getRadialMax(Connect6::Piece color, int x, int y)
{
    int  n = connect6->countN(color, x, y);
    int  s = connect6->countS(color, x, y);
    int  w = connect6->countW(color, x, y);
    int  e = connect6->countE(color, x, y);
    int nw = connect6->countNW(color, x, y);
    int ne = connect6->countNE(color, x, y);
    int sw = connect6->countSW(color, x, y);
    int se = connect6->countSE(color, x, y);

    int  h = max(n, s);
    int  v = max(w, e);
    int rd = max(nw, se);
    int ld = max(ne, sw);

    return max( max(h, v), max(rd, ld) );
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
            if(connect6->board[r][c] != EMPTY)
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

            // 1등보다 크면
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


// ========== private function ==========




// 한 줄만 보자...
void Connect6AI::updateLineWeight(Connect6::Piece boardLine[], char weightLine[], int len)
{
    int  emptyIdx[BOARDSIZE] = {0, };  // 비어있는 칸 인덱스
    int  numOfEmpty = 0;  // 비어있는 칸 개수
    int  numOfai = 0;     // AI 돌 개수
    int  numOfHuman = 0;  // 사람 돌 개수
    for(int i = 0; i < len; i++)
    {
        if(boardLine[i] == Connect6::EMPTY)  // 비어있다면
        {
            emptyIdx[numOfEmpty] = i;
            numOfEmpty++;
        }
        else if(boardLine[i] == aiColor)  // 나의 돌이라면
            numOfai++;
        else  // 사람 돌이라면
            numOfHuman++;
    }

    // 놓을 칸이 없으면 리턴
    if(numOfEmpty == 0)
        return;

    // 아직 킬각이 안 떴었고
    // 1칸 이상 비어있고 4개 이상 내 돌이 있으면
    // 킬각을 살핀다.
    if(isAiKillGak == false)
    {
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
                    if(6 <= count)
                    {
                        weightLine[idxA] = 120;
                        weightLine[idxB] = 120;
                        isAiKillGak = true;
                        break;
                    }
                    // 놓았던거 다시 원복
                    else
                    {
                        boardLine[idxA] = Connect6::EMPTY;
                        boardLine[idxB] = Connect6::EMPTY;
                    }
                }
                if(isAiKillGak)
                    break;
            }
        }
    }  // if(isKillGak == false)

    if(isAiKillGak)
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


// 한 줄만 가져오자...
// [y][x]를 지나가는 각 방향으로 boardLine에 복사.
// len은 유효 길이.
void Connect6AI::copyBoardLineH(int x, int y, Connect6::Piece boardLine[], int* len)
{
    for(int c = 0; c < Connect6::BOARDSIZE; c++)
        boardLine[c] = connect6->board[y][c];
    *len = Connect6::BOARDSIZE;
}
void Connect6AI::copyBoardLineV(int x, int y, Connect6::Piece boardLine[], int* len)
{
    for(int r = 0; r < Connect6::BOARDSIZE; r++)
        boardLine[r] = connect6->board[r][x];
    *len = Connect6::BOARDSIZE;
}
void Connect6AI::copyBoardLineRD(int x, int y, Connect6::Piece boardLine[], int* len)
{
    int idx = 0;
    for(int r = y - min(x, y), c = x - min(x, y);
        r < Connect6::BOARDSIZE && c < Connect6::BOARDSIZE;
        r++, c++)
    {
        boardLine[idx] = connect6->board[r][c];
        idx++;
    }
    *len = idx;
}
void Connect6AI::copyBoardLineLD(int x, int y, Connect6::Piece boardLine[], int* len)
{
    int idx = 0;
    for(int r = max(y-(Connect6::BOARDSIZE-1-x), 0), c = min(x+y, Connect6::BOARDSIZE-1);
        r < Connect6::BOARDSIZE && -1 < c;
        r++, c--)
    {
        boardLine[idx] = connect6->board[r][c];
        idx++;
    }
    *len = idx;
}


// 한 줄만 업데이트...
// [y][x]를 지나가는 각 방향으로 weight를 업데이트. max값.
// len은 유효 길이.
void Connect6AI::pasteWeightLineH(int x, int y, char weightLine[])
{
    for(int c = 0; c < BOARDSIZE; c++)
    {
        if(weight[y][c] < weightLine[c])
            weight[y][c] = weightLine[c];
    }
}
void Connect6AI::pasteWeightLineV(int x, int y, char weightLine[])
{
    for(int r = 0; r < Connect6::BOARDSIZE; r++)
    {
        if(weight[r][x] < weightLine[r])
            weight[r][x] = weightLine[r];
    }
}
void Connect6AI::pasteWeightLineRD(int x, int y, char weightLine[])
{
    int idx = 0;
    for(int r = y - min(x, y), c = x - min(x, y);
        r < Connect6::BOARDSIZE && c < Connect6::BOARDSIZE;
        r++, c++)
    {
        if(weight[r][c] < weightLine[idx])
            weight[r][c] = weightLine[idx];
        idx++;
    }
}
void Connect6AI::pasteWeightLineLD(int x, int y, char weightLine[])
{
    int idx = 0;
    for(int r = max(y-(Connect6::BOARDSIZE-1-x), 0), c = min(x+y, Connect6::BOARDSIZE-1);
        r < Connect6::BOARDSIZE && -1 < c;
        r++, c--)
    {
        if(weight[r][c] < weightLine[idx])
            weight[r][c] = weightLine[idx];
        idx++;
    }
}


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
