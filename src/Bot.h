#ifndef BOT_H
#define BOT_H

#include <QThread>

#include "Connect6Type.h"
#include "Controller.h"

class Bot : public QThread
{
    Q_OBJECT

public:
    Bot(QObject* parent = nullptr);

protected:
    void run() override;

private:
    Piece botColor;
    Piece userColor;

    int weight[BOARDSIZE][BOARDSIZE];
};

#endif // BOT_H
