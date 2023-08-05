#ifndef CONNECT6_H
#define CONNECT6_H

#include <QObject>
#include <functional>

class Connect6 : public QObject
{
    Q_OBJECT

public:
    enum Piece  {EMPTY, BLACK, WHITE};
    enum Status {READY, START, BLACK1, BLACK2, WHITE1, WHITE2, END};

    static Connect6* getInstance();
    void reset();
    void startDuo();
    Piece  getBoard(int y, int x) const;
    Status getStatus() const;
    std::function<void(int, int)> setPiece;

    constexpr static int BOARDSIZE = 19;

signals:
    void boardChanged();

private:
    explicit Connect6(QObject* parent = nullptr);
    bool isEnd(Piece color, int y, int x) const;

    void setPieceNull(int y, int x);
    void setPieceDuo(int y, int x);

    Piece  board[BOARDSIZE][BOARDSIZE];
    Status status;
};

#endif // CONNECT6_H
