#include "widget.h"
#include "ui_widget.h"

// 네트워크 관련된 부분
// 따로 분리하고 싶었는데... 잘 안됨 ㅠㅠ

void Widget::on_btnCpuNet_clicked()
{
    //connect6 = new Connect6CpuNet;

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

    ui->labelStatus->setText("게임이 시작되기를 기다리는 중...");

    update();
}

void Widget::recv()
{
    qDebug() << "received packet!!";

    // 소켓으로 부터 읽어온다.
    uchar recvBuff[256] = {0, };
    int ret = socket->read( (char*)recvBuff, sizeof(recvBuff) );
    qDebug() << "ret: " << ret;

    // 헤더 부분 파싱
    struct Connect6ProtocolHdr hdr;
    hdr_parsing(recvBuff, sizeof(recvBuff), &hdr);

    struct GameStartData start;
    struct PutTurnData putTurn;

    uchar   sendBuff[256] = {0, };
    size_t  sendLen = 0;

    switch(hdr.type)
    {
    case GAME_START:
        game_start_data_parsing(recvBuff+sizeof(hdr), sizeof(start), &start);
        playerNum = hdr.player_num;
        qDebug() << "나의 번호: " << playerNum;
        break;

    case PUT:
        ui->labelStatus->setText("");
        put_turn_data_parsing(recvBuff+sizeof(hdr), sizeof(putTurn), &putTurn);
        qDebug() << putTurn.xy[0] << ", " << putTurn.xy[1] << ", " << putTurn.xy[2] << ", " << putTurn.xy[3];
        if(putTurn.coord_num == 2)
        {

        }
        break;

    case TURN:
        ui->labelStatus->setText("당신의 차례입니다.");
        put_turn_data_parsing(recvBuff+sizeof(hdr), sizeof(putTurn), &putTurn);
        qDebug() << "coord_num: " << putTurn.coord_num;
        qDebug() << putTurn.xy[0] << ", " << putTurn.xy[1] << ", " << putTurn.xy[2] << ", " << putTurn.xy[3];
        if(putTurn.coord_num == 2)
        {

        }
        else  // 1개 둔 경우
        {

        }
        update();
        // 내가 둘 차례!

        break;

    case GAME_OVER:
        ui->labelStatus->setText("게임이 끝났습니다.");
        break;
    default:
        break;
    }
}
