#include "Connect6.h"

#include <cstring>

Connect6::Connect6(QObject* parent) : QObject(parent)
{
    reset();
}

Connect6* Connect6::getInstance()
{
    static Connect6 instance;
    return &instance;
}

void Connect6::reset()
{
    std::memset(board, 0, sizeof(Piece)*BOARDSIZE*BOARDSIZE);
    status = READY;
    emit boardChanged();
}

void Connect6::startDuo()
{
    status = START;
    emit boardChanged();
}

void Connect6::setPiece(int y, int x)
{
    if(status != START  &&
       status != BLACK1 && status != BLACK2 &&
       status != WHITE1 && status != WHITE2)
        return;

    if(board[y][x] != EMPTY)
        return;

    switch(status)
    {
    case START:
        board[y][x] = BLACK;
        status = WHITE1;
        break;
    case BLACK1:
        board[y][x] = BLACK;
        status = BLACK2;
        break;
    case BLACK2:
        board[y][x] = BLACK;
        status = WHITE1;
        break;
    case WHITE1:
        board[y][x] = WHITE;
        status = WHITE2;
        break;
    case WHITE2:
        board[y][x] = WHITE;
        status = BLACK1;
        break;
    default:
        break;
    }

    if(isEnd(board[y][x], y, x))
    {
        switch(whoTurn())
        {
        case BLACK:
            status = BLACKWIN;
            break;
        case WHITE:
            status = WHITEWIN;
            break;
        default:
            break;
        }
    }

    emit boardChanged();
}

Connect6::Piece Connect6::whoTurn() const
{
    switch(status)
    {
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

Connect6::Piece Connect6::getBoard(int y, int x) const
{
    return board[y][x];
}

Connect6::Status Connect6::getStatus() const
{
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
