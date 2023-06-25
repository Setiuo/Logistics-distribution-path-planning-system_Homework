#include "mygraphicview.h"

MyGraphicView::MyGraphicView(QWidget *parent) : QGraphicsView(parent)
{

}

void MyGraphicView::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        QPoint point = event->pos();          //view坐标
        emit mouseClick(std::move(point));
    }
    QGraphicsView::mousePressEvent(event);
}

void MyGraphicView::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    emit mouseMovePoint(point);
    QGraphicsView::mouseMoveEvent(event);
}
