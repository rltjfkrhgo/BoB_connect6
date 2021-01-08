#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QPainter>
#include <QMouseEvent>

#include "Connect6.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;

// 내가 추가 한 것들
private:
    const int RECTSIZE = 40;              // 바둑판 한 칸 사이즈
    const int BOARD_X = 40;  // 바둑판 시작 X 좌표
    const int BOARD_Y = 40;  // 바둑판 시작 Y 좌표
    const int BOARD_OFFSET = 30;  // 바둑판 여백
    const int BOARDSIZE = RECTSIZE * 18 + BOARD_OFFSET * 2;  // 바둑판 총 사이즈
    //const int CLICK_OFFSET = 10;  // 좌표 클릭할 때 인지할 오프셋

    const int TURN_X = 950;
    const int TURN_Y = 270;

    Connect6 connect6;  // 바둑판

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
private slots:
    void on_btnReset_clicked();
    void on_btnDuo_clicked();
};
#endif // WIDGET_H
