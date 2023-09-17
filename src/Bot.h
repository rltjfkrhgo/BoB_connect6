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
    void doWork(Status status);

signals:
    void setPieceBot(const int y, const int x);

private:
    Piece botColor;
    Piece userColor;

    int weight[BOARDSIZE][BOARDSIZE];
};

#endif // BOT_H
