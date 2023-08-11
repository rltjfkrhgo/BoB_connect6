#include "RenderArea.h"

#include <QPainter>
#include <QMouseEvent>
#include <QtDebug>

#include "Controller.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent), blackImg(":/resource/mushroom.png"), whiteImg(":/resource/slime.png")
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

    Controller::getInstance()->setPieceUser(y, x);
}

void RenderArea::paintEvent([[maybe_unused]] QPaintEvent* event)
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

    for(int y = 0; y < Controller::BOARDSIZE; y++)
    {
        for(int x = 0; x < Controller::BOARDSIZE; x++)
        {
            const Controller::Piece piece = Controller::getInstance()->getBoard(y, x);
            switch(piece)
            {
            case Controller::BLACK:
                drawPiece(blackImg, y, x);
                break;
            case Controller::WHITE:
                drawPiece(whiteImg, y, x);
                break;
            default:
                break;
            }
        }
    }
}

void RenderArea::drawPiece(const QImage& image, int y, int x)
{
    QPainter painter(this);
    QRect target(RECTSIZE/2 + x*RECTSIZE - image.width()/2,
                 RECTSIZE/2 + y*RECTSIZE - image.height()/2,
                 image.width(),
                 image.height());
    painter.drawImage(target, image);
}
