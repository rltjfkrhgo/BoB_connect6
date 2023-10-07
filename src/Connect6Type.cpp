#include "Connect6Type.h"

Piece operator!(Piece piece)
{
    switch(piece)
    {
    case BLACK:
        return WHITE;
    case WHITE:
        return BLACK;
    default:
        return piece;
    }
}
