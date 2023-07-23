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
    void paintEvent(QPaintEvent* event) override;

private:
    const QImage blackImg;
    const QImage whiteImg;
};

#endif // RENDERAREA_H
