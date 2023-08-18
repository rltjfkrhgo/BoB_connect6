#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "Connect6Type.h"
#include "RenderArea.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private slots:
    void onBoardChanged(Status status);
    void onResetButtonClicked();
    void onStartDuoButtonClicked();
    void onSoloBlackStartButtonClicked();
    void onSoloWhiteStartButtonClicked();
    void onNetworkStartButtonClicked();

private:
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
};

#endif // WIDGET_H
