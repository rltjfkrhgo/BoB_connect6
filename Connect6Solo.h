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

    void autoSetPiece();
    void updateWeight(Piece color, int x, int y);

    void swap(int* a, int* b);
};

#endif // CONNECT6SOLO_H
