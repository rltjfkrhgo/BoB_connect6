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
    void copyBoardLineH(int x, int y, Connect6::Piece boardLine[], int* len);
    void copyBoardLineV(int x, int y, Connect6::Piece boardLine[], int* len);
    void copyBoardLineRD(int x, int y, Connect6::Piece boardLine[], int* len);
    void copyBoardLineLD(int x, int y, Connect6::Piece boardLine[], int* len);

    void pasteWeightLineH(int x, int y, char weightLine[]);
    void pasteWeightLineV(int x, int y, char weightLine[]);
    void pasteWeightLineRD(int x, int y, char weightLine[]);
    void pasteWeightLineLD(int x, int y, char weightLine[]);

    char getRadialMax(Piece color, int x, int y);
    char getRadialWeightMax(int x, int y);
    int  max(int a, int b);
    int  min(int a, int b);
    void swap(int* a, int* b);
};

#endif // CONNECT6SOLO_H
