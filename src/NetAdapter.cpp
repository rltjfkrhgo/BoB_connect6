#include "NetAdapter.h"

#include <QtDebug>

#include <connect6_protocol.h>

#include "Controller.h"

NetAdapter::NetAdapter(QObject* parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    qDebug() << "Net()";

    connect(socket, &QIODevice::readyRead, this, &NetAdapter::onRecv);
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

void NetAdapter::sendPut(int y1, int x1, int y2, int x2)
{
    struct PutTurnData putTurn;
    size_t sendLen;
    // PUT 패킷 전송
    putTurn.coord_num = 2;
    putTurn.xy[0] = x1;
    putTurn.xy[1] = y1;
    putTurn.xy[2] = x2;
    putTurn.xy[3] = y2;
    make_put_payload(reinterpret_cast<unsigned char*>(sendBuff),
                     sizeof(sendBuff), &sendLen, mynumber, putTurn);
    socket->write((const char*)sendBuff, sendLen);
}

void NetAdapter::onRecv()
{
    socket->read(recvBuff, sizeof(recvBuff));

    struct Connect6ProtocolHdr hdr;
    hdr_parsing(reinterpret_cast<unsigned char*>(recvBuff), sizeof(recvBuff), &hdr);

    switch(hdr.type)
    {
    case GAME_START:
        gameStart(hdr);
        break;
    case PUT:
        put(hdr);
        break;
    case TURN:
        turn(hdr);
        break;

    default:
        break;
    }  // switch
}

void NetAdapter::gameStart(const struct Connect6ProtocolHdr& hdr)
{
    struct GameStartData start;
    game_start_data_parsing(
                reinterpret_cast<unsigned char*>(recvBuff)+sizeof(hdr),
                sizeof(start), &start);
    mynumber = hdr.player_num;
    othername = start.name;
    if(mynumber == 1)
    {  // 내가 검정
        emit postGameStart(BLACK, othername);
    }
    else
    {  // 내가 흰색
        emit postGameStart(WHITE, othername);
    }
}

void NetAdapter::put(const struct Connect6ProtocolHdr &hdr)
{
    // bot이 첫수에는 항상 9, 9를 두도록 수정
    /*
    struct PutTurnData putTurn;
    // PUT을 받는 경우는 첫 수를 대신 뒀을 때만
    // 따지고 보면 내가 둔거임
    put_turn_data_parsing(
                reinterpret_cast<unsigned char*>(recvBuff)+sizeof(hdr),
                sizeof(putTurn), &putTurn);
    Controller::getInstance()->setPieceBot(putTurn.xy[1], putTurn.xy[0]);
    */
}

void NetAdapter::turn(const struct Connect6ProtocolHdr &hdr)
{
    struct PutTurnData putTurn;
    // 상대가 둔거 업데이트
    put_turn_data_parsing(
                reinterpret_cast<unsigned char*>(recvBuff)+sizeof(hdr),
                sizeof(putTurn), &putTurn);
    if(putTurn.coord_num == 2)
    {
        Controller::getInstance()->setPieceNet(putTurn.xy[1], putTurn.xy[0]);
        Controller::getInstance()->setPieceNet(putTurn.xy[3], putTurn.xy[2]);
    }
    else  // 내가 흰색이면 처음에 저쪽에서 1개만 둠
    {
        Controller::getInstance()->setPieceNet(putTurn.xy[1], putTurn.xy[0]);
    }
}
