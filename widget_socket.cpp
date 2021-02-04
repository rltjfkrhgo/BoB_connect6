#include "widget.h"
#include "ui_widget.h"

// 네트워크 관련된 부분
// 따로 분리하고 싶었는데... 잘 안됨 ㅠㅠ

void Widget::on_btnCpuNet_clicked()
{
    connect6 = new Connect6CpuNet;

    ui->labelMode->setText("Mode: CPU vs Network");
    ui->btnSoloB->setEnabled(false);
    ui->btnSoloW->setEnabled(false);
    ui->btnDuo->setEnabled(false);
    ui->btnCpuNet->setEnabled(false);

    QString  name = ui->nameInput->text();
    QString    ip = ui->  ipInput->text();
    QString  port = ui->portInput->text();

    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(recv()));

    // 서버에 연결
    socket->connectToHost(ip, port.toInt());

    // 게임 시작 요청
    struct GameStartData startData;
    startData.req_res_flag = 0x0;
    startData.name_length = name.length();
    sprintf(startData.name, "%s", name.toStdString().c_str());

    uchar sendBuff[256] = {0, };
    size_t sendLen;
    make_game_start_payload(sendBuff, sizeof(startData), &sendLen, 0x0, startData);
    socket->write((const char*)sendBuff, sendLen);

    ui->listNet->addItem("게임이 시작되기를 기다리는 중...");
    ui->listWidget->scrollToBottom();
    update();
}

void Widget::recv()
{
    // 소켓으로 부터 읽어온다.
    uchar recvBuff[256] = {0, };
    socket->read( (char*)recvBuff, sizeof(recvBuff) );

    // 헤더 부분 파싱
    struct Connect6ProtocolHdr hdr;
    hdr_parsing(recvBuff, sizeof(recvBuff), &hdr);

    struct PutTurnData putTurn;

    uchar   sendBuff[256] = {0, };
    size_t  sendLen = 0;

    switch(hdr.type)
    {
    case GAME_START:
    {
        struct GameStartData start;
        game_start_data_parsing(recvBuff+sizeof(hdr), sizeof(start), &start);
        playerNum = hdr.player_num;
        if(playerNum == 1)
            ai = new Connect6AI(Connect6::BLACK);
        else
            ai = new Connect6AI(Connect6::WHITE);
        break;
    }

    // PUT을 받는 경우는 첫 수를 대신 뒀을 때만
    // 따지고 보면 내가 둔거임
    case PUT:
    {
        ui->listNet->addItem("게임이 시작되었습니다!");
        put_turn_data_parsing(recvBuff+sizeof(hdr), sizeof(putTurn), &putTurn);
        connect6->putPiece(putTurn.xy[0], putTurn.xy[1]);
        ai->putPiece(putTurn.xy[0], putTurn.xy[1]);
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
            ai->putPiece(putTurn.xy[0], putTurn.xy[1]);
            ai->putPiece(putTurn.xy[2], putTurn.xy[3]);
            ai->updateWeight(putTurn.xy[0], putTurn.xy[1]);
            ai->updateWeight(putTurn.xy[2], putTurn.xy[3]);
        }
        else  // 내가 흰색이면 처음에 저쪽에서 1개만 둠
        {
            connect6->putPiece(putTurn.xy[0], putTurn.xy[1]);
            ai->putPiece(putTurn.xy[0], putTurn.xy[1]);
            ai->updateWeight(putTurn.xy[0], putTurn.xy[1]);
        }
        update();

        // 내가 둘 차례!
        ui->listNet->addItem("당신의 차례입니다.");
        ui->listNet->scrollToBottom();
        int x1, y1, x2, y2;
        ai->getNextPut(&x1, &y1, &x2, &y2);

        connect6->putPiece(x1, y1);
        connect6->putPiece(x2, y2);
        ai->putPiece(x1, y1);
        ai->putPiece(x2, y2);

        time_t t = time(NULL);
        while(time(NULL) - t < 1) {}

        putTurn.coord_num = 2;
        putTurn.xy[0] = x1;
        putTurn.xy[1] = y1;
        putTurn.xy[2] = x2;
        putTurn.xy[3] = y2;
        make_put_payload(sendBuff, sizeof(sendBuff), &sendLen, playerNum, putTurn);
        socket->write((const char*)sendBuff, sendLen);

        ui->listNet->addItem("상대의 차례입니다.");
        ui->listNet->scrollToBottom();
        break;
    }

    case GAME_OVER:
    {
        ui->listNet->addItem("게임이 끝났습니다.");
        ui->listNet->scrollToBottom();
        struct GameOverData over;
        game_over_data_parsing(recvBuff+sizeof(hdr), sizeof(over), &over);
        break;
    }

    default:
        break;
    }
    update();
}
