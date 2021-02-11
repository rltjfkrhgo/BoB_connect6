#ifndef CONNECT6SOLO_H
#define CONNECT6SOLO_H

#include "Connect6.h"

class Connect6Solo : public Connect6
{
public:
    enum Who {CPU, HUMAN};

    Connect6Solo(Piece userColor);

    void putPiece(int x, int y) override;

private:
    Piece cpuColor;
    Piece userColor;
    Who   turn;

    char weight[BOARDSIZE][BOARDSIZE];

    void autoSetPiece();
    void updateWeight(Piece color, int x, int y);
    void updateWeight();

    char getRadialMax(Piece color, int x, int y);
    char getRadialWeightMax(int x, int y);
    int  max(int a, int b);
    void swap(int* a, int* b);
};

#endif // CONNECT6SOLO_H
