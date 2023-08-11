#ifndef BOT_H
#define BOT_H

#include <QThread>

#include "Connect6.h"

class Bot : public QThread
{
    Q_OBJECT

public:
    Bot(QObject* parent = nullptr);

protected:
    void run() override;

private:
    Connect6::Piece botColor;
    Connect6::Piece userColor;

    int weight[Connect6::BOARDSIZE][Connect6::BOARDSIZE];
};

#endif // BOT_H
