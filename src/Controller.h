#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "Connect6.h"
#include "Connect6Type.h"

class Controller : public QObject
{
    Q_OBJECT

public:
    static Controller* getInstance();

    void reset();
    void start();

    void setPieceNull(int y, int x);
    void setPieceBlack(int y, int x);
    void setPieceWhite(int y, int x);
    void setPieceDuo(int y, int x);

    Piece  whoseTurn() const;
    Piece  getBoard(int y, int x) const;
    Status getStatus() const;

signals:
    void boardChanged(Piece color, int y, int x);
    void statusChanged(Status status);
    void appendTextEdit(const QString& str);

private:
    explicit Controller(QObject* parent = nullptr);

    Connect6 connect6;
};

#endif // CONTROLLER_H
