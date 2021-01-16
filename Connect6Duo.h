#ifndef CONNECT6DUO_H
#define CONNECT6DUO_H

#include "Connect6.h"

class Connect6Duo : public Connect6
{
public:
    Connect6Duo();

    void putPiece(int x, int y) override;
};

#endif // CONNECT6DUO_H
