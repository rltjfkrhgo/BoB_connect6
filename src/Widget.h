#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "Bot.h"
#include "Connect6Type.h"
#include "Net.h"
#include "RenderArea.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private slots:
    void onBoardChanged(const Piece color, const int y, const int x);
    void onStatusChanged(const Status status);
    void onResetButtonClicked();
    void onStartDuoButtonClicked();
    void onSoloBlackStartButtonClicked();
    void onSoloWhiteStartButtonClicked();
    void onNetworkStartButtonClicked();
    void onPostStartNet(const Piece myColor, const QString& othername);

private:
    void startBot(const Piece userColor);

    RenderArea* renderArea;

    QLabel* statusLabel;
    QPushButton* startDuoButton;
    QPushButton* soloBlackStartButton;
    QPushButton* soloWhiteStartButton;
    QPushButton* networkStartButton;
    QPushButton* resetButton;
    QLineEdit* nameEdit;
    QLineEdit* ipEdit;
    QLineEdit* portEdit;
    QTextEdit* textEdit;
    QString blackName;
    QString whiteName;

    Bot* bot;
    Net* net;
};

#endif // WIDGET_H
