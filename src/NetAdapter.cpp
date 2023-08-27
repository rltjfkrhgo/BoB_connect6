#include "NetAdapter.h"

#include <QtDebug>

#include <connect6_protocol.h>

#include "Controller.h"

NetAdapter::NetAdapter(QObject* parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    qDebug() << "Net()";

    connect(socket, &QIODevice::readyRead, this, &NetAdapter::recv);
}

NetAdapter::~NetAdapter()
{
    qDebug() << "~Net()";
}

void NetAdapter::sendGameStart(const QString &myname, const QString &ip, const QString &port)
{
    socket->connectToHost(ip, port.toInt());

    struct GameStartData startData;
    startData.req_res_flag = GAME_START;
    startData.name_length = myname.length();
    sprintf(startData.name, "%s", myname.toStdString().c_str());

    size_t sendLen;
    make_game_start_payload(reinterpret_cast<unsigned char*>(sendBuff),
                            sizeof(startData), &sendLen, 0x0, startData);
    socket->write(sendBuff, sendLen);
}

void NetAdapter::recv()
{
    socket->read(recvBuff, sizeof(recvBuff));

    struct Connect6ProtocolHdr hdr;
    hdr_parsing(reinterpret_cast<unsigned char*>(recvBuff), sizeof(recvBuff), &hdr);

    switch(hdr.type)
    {
    case GAME_START:
        recvGameStart(hdr);
        break;


    default:
        break;
    }  // switch
}

void NetAdapter::send()
{

}

void NetAdapter::recvGameStart(const struct Connect6ProtocolHdr& hdr)
{
    struct GameStartData start;
    game_start_data_parsing(
                reinterpret_cast<unsigned char*>(recvBuff)+sizeof(hdr),
                sizeof(start), &start);
    mynumber = hdr.player_num;
    othername = start.name;
    if(mynumber == 1)
    {  // 내가 검정
    }
    else
    {  // 내가 흰색
    }
}
