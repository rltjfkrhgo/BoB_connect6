#include "Controller.h"

#include <cstring>

Controller::Controller(QObject* parent) : QObject(parent)
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
    setPieceUser = std::bind(&Controller::setPieceNull, this,
                             std::placeholders::_1, std::placeholders::_2);
    setPieceBot = std::bind(&Controller::setPieceNull, this,
                            std::placeholders::_1, std::placeholders::_2);
    std::memset(board, 0, sizeof(Piece)*BOARDSIZE*BOARDSIZE);
    status = READY;
    emit boardChanged();
}

void Controller::startDuo()
{
    setPieceUser = std::bind(&Controller::setPieceDuo, this,
                             std::placeholders::_1, std::placeholders::_2);
    status = START;
    emit boardChanged();
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

    status = START;
    emit boardChanged();
}

void Controller::setPieceNull([[maybe_unused]] int y, [[maybe_unused]] int x)
{
    // do nothing
}

void Controller::setPieceBlack(int y, int x)
{
    setPiece(BLACK, y, x);
}

void Controller::setPieceWhite(int y, int x)
{
    setPiece(WHITE, y, x);
}

void Controller::setPieceDuo(int y, int x)
{
    setPiece(whoseTurn(), y, x);
}

Controller::Piece Controller::whoseTurn() const
{
    switch(status)
    {
    case START:
    case BLACK1:
    case BLACK2:
        return BLACK;
    case WHITE1:
    case WHITE2:
        return WHITE;
    default:
        return EMPTY;
    }
}

Controller::Piece Controller::getBoard(int y, int x) const
{
    return board[y][x];
}

Controller::Status Controller::getStatus() const
{
    return status;
}

void Controller::setPiece(Piece color, int y, int x)
{
    if(whoseTurn() != color)
        return;

    if(board[y][x] != EMPTY)
        return;

    board[y][x] = color;

    if(isEnd(color, y, x))
    {
        if(color == BLACK)
            status = BLACKWIN;
        else if(color == WHITE)
            status = WHITEWIN;
    }
    else
    {
        status = nextStatus(status);
    }

    emit boardChanged();
}

Controller::Status Controller::nextStatus(Status status) const
{
    switch(status)
    {
    case START:
        return WHITE1;
    case BLACK1:
        return BLACK2;
    case BLACK2:
        return WHITE1;
    case WHITE1:
        return WHITE2;
    case WHITE2:
        return BLACK1;
    default:
        return status;
    }
}

bool Controller::isEnd(Piece color, int Y, int X) const
{
    constexpr static int dy[] = {-1, -1, 0, 1, 1,  1,  0, -1};
    constexpr static int dx[] = { 0,  1, 1, 1, 0, -1, -1, -1};

    int cnt[8] = {0};

    for(int i = 0; i < 8; i++)
    {
        int y = Y + dy[i];
        int x = X + dx[i];
        while(0 <= y && y < BOARDSIZE &&
              0 <= x && x < BOARDSIZE &&
              board[y][x] == color)
        {
            cnt[i]++;
            y += dy[i];
            x += dx[i];
        }
    }

    for(int i = 0; i < 4; i++)
    {
        if(6 <= 1+cnt[i]+cnt[i+4])
            return true;
    }

    return false;
}
