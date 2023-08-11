#ifndef BOT_H
#define BOT_H

#include <QThread>

#include "Controller.h"

class Bot : public QThread
{
    Q_OBJECT

public:
    Bot(QObject* parent = nullptr);

protected:
    void run() override;

private:
    Controller::Piece botColor;
    Controller::Piece userColor;

    int weight[Controller::BOARDSIZE][Controller::BOARDSIZE];
};

#endif // BOT_H
