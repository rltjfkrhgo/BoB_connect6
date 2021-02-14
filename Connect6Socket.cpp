#include "Connect6Socket.h"

Connect6Socket::Connect6Socket(QString myname, QString ip, QString port, Connect6* connect6)
{
    memset(recvBuff, 0, BUFFSIZE);
    memset(sendBuff, 0, BUFFSIZE);
    recvLen = 0;
    sendLen = 0;

    this->myname = myname;

    isRunning = true;

    this->connect6 = connect6;
    ai = nullptr;

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(recv()));

    emit sendMsg("연결중...");

    // 서버에 연결
    socket->connectToHost(ip, port.toInt());

    // 게임 시작 요청
    struct GameStartData startData;
    startData.req_res_flag = 0x0;
    startData.name_length = myname.length();
    sprintf(startData.name, "%s", myname.toStdString().c_str());

    size_t sendLen;
    make_game_start_payload(sendBuff, sizeof(startData), &sendLen, 0x0, startData);
    socket->write((const char*)sendBuff, sendLen);

    emit sendMsg("게임이 시작되기를 기다리는 중...");
}

Connect6Socket::~Connect6Socket()
{
    if (socket != nullptr)
        delete socket;
    if (ai != nullptr)
        delete ai;
}

void Connect6Socket::recv()
{
    // 소켓으로 부터 읽어온다.
    socket->read( (char*)recvBuff, sizeof(recvBuff) );

    // 헤더 부분 파싱
    struct Connect6ProtocolHdr hdr;
    hdr_parsing(recvBuff, sizeof(recvBuff), &hdr);

    struct PutTurnData putTurn;

    switch(hdr.type)
    {
    case GAME_START:
    {
        struct GameStartData start;
        game_start_data_parsing(recvBuff+sizeof(hdr), sizeof(start), &start);
        mynumber = hdr.player_num;
        othername = start.name;
        if(mynumber == 1)
        {  // 내가 검정
            ai = new Connect6AI(Connect6::BLACK, connect6);
            msg = "● " + myname + " vs " + othername + " ○\n";
            emit sendMsg(msg);
        }
        else
        {  // 내가 흰색
            ai = new Connect6AI(Connect6::WHITE, connect6);
            msg = "○ " + myname + " vs " + othername + " ●\n";
            emit sendMsg(msg);
        }
        break;
    }

    // PUT을 받는 경우는 첫 수를 대신 뒀을 때만
    // 따지고 보면 내가 둔거임
    case PUT:
    {
        put_turn_data_parsing(recvBuff+sizeof(hdr), sizeof(putTurn), &putTurn);
        connect6->putPiece(putTurn.xy[0], putTurn.xy[1]);
        emit sendMsg(msg + "상대가 수를 두는 중...");
        break;
    }

    case TURN:
    {
        // 상대가 둔거 업데이트
        put_turn_data_parsing(recvBuff+sizeof(hdr), sizeof(putTurn), &putTurn);
        if(putTurn.coord_num == 2)
        {
            connect6->putPiece(putTurn.xy[0], putTurn.xy[1]);
            connect6->putPiece(putTurn.xy[2], putTurn.xy[3]);
            ai->updateWeight();
        }
        else  // 내가 흰색이면 처음에 저쪽에서 1개만 둠
        {
            connect6->putPiece(putTurn.xy[0], putTurn.xy[1]);
            ai->updateWeight();
        }

        // 내가 둘 차례!
        emit sendMsg(msg + "내가 수를 두는 중...");

        int x1, y1, x2, y2;
        ai->getNextPut(&x1, &y1, &x2, &y2);

        time_t t = time(NULL);
        while(time(NULL) - t < 1) {}

        connect6->putPiece(x1, y1);
        connect6->putPiece(x2, y2);

        // PUT 패킷 전송
        putTurn.coord_num = 2;
        putTurn.xy[0] = x1;
        putTurn.xy[1] = y1;
        putTurn.xy[2] = x2;
        putTurn.xy[3] = y2;
        make_put_payload(sendBuff, sizeof(sendBuff), &sendLen, mynumber, putTurn);
        socket->write((const char*)sendBuff, sendLen);

        emit sendMsg(msg + "상대가 수를 두는 중...");
        break;
    }

    case GAME_OVER:
    {
        struct GameOverData over;
        game_over_data_parsing(recvBuff+sizeof(hdr), sizeof(over), &over);
        if(hdr.player_num == mynumber)
            emit sendMsg("이겼어요!!");
        else
            emit sendMsg("졌어요 ㅠㅠ");
        isRunning = false;
        break;
    }

    default:
        break;
    }  // switch
}
