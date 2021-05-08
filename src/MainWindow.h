#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include "arenapainter.h"
#include "global.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void setGraph(QMap<Point, QList<Point>> graph){painter.sourceGraph = graph; painter.update();}
    void setObstacles(QList<Obstacle> list){painter.obstacles = list; painter.update();}
    void setGoal(Point goalPoint){painter.goal = goalPoint; painter.update();}
    void setStart(Point startPoint){painter.start = startPoint; painter.update();}
    void setTolerances(double tolX, double tolY){painter.tolerance_x=tolX; painter.tolerance_y=tolY; painter.update();}
    void setArenaBounds(int width, int height){painter.width_cm=width; painter.height_cm=height; painter.update();}
    void setEpsilon(double eps){painter.epsilon =eps; painter.update();};
    void setGoalPath(QList<Point> path){painter.goalPath = path; update();}

signals:
    void startSim();

private:
    arenaPainter painter;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
