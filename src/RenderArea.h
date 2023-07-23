#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget* parent = nullptr);
    QSize sizeHint() const override;

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;

private:
    void drawPiece(const QImage& img, int y, int x);

    constexpr static int RECTSIZE = 24;

    const QImage blackImg;
    const QImage whiteImg;
};

#endif // RENDERAREA_H
