#include "Controller.h"

#include <cstring>

Controller::Controller(QObject* parent) : QObject(parent), connect6()
{
}

Controller* Controller::getInstance()
{
    static Controller instance;
    return &instance;
}

void Controller::reset()
{
    setPieceUser = std::bind(&Controller::setPieceNull, this,
                             std::placeholders::_1, std::placeholders::_2);
    setPieceBot = std::bind(&Controller::setPieceNull, this,
                            std::placeholders::_1, std::placeholders::_2);
    const Status status = connect6.reset();
    emit boardChanged(status);
}

void Controller::startDuo()
{
    setPieceUser = std::bind(&Controller::setPieceDuo, this,
                             std::placeholders::_1, std::placeholders::_2);
    const Status status = connect6.start();
    emit boardChanged(status);
}

void Controller::startBot(Piece userColor)
{
    switch(userColor)
    {
    case BLACK:
        setPieceUser = std::bind(&Controller::setPieceBlack, this,
                                 std::placeholders::_1, std::placeholders::_2);
        setPieceBot = std::bind(&Controller::setPieceWhite, this,
                                std::placeholders::_1, std::placeholders::_2);
        break;
    case WHITE:
        setPieceUser = std::bind(&Controller::setPieceWhite, this,
                                 std::placeholders::_1, std::placeholders::_2);
        setPieceBot = std::bind(&Controller::setPieceBlack, this,
                                std::placeholders::_1, std::placeholders::_2);
        break;
    default:
        break;
    }

    const Status status = connect6.start();
    emit boardChanged(status);
}

void Controller::setPieceNull([[maybe_unused]] int y, [[maybe_unused]] int x)
{
    // do nothing
    emit boardChanged(connect6.getStatus());
}

void Controller::setPieceBlack(int y, int x)
{
    const Status status = connect6.setPiece(BLACK, y, x);
    emit boardChanged(status);
}

void Controller::setPieceWhite(int y, int x)
{
    const Status status = connect6.setPiece(WHITE, y, x);
    emit boardChanged(status);
}

void Controller::setPieceDuo(int y, int x)
{
    const Status status = connect6.setPiece(whoseTurn(), y, x);
    emit boardChanged(status);
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