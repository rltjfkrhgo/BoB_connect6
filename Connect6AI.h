#ifndef CONNECT6AI_H
#define CONNECT6AI_H

#include "Connect6.h"

class Connect6AI : public Connect6
{
public:
    Connect6AI(Piece aiColor, Connect6* connect6);

    void putPiece(int x, int y) override;

    void updateWeight();

    char getRadialMax(Connect6::Piece color, int x, int y);
    void getNextPut(int *x1, int *y1, int* x2, int* y2);

private:
    Connect6* connect6;

    Connect6::Piece  aiColor;
    Connect6::Piece  humanColor;

    char  weight[Connect6::BOARDSIZE][Connect6::BOARDSIZE];
    const static char ONE_COM = 120;

    bool isAiKillGak;
    void updateLineWeight(Connect6::Piece boardLine[], char weightLine[], int len);
    void copyBoardLineH(int x, int y, Connect6::Piece boardLine[], int* len);
    void copyBoardLineV(int x, int y, Connect6::Piece boardLine[], int* len);
    void copyBoardLineRD(int x, int y, Connect6::Piece boardLine[], int* len);
    void copyBoardLineLD(int x, int y, Connect6::Piece boardLine[], int* len);

    void pasteWeightLineH(int x, int y, char weightLine[]);
    void pasteWeightLineV(int x, int y, char weightLine[]);
    void pasteWeightLineRD(int x, int y, char weightLine[]);
    void pasteWeightLineLD(int x, int y, char weightLine[]);

    int  max(int a, int b);
    int  min(int a, int b);
    void swap(int* a, int* b);
};

#endif // CONNECT6AI_H
