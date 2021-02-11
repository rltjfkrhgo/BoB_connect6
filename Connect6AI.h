#ifndef CONNECT6AI_H
#define CONNECT6AI_H

#include "Connect6.h"

class Connect6AI : public Connect6
{
public:
    Connect6AI(Piece aiColor, Connect6* connect6);

    void putPiece(int x, int y) override;

    void updateWeight();

    void updateWeight(int x, int y);
    void updateAiWeight(int x, int y);
    void getNextPut(int *x1, int *y1, int* x2, int* y2);

private:
    Connect6* connect6;

    Piece  aiColor;
    Piece  humanColor;

    char  weight[BOARDSIZE][BOARDSIZE];
    char  aiWeight[BOARDSIZE][BOARDSIZE];

    char getRadialMax(Connect6::Piece color, int x, int y);
    int  max(int a, int b);
    void swap(int* a, int* b);
};

#endif // CONNECT6AI_H
