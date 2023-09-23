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
    void onBoardChanged(const Piece color, const int y, const int x);
    void onStatusChanged(const Status status);

signals:
    void setPieceBot(const int y, const int x);
    void work();

private:
    void doWork();

    Piece botColor;
    Piece board[BOARDSIZE][BOARDSIZE];
    int weight[BOARDSIZE][BOARDSIZE];
};

#endif // BOT_H
