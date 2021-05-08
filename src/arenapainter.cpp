#include <QStyleOption>
#include <QPainter>
#include <math.h>
#include "arenapainter.h"

arenaPainter::arenaPainter(QWidget *parent) : QWidget(parent)
{

}

void arenaPainter::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    if(this->width() < this->height())
        this->resize(this->width(), this->width());
    else
        this->resize(this->height(), this->height());
    opt.init(this);
    QPainter p(this);

    QPainter painter(this);
    painter.setBrush(Qt::SolidPattern);
    QPen pen;
    pen.setColor(Qt::black);
    pen.setWidth(2);
    painter.setPen(pen);

    QLine line;
    line.setP1({1, 1});
    line.setP2({this->width()-1, 1});
    painter.drawLine(line);
    line.setP2({1, this->height()-1});
    painter.drawLine(line);
    line.setP1({this->width()-1, this->height()-1});
    painter.drawLine(line);
    line.setP2({this->width()-1, 1});
    painter.drawLine(line);
    QRect obstacle;

    for(Obstacle obs : obstacles){
        obstacle.setX(convertXToPixels(obs.center.x-obs.width/2.0));
        obstacle.setY(convertYToPixels(obs.center.y-obs.height/2.0));
        obstacle.setWidth(convertXToPixels(obs.width));
        obstacle.setHeight(convertYToPixels(obs.height));
        painter.drawRect(obstacle);
    }


    painter.setBrush(Qt::SolidPattern);
    pen.setColor(Qt::darkGreen);
    painter.setPen(pen);
    QRect goalArea;
    goalArea.setX(convertXToPixels(goal.x-tolerance_x/2));
    goalArea.setY(convertYToPixels(goal.y-tolerance_y/2));
    goalArea.setWidth(convertXToPixels(tolerance_x));
    goalArea.setHeight(convertYToPixels(tolerance_y));
    painter.fillRect(goalArea, QBrush(Qt::darkGreen, Qt::SolidPattern));
    pen.setWidth(10);
    QPoint startPoint(convertXToPixels(start.x), convertYToPixels(start.y));
    pen.setColor(Qt::red);
    painter.setPen(pen);
    painter.drawPoint(startPoint);

    pen.setColor(Qt::blue);
    painter.setPen(pen);
    QPoint point;
    QLine edge;
    for(Point vertex : sourceGraph.keys()){
        pen.setWidth(5);
        pen.setColor(Qt::blue);
        painter.setPen(pen);
        point.setX(convertXToPixels(vertex.x));
        point.setY(convertYToPixels(vertex.y));
        painter.drawPoint(point);
        for(Point edges : sourceGraph[vertex]){
            pen.setWidth(1);
            pen.setColor(Qt::black);
            painter.setPen(pen);
            edge.setP1({convertXToPixels(vertex.x),convertYToPixels(vertex.y)});
            edge.setP2({convertXToPixels(edges.x),convertYToPixels(edges.y)});
            painter.drawLine(edge);
         }
    }

    //draw goal path
    Point prevPoint = goal;
    for(Point pathPoint : goalPath){
        pen.setWidth(5);
        pen.setColor(Qt::red);
        painter.setPen(pen);
        point.setX(convertXToPixels(pathPoint.x));
        point.setY(convertYToPixels(pathPoint.y));
        painter.drawPoint(point);
        if(prevPoint == goal){
            continue;
        }
        pen.setWidth(1);
        pen.setColor(Qt::red);
        painter.setPen(pen);
        edge.setP1({convertXToPixels(prevPoint.x),convertYToPixels(prevPoint.y)});
        edge.setP2({convertXToPixels(pathPoint.x),convertYToPixels(pathPoint.y)});
        painter.drawLine(edge);
    }
    goalPath.clear();
}
