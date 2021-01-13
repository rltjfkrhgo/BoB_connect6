// 카운트 함수

#include "Connect6.h"

int Connect6::countN(Piece color, int x, int y)
{
    int count = 0;
    for(y = y-1; y > -1; y--)
    {
        if(board[y][x] != color)
            break;
        count++;
    }
    return count;
}
int Connect6::countS(Piece color, int x, int y)
{
    int count = 0;
    for(y = y+1; y < BOARDSIZE; y++)
    {
        if(board[y][x] != color)
            break;
        count++;
    }
    return count;
}
int Connect6::countE(Piece color, int x, int y)
{
    int count = 0;
    for(x = x+1; x < BOARDSIZE; x++)
    {
        if(board[y][x] != color)
            break;
        count++;
    }
    return count;
}
int Connect6::countW(Piece color, int x, int y)
{
    int count = 0;
    for(x = x-1; x > -1; x--)
    {
        if(board[y][x] != color)
            break;
        count++;
    }
    return count;
}
int Connect6::countNW(Piece color, int x, int y)
{
    int count = 0;
    for(x = x-1, y = y-1; x > -1 && y > -1; x--, y--)
    {
        if(board[y][x] != color)
            break;
        count++;
    }
    return count;
}
int Connect6::countNE(Piece color, int x, int y)  // ↗
{
    int count = 0;
    for(x = x+1, y = y-1; x < BOARDSIZE && y > -1; x++, y--)
    {
        if(board[y][x] != color)
            break;
        count++;
    }
    return count;
}
int Connect6::countSW(Piece color, int x, int y)  // ↙
{
    int count = 0;
    for(x = x-1, y = y+1; x > -1 && y < 19; x--, y++)
    {
        if(board[y][x] != color)
            break;
        count++;
    }
    return count;
}
int Connect6::countSE(Piece color, int x, int y)  // ↘
{
    int count = 0;
    for(x = x+1, y = y+1; x < 19 && y < 19; x++, y++)
    {
        if(board[y][x] != color)
            break;
        count++;
    }
    return count;
}


// 해당 색상이 x, y에 놓아서
// 방향으로 몇 개 놓여 있는가?
int Connect6::countH(Piece color, int x, int y)
{
    int count = 1;
    count += countW(color, x, y);
    count += countE(color, x, y);
    return count;
}

int Connect6::countV(Piece color, int x, int y)
{
    int count = 1;
    count += countN(color, x, y);
    count += countS(color, x, y);
    return count;
}

int Connect6::countRD(Piece color, int x, int y)  // right down
{
    int count = 1;
    count += countNW(color, x, y);
    count += countSE(color, x, y);
    return count;
}

int Connect6::countLD(Piece color, int x, int y)  // left down
{
    int count = 1;
    count += countNE(color, x, y);
    count += countSW(color, x, y);
    return count;
}
