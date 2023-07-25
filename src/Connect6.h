#ifndef CONNECT6_H
#define CONNECT6_H

#include <QObject>

class Connect6 : public QObject
{
    Q_OBJECT

public:
    enum Piece {EMPTY, BLACK, WHITE};

    static Connect6* getInstance();
    void resetBoard();
    void setPiece(Piece color, int y, int x);
    Piece getBoard(int y, int x) const;

    constexpr static int BOARDSIZE = 19;

signals:
    void boardChanged();

private:
    explicit Connect6(QObject* parent = nullptr);
    Piece board[BOARDSIZE][BOARDSIZE];
};

#endif // CONNECT6_H
