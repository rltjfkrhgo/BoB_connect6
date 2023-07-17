#include "Widget.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent)
{
    renderArea = new RenderArea;

    statusLabel = new QLabel(tr("Ready"));

    duoStartButton = new QPushButton(tr("1 : 1"), this);
    soloBlackStartButton = new QPushButton(QIcon(":/img/mushroom.png"),
                                           tr("1(B) : CPU"),
                                           this);
    soloWhiteStartButton = new QPushButton(QIcon(":/img/slime.png"),
                                           tr("1(W) : CPU"),
                                           this);
    networkStartButton = new QPushButton(tr("1 : Network"), this);

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea, 0, 0);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(duoStartButton);
    mainLayout->addWidget(soloBlackStartButton);
    mainLayout->addWidget(soloWhiteStartButton);
    mainLayout->addWidget(networkStartButton);
    setLayout(mainLayout);
}

Widget::~Widget()
{
}
