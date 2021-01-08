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
    for(x = y-1; x > -1; x--)
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