#include "Connect6.h"

#include <cstring>

Connect6::Connect6()
{
    reset();
}

Piece Connect6::whoseTurn() const
{
    switch(status)
    {
    case START:
    case BLACK1:
    case BLACK2:
        return BLACK;
    case WHITE1:
    case WHITE2:
        return WHITE;
    default:
        return EMPTY;
    }
}

Piece Connect6::getBoard(int y, int x) const
{
    return board[y][x];
}

Status Connect6::reset()
{
    std::memset(board, 0, sizeof(Piece)*BOARDSIZE*BOARDSIZE);
    status = READY;
    return status;
}

Status Connect6::start()
{
    status = START;
    return status;
}

Status Connect6::getStatus() const
{
    return status;
}

Status Connect6::setPiece(Piece color, int y, int x)
{
    if(whoseTurn() != color)
        return status;

    if(board[y][x] != EMPTY)
        return status;

    board[y][x] = color;

    if(isEnd(color, y, x))
    {
        if(color == BLACK)
            status = BLACKWIN;
        else if(color == WHITE)
            status = WHITEWIN;
    }
    else
    {
        status = nextStatus(status);
    }
    return status;
}

bool Connect6::isEnd(Piece color, int Y, int X) const
{
    constexpr static int dy[] = {-1, -1, 0, 1, 1,  1,  0, -1};
    constexpr static int dx[] = { 0,  1, 1, 1, 0, -1, -1, -1};

    int cnt[8] = {0};

    for(int i = 0; i < 8; i++)
    {
        int y = Y + dy[i];
        int x = X + dx[i];
        while(0 <= y && y < BOARDSIZE &&
              0 <= x && x < BOARDSIZE &&
              board[y][x] == color)
        {
            cnt[i]++;
            y += dy[i];
            x += dx[i];
        }
    }

    for(int i = 0; i < 4; i++)
    {
        if(6 <= 1+cnt[i]+cnt[i+4])
            return true;
    }

    return false;
}

Status Connect6::nextStatus(Status status) const
{
    switch(status)
    {
    case START:
        return WHITE1;
    case BLACK1:
        return BLACK2;
    case BLACK2:
        return WHITE1;
    case WHITE1:
        return WHITE2;
    case WHITE2:
        return BLACK1;
    default:
        return status;
    }
}
