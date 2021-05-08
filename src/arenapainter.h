#ifndef ARENAPAINTER_H
#define ARENAPAINTER_H

#include <QObject>
#include <QWidget>
#include <QMap>
#include "global.h"
class arenaPainter : public QWidget
{
    Q_OBJECT
public:
    explicit arenaPainter(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *event);

    QMap<Point, QList<Point>> sourceGraph;
    QList<Obstacle> obstacles;
    QList<Point> goalPath;
    Point start;
    Point goal;
    double tolerance_x = 0;
    double tolerance_y = 0;
    double epsilon = 0.0;
    int width_cm = 0;
    int height_cm = 0;

    int convertXToPixels(int val){return val*(this->width()/double(width_cm));}
    int convertYToPixels(int val){return val*(this->height()/double(height_cm));}


signals:

};

#endif // ARENAPAINTER_H
