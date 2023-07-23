#include "RenderArea.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtDebug>

#include "Connect6.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent), blackImg(":/img/mushroom.png"), whiteImg(":/img/slime.png")
{

}

QSize RenderArea::sizeHint() const
{
    return QSize(456, 456);
}

void RenderArea::mousePressEvent(QMouseEvent* event)
{
    const int x = event->x() / RECTSIZE;
    const int y = event->y() / RECTSIZE;

    Connect6::getInstance()->setPiece(Connect6::BLACK, y, x);

    update();
}

void RenderArea::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);

    // 바둑판 배경
    painter.fillRect(0, 0, 456, 456, Qt::white);

    // 바둑판 칸 그리기
    painter.setPen(QPen(Qt::lightGray, 1, Qt::SolidLine, Qt::RoundCap));
    for(int y = 0; y < 18; y++)
    {
        for(int x = 0; x < 18; x++)
        {
            painter.drawRect(RECTSIZE/2 + x*RECTSIZE,
                             RECTSIZE/2 + y*RECTSIZE,
                             RECTSIZE,
                             RECTSIZE);
        }
    }

    // 점 찍기
    int point[] = {3, 9, 15};
    painter.setPen(QPen(Qt::darkGray, 5, Qt::SolidLine, Qt::RoundCap));
    for(int y = 0; y < 3; y++)
    {
        for(int x = 0; x < 3; x++)
        {
            painter.drawPoint(RECTSIZE/2 + point[x]*RECTSIZE,
                              RECTSIZE/2 + point[y]*RECTSIZE);
        }
    }

    for(int y = 0; y < Connect6::BOARDSIZE; y++)
    {
        for(int x = 0; x < Connect6::BOARDSIZE; x++)
        {
            Connect6::Piece piece = Connect6::getInstance()->getBoard(y, x);

            if(piece == Connect6::BLACK)
            {
                const QImage& image = blackImg;
                QRect target(RECTSIZE/2 + x*RECTSIZE - image.width()/2,
                             RECTSIZE/2 + y*RECTSIZE - image.height()/2,
                             image.width(),
                             image.height());
                painter.drawImage(target, image);
            }
            else if(piece == Connect6::WHITE)
            {
                const QImage& image = whiteImg;
                QRect target(RECTSIZE/2 + x*RECTSIZE - image.width()/2,
                             RECTSIZE/2 + y*RECTSIZE - image.height()/2,
                             image.width(),
                             image.height());
                painter.drawImage(target, image);
            }
        }
    }
}