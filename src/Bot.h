#ifndef BOT_H
#define BOT_H

#include <QObject>

#include "Connect6Type.h"

class Bot : public QObject
{
    Q_OBJECT

public:
    Bot(Piece _botColor, QObject* parent = nullptr);
    ~Bot();

public slots:
    void doWork(const Piece color, const int y, const int x);

signals:
    void setPieceBot(const int y, const int x);

private:
    Piece botColor;
    Piece board[BOARDSIZE][BOARDSIZE];
    int weight[BOARDSIZE][BOARDSIZE];
};

#endif // BOT_H
