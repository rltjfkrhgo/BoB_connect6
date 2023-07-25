#include "Widget.h"

#include "Connect6.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent)
{
    renderArea = new RenderArea;

    statusLabel = new QLabel(tr("Ready"));

    startDuoButton = new QPushButton(tr("1 : 1"), this);
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

    connect(startDuoButton, &QPushButton::clicked, this, &Widget::onStartDuo);
    connect(resetButton, &QPushButton::clicked, this, &Widget::onReset);

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea, 0, 0);
    mainLayout->addWidget(statusLabel);
    mainLayout->addWidget(startDuoButton);
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

    QString str;
    switch(Connect6::getInstance()->getStatus())
    {
    case Connect6::READY:
        str = "Ready";
        break;
    case Connect6::START:
        str = "Start";
        break;
    case Connect6::BLACK1:
        str = "Black1";
        break;
    case Connect6::BLACK2:
        str = "Black2";
        break;
    case Connect6::WHITE1:
        str = "White1";
        break;
    case Connect6::WHITE2:
        str = "White2";
        break;
    case Connect6::END:
        str = "End";
        break;
    default:
        break;
    }

    statusLabel->setText(str);
}

void Widget::onReset()
{
    startDuoButton->setEnabled(true);
    soloBlackStartButton->setEnabled(true);
    soloWhiteStartButton->setEnabled(true);
    networkStartButton->setEnabled(true);

    Connect6::getInstance()->reset();
}

void Widget::onStartDuo()
{
    startDuoButton->setEnabled(false);
    soloBlackStartButton->setEnabled(false);
    soloWhiteStartButton->setEnabled(false);
    networkStartButton->setEnabled(false);

    Connect6::getInstance()->startDuo();
}
