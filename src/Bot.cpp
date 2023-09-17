#include "Bot.h"

#include <cstring>

#include <QtDebug>

#include "Controller.h"

Bot::Bot(Piece _botColor, QObject* parent)
    : QObject(parent), botColor(_botColor)
{
    qDebug() << "Bot()";

    std::memset(board, 0, sizeof(Piece)*BOARDSIZE*BOARDSIZE);
    std::memset(weight, 0, sizeof(int)*BOARDSIZE*BOARDSIZE);
}

Bot::~Bot()
{
    qDebug() << "~Bot()";
}

void Bot::doWork(const Piece color, const int y, const int x)
{
    qDebug() << "doWork()";

    board[y][x] = color;

    if(Controller::getInstance()->whoseTurn() != botColor)
        return;

    // 첫 수는 항상 9, 9.
    if(Controller::getInstance()->getStatus() == START)
    {
        emit setPieceBot(9, 9);
        return;
    }

    // 임시로 빈칸 아무곳에나
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            if(Controller::getInstance()->getBoard(y, x) == EMPTY)
            {
                emit setPieceBot(y, x);
                return;
            }
        }
    }
}
