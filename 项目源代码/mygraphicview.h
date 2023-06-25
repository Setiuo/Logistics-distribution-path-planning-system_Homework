#ifndef MYGRAPHICVIEW_H
#define MYGRAPHICVIEW_H

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QGraphicsView>
#include <QMouseEvent>

class MyGraphicView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit MyGraphicView(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

signals:
    void mouseMovePoint(QPoint point);
    void mouseClick(QPoint point);

};

#endif // MYGRAPHICVIEW_H
