#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>

#define SCALE_FACTOR 1.2

class MyGraphicsView : public QGraphicsView
{
       Q_OBJECT
public:
    MyGraphicsView(QWidget *parent);
    ~MyGraphicsView();
    void wheelEvent(QWheelEvent *event);
};

#endif // MYGRAPHICSVIEW_H
