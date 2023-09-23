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

void Bot::onBoardChanged(const Piece color, const int y, const int x)
{
    qDebug() << "Bot::onBoardChanged()";
    board[y][x] = color;
}

void Bot::onStatusChanged(const Status status)
{
    qDebug() << "Bot::onStatusChanged()";
    switch(status)
    {
    case START:
        if(BLACK == botColor)
            emit setPieceBot(9, 9);
        break;
    case BLACK1:
        if(BLACK == botColor)
            doWork();
        break;
    case WHITE1:
        if(WHITE == botColor)
            doWork();
        break;
    default:
        break;
    }
}

void Bot::doWork()
{
    qDebug() << "doWork()";

    int cnt = 0;

    // 임시로 빈칸 아무곳에나
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            if(Controller::getInstance()->getBoard(y, x) == EMPTY)
            {
                emit setPieceBot(y, x);
                cnt++;
                if(cnt == 2)
                    return;
            }
        }
    }
}
