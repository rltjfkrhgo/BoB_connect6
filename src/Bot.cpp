#include "Bot.h"

#include <QThread>
#include <QtDebug>

#include "Controller.h"

Bot::Bot(Piece _botColor, QObject* parent)
    : QObject(parent), botColor(_botColor), userColor(!_botColor)
{
    qDebug() << "Bot()";
}

Bot::~Bot()
{
    qDebug() << "~Bot()";
}

void Bot::doWork(Status status)
{
    qDebug() << "doWork() " << status;

    if(Controller::getInstance()->whoseTurn() != botColor)
        return;

    // 첫 수는 항상 9, 9.
    if(Controller::getInstance()->getStatus() == START)
    {
        Controller::getInstance()->setPieceBot(9, 9);
        return;
    }

    // 임시로 빈칸 아무곳에나
    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            if(Controller::getInstance()->getBoard(y, x) == EMPTY)
            {
                Controller::getInstance()->setPieceBot(y, x);
                return;
            }
        }
    }
}
