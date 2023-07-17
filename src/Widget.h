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

private:
    RenderArea* renderArea;

    QLabel* statusLabel;
    QPushButton* duoStartButton;
    QPushButton* soloBlackStartButton;
    QPushButton* soloWhiteStartButton;
    QPushButton* networkStartButton;
};

#endif // WIDGET_H
