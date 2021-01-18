#ifndef CONNECT6SOLO_H
#define CONNECT6SOLO_H

#include "Connect6.h"

class Connect6Solo : public Connect6
{
public:
    Connect6Solo(Piece color);

    void putPiece(int x, int y) override;

private:
    Piece cpuColor;
    Piece userColor;

    char weight[BOARDSIZE][BOARDSIZE];

    void autoSetPiece(int x1, int y1, int x2, int y2);
    void updateWeight(Piece color, int x, int y);
};

#endif // CONNECT6SOLO_H
