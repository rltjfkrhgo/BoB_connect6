#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    ui->labelMode->setText("Mode:");
    connect6 = nullptr;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 바둑판 배경
    painter.fillRect(BOARD_X-BOARD_OFFSET, BOARD_Y-BOARD_OFFSET, BOARDSIZE, BOARDSIZE, Qt::darkYellow);

    // 바둑판 칸 그리기
    painter.setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap));
    for(int y = 0; y < 18; y++)
    {
        for(int x = 0; x < 18; x++)
        {
            painter.drawRect(x*RECTSIZE+BOARD_X, y*RECTSIZE+BOARD_Y, RECTSIZE, RECTSIZE);
        }
    }

    // 점 찍기
    int point[] = {3, 9, 15};
    painter.setPen(QPen(Qt::black, 8, Qt::SolidLine, Qt::RoundCap));
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 3; x++)
        {
            painter.drawPoint(point[x]*RECTSIZE+BOARD_X, point[y]*RECTSIZE+BOARD_Y);
        }
    }

    if(connect6 == nullptr)
        return;

    // 바둑 알 두기
    for(int y = 0; y < 19; y++)
    {
        for(int x = 0; x < 19; x++)
        {
            Connect6::Piece piece = connect6->getPiece(x, y);
            if(piece == Connect6::BLACK)
            {
                painter.setPen(QPen(Qt::black, 35, Qt::SolidLine, Qt::RoundCap));
                painter.drawPoint(x*RECTSIZE+BOARD_X, y*RECTSIZE+BOARD_Y);
            }
            else if(piece == Connect6::WHITE)
            {
                painter.setPen(QPen(Qt::white, 35, Qt::SolidLine, Qt::RoundCap));
                painter.drawPoint(x*RECTSIZE+BOARD_X, y*RECTSIZE+BOARD_Y);
            }
        }
    }

    // 상태 표시
    switch(connect6->getStatus())
    {
    case Connect6::READY:
        ui->labelStatus->setText("Status: READY");
        break;
    case Connect6::START:
        ui->labelStatus->setText("Status: START");
        break;
    case Connect6::ING:
        ui->labelStatus->setText("Status: ING");
        break;
    case Connect6::END:
        ui->labelStatus->setText("Status: END");
        break;
    }

    // 턴 표시
    Connect6::Piece piece = connect6->whosTurn();
    if(piece == Connect6::BLACK)
    {
        painter.setPen(QPen(Qt::black, 35, Qt::SolidLine, Qt::RoundCap));
    }
    else if(piece == Connect6::WHITE)
    {
        painter.setPen(QPen(Qt::white, 35, Qt::SolidLine, Qt::RoundCap));
    }
    painter.drawPoint(TURN_X, TURN_Y);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    // 격자 근처에서만 반응하게 고쳐야 하는데... 너모 어렵담.
    int x = (event->x() + (RECTSIZE/2) - BOARD_X) / RECTSIZE;
    int y = (event->y() + (RECTSIZE/2) - BOARD_Y) / RECTSIZE;

    ui->lcdX->display(event->x());
    ui->lcdY->display(event->y());

    if(connect6 == nullptr)
        return;

    connect6->putPiece(x, y);
    update();
}

void Widget::on_btnReset_clicked()
{
    if(connect6 != nullptr)
    {
        delete connect6;
        connect6 = nullptr;
    }

    ui->labelMode->setText("Mode:");
    ui->labelStatus->setText("Status:");
    ui->btnSoloB->setEnabled(true);
    ui->btnSoloW->setEnabled(true);
    ui->btnDuo->setEnabled(true);
    ui->btnCpuNet->setEnabled(true);

    update();
}

void Widget::on_btnDuo_clicked()
{
    connect6 = new Connect6Duo;

    ui->labelMode->setText("Mode: DUO");
    ui->btnSoloB->setEnabled(false);
    ui->btnSoloW->setEnabled(false);
    ui->btnDuo->setEnabled(false);
    ui->btnCpuNet->setEnabled(false);

    update();
}
/*
void Widget::on_btnSoloB_clicked()
{
    ui->labelMode->setText("Mode: SOLO");
    connect6->startSoloB();
    ui->btnSoloB->setEnabled(false);
    ui->btnSoloW->setEnabled(false);
    ui->btnDuo->setEnabled(false);
    ui->btnCpuNet->setEnabled(false);
    update();
}

void Widget::on_btnSoloW_clicked()
{
    ui->labelMode->setText("Mode: SOLO");
    connect6->startSoloW();
    ui->btnSoloB->setEnabled(false);
    ui->btnSoloW->setEnabled(false);
    ui->btnDuo->setEnabled(false);
    ui->btnCpuNet->setEnabled(false);
    update();
}
*/
