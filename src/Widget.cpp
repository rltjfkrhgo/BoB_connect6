#include "Widget.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent)
{
    statusLabel = new QLabel(tr("Ready"));

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(statusLabel);
    setLayout(mainLayout);
}

Widget::~Widget()
{
}
