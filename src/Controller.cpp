#include "Controller.h"

#include <cstring>

Controller::Controller(QObject* parent) : QObject(parent), connect6()
{
    reset();
}

Controller* Controller::getInstance()
{
    static Controller instance;
    return &instance;
}

void Controller::reset()
{
    connect6.reset();
    emit statusChanged(connect6.getStatus());
}

void Controller::start()
{
    connect6.start();
    emit statusChanged(connect6.getStatus());
}

void Controller::setPieceNull([[maybe_unused]] int y, [[maybe_unused]] int x)
{
    // do nothing
    // emit boardChanged(connect6.getStatus());
}

void Controller::setPieceBlack(int y, int x)
{
    if(connect6.setPiece(BLACK, y, x))
    {
        emit boardChanged(BLACK, y, x);
        emit statusChanged(connect6.getStatus());
    }
}

void Controller::setPieceWhite(int y, int x)
{
    if(connect6.setPiece(WHITE, y, x))
    {
        emit boardChanged(WHITE, y, x);
        emit statusChanged(connect6.getStatus());
    }
}

void Controller::setPieceDuo(int y, int x)
{
    const Piece color = connect6.whoseTurn();
    if(connect6.setPiece(color, y, x))
    {
        emit boardChanged(color, y, x);
        emit statusChanged(connect6.getStatus());
    }
}

Piece Controller::whoseTurn() const
{
    return connect6.whoseTurn();
}

Piece Controller::getBoard(int y, int x) const
{
    return connect6.getBoard(y, x);
}

Status Controller::getStatus() const
{
    return connect6.getStatus();
}
