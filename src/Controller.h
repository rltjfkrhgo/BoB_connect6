#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <functional>

class Controller : public QObject
{
    Q_OBJECT

public:
    enum Piece  {EMPTY, BLACK, WHITE};
    enum Status {READY, START, BLACK1, BLACK2, WHITE1, WHITE2,
                 BLACKWIN, WHITEWIN};

    static Controller* getInstance();

    void reset();
    void startDuo();
    void startBot(Piece userColor);

    std::function<void(int, int)> setPieceUser;
    std::function<void(int, int)> setPieceBot;

    Piece  whoseTurn() const;
    Piece  getBoard(int y, int x) const;
    Status getStatus() const;

    constexpr static int BOARDSIZE = 19;

signals:
    void boardChanged();

private:
    explicit Controller(QObject* parent = nullptr);

    void setPieceNull(int y, int x);
    void setPieceBlack(int y, int x);
    void setPieceWhite(int y, int x);
    void setPieceDuo(int y, int x);
    void setPiece(Piece color, int y, int x);

    Status nextStatus(Status status) const;
    bool isEnd(Piece color, int y, int x) const;

    Piece  board[BOARDSIZE][BOARDSIZE];
    Status status;
};

#endif // CONTROLLER_H
