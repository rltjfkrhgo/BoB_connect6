#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
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

    // 바둑 알 두기
    for(int y = 0; y < 19; y++)
    {
        for(int x = 0; x < 19; x++)
        {
            GoBoard::Piece piece = goBoard.getPiece(x, y);
            if(piece == GoBoard::BLACK)
            {
                painter.setPen(QPen(Qt::black, 35, Qt::SolidLine, Qt::RoundCap));
                painter.drawPoint(x*RECTSIZE+BOARD_X, y*RECTSIZE+BOARD_Y);
            }
            else if(piece == GoBoard::WHITE)
            {
                painter.setPen(QPen(Qt::white, 35, Qt::SolidLine, Qt::RoundCap));
                painter.drawPoint(x*RECTSIZE+BOARD_X, y*RECTSIZE+BOARD_Y);
            }
        }
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    // 격자 근처에서만 반응하게 고쳐야 하는데... 너모 어렵담.
    int x = (event->x() + (RECTSIZE/2) - BOARD_X) / RECTSIZE;
    int y = (event->y() + (RECTSIZE/2) - BOARD_Y) / RECTSIZE;

    ui->lcdX->display(x);
    ui->lcdY->display(y);

    if(x > -1 && x < 19 && y > -1 && y < 19)
    {
        goBoard.setPiece(x, y);
    }

    update();
}
