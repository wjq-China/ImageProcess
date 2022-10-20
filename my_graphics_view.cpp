#include "my_graphics_view.h"

MyGraphicsView::MyGraphicsView(QWidget *parent)
    : QGraphicsView(parent)
{
    setDragMode(QGraphicsView::ScrollHandDrag);
}

MyGraphicsView::~MyGraphicsView()
{

}

void MyGraphicsView::wheelEvent(QWheelEvent *event)
{
    qint16 lAngle =qint16(event->angleDelta().y()/120);
    if (lAngle > 0)
    {
        this->scale(SCALE_FACTOR, SCALE_FACTOR);
    }
    else
    {
        this->scale(1.0 / SCALE_FACTOR, 1.0 / SCALE_FACTOR);
    }

}
