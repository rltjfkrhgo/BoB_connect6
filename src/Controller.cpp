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
    botThread.quit();
    botThread.wait();

    setPieceUser = std::bind(&Controller::setPieceNull, this,
                             std::placeholders::_1, std::placeholders::_2);
    setPieceBot = std::bind(&Controller::setPieceNull, this,
                            std::placeholders::_1, std::placeholders::_2);

    connect6.reset();

    emit statusChanged(connect6.getStatus());
}

void Controller::start()
{
    connect6.start();
    emit statusChanged(connect6.getStatus());
}

void Controller::startDuo()
{
    setPieceUser = std::bind(&Controller::setPieceDuo, this,
                             std::placeholders::_1, std::placeholders::_2);
    connect6.start();
    emit statusChanged(connect6.getStatus());
}

void Controller::startBot(Piece userColor)
{
    Bot* bot = new Bot(!userColor);
    bot->moveToThread(&botThread);
    connect(&botThread, &QThread::finished, bot, &QObject::deleteLater);
    qRegisterMetaType<Status>("Status");
    connect(this, &Controller::statusChanged, bot, &Bot::doWork);
    botThread.start();

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
