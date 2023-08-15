#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QThread>
#include <functional>

#include "Bot.h"
#include "Connect6.h"
#include "Connect6Type.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    static Controller* getInstance();

    void reset();
    void startDuo();
    void startBot(Piece userColor);

    std::function<void(int, int)> setPieceUser;
    std::function<void(int, int)> setPieceBot;

    Piece  whoseTurn() const;
    Piece  getBoard(int y, int x) const;
    Status getStatus() const;

signals:
    void boardChanged(Status status);

private:
    explicit Controller(QObject* parent = nullptr);

    void setPieceNull(int y, int x);
    void setPieceBlack(int y, int x);
    void setPieceWhite(int y, int x);
    void setPieceDuo(int y, int x);

    Connect6 connect6;
    QThread workerThread;
};

#endif // CONTROLLER_H
