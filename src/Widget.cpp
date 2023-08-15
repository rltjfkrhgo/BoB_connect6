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
    connect(soloWhiteStartButton, &QPushButton::clicked,
            this, &Widget::onSoloWhiteStartButtonClicked);
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

void Widget::onBoardChanged(Status status)
{
    renderArea->update();

    QString str;
    switch(status)
    {
    case READY:
        str = "Ready";
        break;
    case START:
        str = "Start";
        break;
    case BLACK1:
        str = "Black1";
        break;
    case BLACK2:
        str = "Black2";
        break;
    case WHITE1:
        str = "White1";
        break;
    case WHITE2:
        str = "White2";
        break;
    case BLACKWIN:
        str = "Black Win";
        break;
    case WHITEWIN:
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

    Controller::getInstance()->startBot(BLACK);
}

void Widget::onSoloWhiteStartButtonClicked()
{
    startDuoButton->setEnabled(false);
    soloBlackStartButton->setEnabled(false);
    soloWhiteStartButton->setEnabled(false);
    networkStartButton->setEnabled(false);

    Controller::getInstance()->startBot(WHITE);
}
