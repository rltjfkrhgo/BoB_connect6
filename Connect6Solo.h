#ifndef CONNECT6SOLO_H
#define CONNECT6SOLO_H

#include "Connect6.h"

class Connect6Solo : public Connect6
{
public:
    enum Who {CPU, HUMAN};

    Connect6Solo(Piece humanColor);

    void putPiece(int x, int y) override;

private:
    Piece aiColor;
    Piece humanColor;
    Who   turn;

    char weight[BOARDSIZE][BOARDSIZE];

    void autoSetPiece();
    void updateWeight(Piece color, int x, int y);
    void updateWeight();

    bool isKillGak;
    void updateLineWeight(Connect6::Piece boardLine[], char weightLine[], int len);
    void getBoardLineH(int x, int y, Connect6::Piece boardLine[], int* len);
    void getBoardLineV(int x, int y, Connect6::Piece boardLine[], int* len);
    void getBoardLineRD(int x, int y, Connect6::Piece boardLine[], int* len);
    void getBoardLineLD(int x, int y, Connect6::Piece boardLine[], int* len);

    char getRadialMax(Piece color, int x, int y);
    char getRadialWeightMax(int x, int y);
    int  max(int a, int b);
    int  min(int a, int b);
    void swap(int* a, int* b);
};

#endif // CONNECT6SOLO_H
