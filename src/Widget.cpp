#include "Widget.h"

#include "Controller.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent)
{
    renderArea = new RenderArea;

    statusLabel = new QLabel(tr("Ready"));

    startDuoButton = new QPushButton(tr("1 : 1"), this);
    soloBlackStartButton = new QPushButton(QIcon(":/resource/mushroom.png"),
                                           tr("1(B) : CPU"),
                                           this);
    soloWhiteStartButton = new QPushButton(QIcon(":/resource/slime.png"),
                                           tr("1(W) : CPU"),
                                           this);
    networkStartButton = new QPushButton(tr("1 : Network"), this);
    resetButton = new QPushButton(tr("Reset"), this);

    connect(Controller::getInstance(), &Controller::boardChanged,
            this, &Widget::onBoardChanged);

    connect(startDuoButton, &QPushButton::clicked,
            this, &Widget::onStartDuoButtonClicked);
    connect(soloBlackStartButton, &QPushButton::clicked,
            this, &Widget::onSoloBlackStartButtonClicked);
    connect(resetButton, &QPushButton::clicked,
            this, &Widget::onResetButtonClicked);

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
    switch(Controller::getInstance()->getStatus())
    {
    case Controller::READY:
        str = "Ready";
        break;
    case Controller::START:
        str = "Start";
        break;
    case Controller::BLACK1:
        str = "Black1";
        break;
    case Controller::BLACK2:
        str = "Black2";
        break;
    case Controller::WHITE1:
        str = "White1";
        break;
    case Controller::WHITE2:
        str = "White2";
        break;
    case Controller::BLACKWIN:
        str = "Black Win";
        break;
    case Controller::WHITEWIN:
        str = "White Win";
        break;
    default:
        break;
    }

    statusLabel->setText(str);
}

void Widget::onResetButtonClicked()
{
    startDuoButton->setEnabled(true);
    soloBlackStartButton->setEnabled(true);
    soloWhiteStartButton->setEnabled(true);
    networkStartButton->setEnabled(true);

    Controller::getInstance()->reset();
}

void Widget::onStartDuoButtonClicked()
{
    startDuoButton->setEnabled(false);
    soloBlackStartButton->setEnabled(false);
    soloWhiteStartButton->setEnabled(false);
    networkStartButton->setEnabled(false);

    Controller::getInstance()->startDuo();
}

void Widget::onSoloBlackStartButtonClicked()
{
    startDuoButton->setEnabled(false);
    soloBlackStartButton->setEnabled(false);
    soloWhiteStartButton->setEnabled(false);
    networkStartButton->setEnabled(false);

    Controller::getInstance()->startBot(Controller::BLACK);
}
