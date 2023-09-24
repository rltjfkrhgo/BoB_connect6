#include "Bot.h"

#include <algorithm>
#include <cstring>

#include <QtDebug>

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
    weight[y][x] = 0;

    if(color == !botColor)
    {
        updateWeight(color, y, x);
    }
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

void Bot::updateWeight(const Piece color, const int Y, const int X)
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
        int y = Y + dy[i]*(1+cnt[i]);
        int x = X + dx[i]*(1+cnt[i]);
        if(0 <= y && y < BOARDSIZE &&
           0 <= x && x < BOARDSIZE &&
           EMPTY == board[y][x])
        {
            weight[y][x] = std::max(weight[y][x], 1+cnt[i]+cnt[i+4]);
        }

        y = Y + dy[i+4]*(cnt[i+4]+1);
        x = X + dx[i+4]*(cnt[i+4]+1);
        if(0 <= y && y < BOARDSIZE &&
           0 <= x && x < BOARDSIZE &&
           EMPTY == board[y][x])
        {
            weight[y][x] = std::max(weight[y][x], 1+cnt[i]+cnt[i+4]);
        }
    }
}

void Bot::doWork()
{
    qDebug() << "doWork()";

    for(int y = 0; y < BOARDSIZE; y++)
    {
        QString str;
        for(int x = 0; x < BOARDSIZE; x++)
            str = str + (weight[y][x]+'0') + " ";
        qDebug() << str;
    }

    struct Weight{
        int weight = 0;
        int y = 0;
        int x = 0;
    } max1, max2;

    for(int y = 0; y < BOARDSIZE; y++)
    {
        for(int x = 0; x < BOARDSIZE; x++)
        {
            if(board[y][x] == EMPTY)
            {
                if(max2.weight < weight[y][x])
                {
                    max2.weight = weight[y][x];
                    max2.y = y;
                    max2.x = x;

                    if(max1.weight < max2.weight)
                    {
                        max2.weight = max1.weight;
                        max2.y = max1.y;
                        max2.x = max1.x;
                        max1.weight = weight[y][x];
                        max1.y = y;
                        max1.x = x;
                    }
                }
            }
        }
    }

    emit setPieceBot(max1.y, max1.x);
    emit setPieceBot(max2.y, max2.x);
}
