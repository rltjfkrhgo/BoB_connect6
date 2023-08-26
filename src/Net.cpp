#include "Net.h"

#include <QtDebug>

#include <connect6_protocol.h>

#include "Controller.h"

Net::Net(QObject* parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    qDebug() << "Net()";

    connect(socket, &QIODevice::readyRead, this, &Net::recv);
}

Net::~Net()
{
    qDebug() << "~Net()";
}

void Net::sendGameStart(const QString &myname, const QString &ip, const QString &port)
{
    socket->connectToHost(ip, port.toInt());

    struct GameStartData startData;
    startData.req_res_flag = 0x0;
    startData.name_length = myname.length();
    sprintf(startData.name, "%s", myname.toStdString().c_str());

    size_t sendLen;
    make_game_start_payload(reinterpret_cast<unsigned char*>(sendBuff),
                            sizeof(startData), &sendLen, 0x0, startData);
    socket->write(sendBuff, sendLen);
}

void Net::recv()
{
    socket->read(recvBuff, sizeof(recvBuff));

    struct Connect6ProtocolHdr hdr;
    hdr_parsing(reinterpret_cast<unsigned char*>(recvBuff), sizeof(recvBuff), &hdr);

}

void Net::send()
{

}
