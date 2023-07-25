#include "Widget.h"

#include "Connect6.h"

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
    resetButton = new QPushButton(tr("Reset"), this);

    connect(Connect6::getInstance(), &Connect6::boardChanged,
            this, &Widget::onBoardChanged);

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea, 0, 0);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(duoStartButton);
    mainLayout->addWidget(soloBlackStartButton);
    mainLayout->addWidget(soloWhiteStartButton);
    mainLayout->addWidget(networkStartButton);
    mainLayout->addWidget(resetButton);
    setLayout(mainLayout);
}

Widget::~Widget()
{
}

void Widget::onBoardChanged()
{
    renderArea->update();
}
