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
    if(status == READY || status == END)
        return;

    if(board[y][x] != EMPTY)
        return;

    switch(status)
    {
    case START:
        board[y][x] = BLACK;
        status = WHITE1;
        emit boardChanged();
        break;
    case BLACK1:
        board[y][x] = BLACK;
        status = BLACK2;
        emit boardChanged();
        break;
    case BLACK2:
        board[y][x] = BLACK;
        status = WHITE1;
        emit boardChanged();
        break;
    case WHITE1:
        board[y][x] = WHITE;
        status = WHITE2;
        emit boardChanged();
        break;
    case WHITE2:
        board[y][x] = WHITE;
        status = BLACK1;
        emit boardChanged();
        break;
    default:
        break;
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
