#include "RenderArea.h"

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{

}

QSize RenderArea::sizeHint() const
{
    return QSize(600, 600);
}

void RenderArea::paintEvent(QPaintEvent* event)
{

}
