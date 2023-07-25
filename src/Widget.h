#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>

#include "RenderArea.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private slots:
    void onBoardChanged();
    void onReset();
    void onStartDuo();

private:
    RenderArea* renderArea;

    QLabel* statusLabel;
    QPushButton* startDuoButton;
    QPushButton* soloBlackStartButton;
    QPushButton* soloWhiteStartButton;
    QPushButton* networkStartButton;
    QPushButton* resetButton;
};

#endif // WIDGET_H
