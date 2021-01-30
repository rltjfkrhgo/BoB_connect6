#include "Connect6CpuNet.h"

Connect6CpuNet::Connect6CpuNet(QString name, QString ip, QString port)
{
    struct GameStartData startData;
    startData.req_res_flag = 0x0;
    startData.name_length = name.length();


    socket.connectToHost(ip, port.toInt());
}

void Connect6CpuNet::putPiece(int x, int y)
{

}
