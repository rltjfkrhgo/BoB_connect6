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

void Connect6::setPiece(Piece color, int y, int x)
{
    board[y][x] = color;
    emit boardChanged();
}

Connect6::Piece Connect6::getBoard(int y, int x) const
{
    return board[y][x];
}
