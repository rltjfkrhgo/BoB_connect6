#include "Connect6CpuNet.h"
#include <iostream>

Connect6CpuNet::Connect6CpuNet()
{
    status = START;
}

void Connect6CpuNet::putPiece(int x, int y)
{
    // 첫 수
    if(status == START)
    {
        setPiece(BLACK, x, y);
    }
    // 검정 차례
    else if(status == BLACK1 || status == BLACK2)
    {
        setPiece(BLACK, x, y);
    }
    // 흰색 차례
    else if(status == WHITE1 || status == WHITE2)
    {
        setPiece(WHITE, x, y);
    }

    changeTurn();
}
