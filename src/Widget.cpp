#include "Widget.h"

#include "Controller.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent), bot(nullptr), net(nullptr)
{
    renderArea = new RenderArea;

    statusLabel = new QLabel;

    startDuoButton = new QPushButton(tr("1 : 1"), this);
    soloBlackStartButton = new QPushButton(QIcon(":/resource/mushroom.png"),
                                           tr("1(B) : CPU"),
                                           this);
    soloWhiteStartButton = new QPushButton(QIcon(":/resource/slime.png"),
                                           tr("1(W) : CPU"),
                                           this);
    networkStartButton = new QPushButton(tr("CPU : Network"), this);
    resetButton = new QPushButton(tr("Reset"), this);

    nameEdit = new QLineEdit(this);
    nameEdit->setPlaceholderText(tr("Name"));
    ipEdit = new QLineEdit(this);
    ipEdit->setPlaceholderText(tr("IP"));
    portEdit = new QLineEdit(this);
    portEdit->setPlaceholderText(tr("Port"));
    portEdit->setValidator(new QIntValidator(1, 65535, this));

    // 편의를 위해
    nameEdit->setText("kim1");
    ipEdit->setText(tr("192.168.56.101"));
    portEdit->setText(tr("8089"));

    textEdit = new QTextEdit(this);
    textEdit->setReadOnly(true);

    connect(Controller::getInstance(), &Controller::boardChanged,
            this, &Widget::onBoardChanged);
    connect(Controller::getInstance(), &Controller::statusChanged,
            this, &Widget::onStatusChanged);

    connect(startDuoButton, &QPushButton::clicked,
            this, &Widget::onStartDuoButtonClicked);
    connect(soloBlackStartButton, &QPushButton::clicked,
            this, &Widget::onSoloBlackStartButtonClicked);
    connect(soloWhiteStartButton, &QPushButton::clicked,
            this, &Widget::onSoloWhiteStartButtonClicked);
    connect(networkStartButton, &QPushButton::clicked,
            this, &Widget::onNetworkStartButtonClicked);
    connect(resetButton, &QPushButton::clicked,
            this, &Widget::onResetButtonClicked);

    QGridLayout* mainLayout = new QGridLayout;
    mainLayout->addWidget(renderArea, 0, 0, 9, 1);
    mainLayout->addWidget(statusLabel, 9, 0);
    mainLayout->addWidget(startDuoButton, 0, 1);
    mainLayout->addWidget(soloBlackStartButton, 1, 1);
    mainLayout->addWidget(soloWhiteStartButton, 2, 1);
    mainLayout->addWidget(nameEdit, 3, 1);
    mainLayout->addWidget(ipEdit, 4, 1);
    mainLayout->addWidget(portEdit, 5, 1);
    mainLayout->addWidget(networkStartButton, 6, 1);
    mainLayout->addWidget(resetButton, 7, 1);
    mainLayout->addWidget(textEdit, 8, 1);
    setLayout(mainLayout);
}

Widget::~Widget()
{
}

void Widget::onBoardChanged(const Piece color, const int y, const int x)
{
}

void Widget::onStatusChanged(Status status)
{
    renderArea->update();

    switch(status)
    {
    case START:
        statusLabel->setText("[ "+blackName+" ] 님이 하실 차례입니다.");
        textEdit->append(tr("게임이 시작되었습니다."));
        break;
    case BLACK1:
        statusLabel->setText("[ "+blackName+" ] 님이 하실 차례입니다.");
        break;
    case WHITE1:
        statusLabel->setText("[ "+ whiteName+" ] 님이 하실 차례입니다.");
        break;
    case BLACKWIN:
        textEdit->append("["+blackName+"]님이 승리하였습니다.");
        break;
    case WHITEWIN:
        textEdit->append("["+whiteName+"]님이 승리하였습니다.");
        break;
    default:
        break;
    }
}

void Widget::onResetButtonClicked()
{
    if(bot)
    {
        delete bot;
        bot = nullptr;
    }

    if(net)
    {
        delete net;
        net = nullptr;
    }

    startDuoButton->setEnabled(true);
    soloBlackStartButton->setEnabled(true);
    soloWhiteStartButton->setEnabled(true);
    networkStartButton->setEnabled(true);
    statusLabel->clear();
    textEdit->clear();

    connect(renderArea, &RenderArea::setPieceUser,
            Controller::getInstance(), &Controller::setPieceNull);

    Controller::getInstance()->reset();
}

void Widget::onStartDuoButtonClicked()
{
    startDuoButton->setEnabled(false);
    soloBlackStartButton->setEnabled(false);
    soloWhiteStartButton->setEnabled(false);
    networkStartButton->setEnabled(false);
    blackName = "mushroom";
    whiteName = "slime";

    connect(renderArea, &RenderArea::setPieceUser,
            Controller::getInstance(), &Controller::setPieceDuo);

    Controller::getInstance()->start();
}

void Widget::onSoloBlackStartButtonClicked()
{
    startBot(BLACK);
}

void Widget::onSoloWhiteStartButtonClicked()
{
    startBot(WHITE);
}

void Widget::startBot(const Piece userColor)
{
    startDuoButton->setEnabled(false);
    soloBlackStartButton->setEnabled(false);
    soloWhiteStartButton->setEnabled(false);
    networkStartButton->setEnabled(false);
    blackName = "mushroom";
    whiteName = "slime";

    bot = new Bot(!userColor);
    connect(Controller::getInstance(), &Controller::boardChanged,
            bot, &Bot::onBoardChanged);
    connect(Controller::getInstance(), &Controller::statusChanged,
            bot, &Bot::onStatusChanged);

    switch(userColor)
    {
    case BLACK:
        connect(renderArea, &RenderArea::setPieceUser,
                Controller::getInstance(), &Controller::setPieceBlack);
        connect(bot, &Bot::setPieceBot,
                Controller::getInstance(), &Controller::setPieceWhite);
        break;
    case WHITE:
        connect(renderArea, &RenderArea::setPieceUser,
                Controller::getInstance(), &Controller::setPieceWhite);
        connect(bot, &Bot::setPieceBot,
                Controller::getInstance(), &Controller::setPieceBlack);
        break;
    default:
        break;
    }

    Controller::getInstance()->start();
}

void Widget::onNetworkStartButtonClicked()
{
    startDuoButton->setEnabled(false);
    soloBlackStartButton->setEnabled(false);
    soloWhiteStartButton->setEnabled(false);
    networkStartButton->setEnabled(false);

    net = new Net(this);
    connect(net, &Net::postGameStart, this, &Widget::onPostStartNet);
    net->sendGameStart(nameEdit->text(), ipEdit->text(), portEdit->text());
    textEdit->append(tr("게임이 시작되기를 기다리는 중..."));
}

void Widget::onPostStartNet(const Piece myColor, const QString& othername)
{
    textEdit->append("["+othername+"]님이 입장하셨습니다.");

    connect(Controller::getInstance(), &Controller::boardChanged, net, &Net::onBoardChanged);

    bot = new Bot(myColor);
    connect(Controller::getInstance(), &Controller::boardChanged,
            bot, &Bot::onBoardChanged);
    connect(Controller::getInstance(), &Controller::statusChanged,
            bot, &Bot::onStatusChanged);

    switch(myColor)
    {
    case BLACK:
        blackName = nameEdit->text();
        whiteName = othername;
        connect(bot, &Bot::setPieceBot,
                Controller::getInstance(), &Controller::setPieceBlack);
        connect(net, &Net::setPieceNet,
                Controller::getInstance(), &Controller::setPieceWhite);
        break;
    case WHITE:
        blackName = othername;
        whiteName = nameEdit->text();
        connect(bot, &Bot::setPieceBot,
                Controller::getInstance(), &Controller::setPieceWhite);
        connect(net, &Net::setPieceNet,
                Controller::getInstance(), &Controller::setPieceBlack);
        break;
    default:
        break;
    }

    Controller::getInstance()->start();
}
