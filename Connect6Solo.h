#ifndef CONNECT6SOLO_H
#define CONNECT6SOLO_H

#include "Connect6.h"
#include "Connect6AI.h"

class Connect6Solo : public Connect6
{
public:
    Connect6Solo(Piece humanColor);
    void putPiece(int x, int y) override;

private:
    Piece aiColor;
    Piece humanColor;

    Connect6AI* ai;

    void autoSetPiece();
};

#endif // CONNECT6SOLO_H
