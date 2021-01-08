#include "GoBoard.h"

GoBoard::GoBoard()
{
    for(int y = 0; y < 19; y++)
    {
        for(int x = 0; x < 19; x++)
        {
            board[y][x] = EMPTY;
        }
    }

    turn = BLACK;
}

bool GoBoard::isEmpty(int x, int y)
{
    return board[y][x] == EMPTY;
}

void GoBoard::resetBoard()
{
    for(int y = 0; y < 19; y++)
    {
        for(int x = 0; x < 19; x++)
        {
            board[y][x] = EMPTY;
        }
    }

    turn = BLACK;
}

// x, y에 color 돌을 놓는다.
// 바둑판 벗어나면 -1
// 이미 돌이 놓여져 있으면 -1
// 돌을 놓으면 0
int GoBoard::setPiece(Piece color, int x, int y)
{
    if(x < -1 || x > BOARDSIZE
    || y < -1 || y > BOARDSIZE)
        return -1;
    if(board[y][x] != EMPTY)
        return -1;

    board[y][x] = color;
    return 0;
}

GoBoard::Piece GoBoard::getPiece(int x, int y)
{
    return board[y][x];
}

void GoBoard::changeTurn()
{
    if(turn == BLACK)
        turn = WHITE;
    else if(turn == WHITE)
        turn = BLACK;
}

GoBoard::Piece GoBoard::getTurn()
{
    return turn;
}


bool GoBoard::checkGameOver(Piece color, int x, int y)
{

}

// ================================================================

int GoBoard::countN(Piece color, int x, int y)
{
    int count = 0;
    int r = 0;
    for(r = y-1; r > -1; r--)
    {
        if(board[r][x] != color)
            break;
        count++;
    }
    return count;
}
int GoBoard::countS(Piece color, int x, int y)
{
    int count = 0;
    int r = 0;
    for(r = y+1; r < 19; r++)
    {
        if(board[r][x] != color)
            break;
        count++;
    }
    return count;
}
int GoBoard::countE(Piece color, int x, int y)
{
    int count = 0;
    int c = 0;
    for(c = y+1; c < 19; c++)
    {
        if(board[y][c] != color)
            break;
        count++;
    }
    return count;
}
int GoBoard::countW(Piece color, int x, int y)
{
    int count = 0;
    int c = 0;
    for(c = y-1; c > -1; c--)
    {
        if(board[y][c] != color)
            break;
        count++;
    }
    return count;
}
int GoBoard::countNW(Piece color, int x, int y)
{
    int count = 0;
    int c = 0;
    int r = 0;
    for(c = x-1, r = y-1; c > -1 && r > -1; c--, r--)
    {
        if(board[y][c] != color)
            break;
        count++;
    }
    return count;
}
int GoBoard::countNE(Piece color, int x, int y)  // ↗
{
    int count = 0;
    for(x = x+1, y = y-1; x < 19 && y > -1; x++, y--)
    {
        if(board[y][x] != color)
            break;
        count++;
    }
    return count;
}
int GoBoard::countSW(Piece color, int x, int y)  // ↙
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
int GoBoard::countSE(Piece color, int x, int y)  // ↘
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

// ================================================================

// 해당 색상이 x, y에 놓아서
// 방향으로 몇 개 놓여 있는가?
int GoBoard::countH(Piece color, int x, int y)
{
    int count = 1;

    for(int c = x-1; c > -1; c--)
    {
        if(board[y][c] != color)
            break;
        count++;
    }

    for(int c = x+1; c < 19; c++)
    {
        if(board[y][c] != color)
            break;
        count++;
    }

    return count;
}

int GoBoard::countV(Piece color, int x, int y)
{
    int count = 1;

    for(int r = y-1; r > -1; r--)
    {
        if(board[r][x] != color)
            break;
        count++;
    }

    for(int r = y+1; r < 19; r++)
    {
        if(board[r][x] != color)
            break;
        count++;
    }

    return count;
}

int GoBoard::countRD(Piece color, int x, int y)  
{
    int count = 1;

    int c = 0;
    int r = 0;

    for(c = x-1, r = y-1; c > -1 && r > -1; c--, r--)
    {
        if(board[y][c] != color)
            break;
        count++;
    }

    for(c = x+1, r = y+1; c < 19 && r < 19; c++, r++)
    {
        if(board[y][c] != color)
            break;
        count++;
    }

    return count;
}

int GoBoard::countLD(Piece color, int x, int y)
{
    int count = 1;
    count += countNE(color, x, y);
    count += countSW(color, x, y);
    return count;
}
