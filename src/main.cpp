#include "MainWindow.h"
#include "global.h"
#include <QApplication>
#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    controller cont;
#if ENABLE_GRAPHICS == ON
    MainWindow w;
    a.connect(&cont, &controller::setGraph, &w, &MainWindow::setGraph);
    a.connect(&cont, &controller::setObstacles, &w, &MainWindow::setObstacles);
    a.connect(&cont, &controller::setGoal, &w, &MainWindow::setGoal);
    a.connect(&cont, &controller::setStart, &w, &MainWindow::setStart);
    a.connect(&cont, &controller::setTolerances, &w, &MainWindow::setTolerances);
    a.connect(&cont, &controller::setArenaBounds, &w, &MainWindow::setArenaBounds);
    a.connect(&cont, &controller::setEpsilon, &w, &MainWindow::setEpsilon);
    a.connect(&w, &MainWindow::startSim, &cont, &controller::startSim);
    a.connect(&cont, &controller::setGoalPath, &w, &MainWindow::setGoalPath);

#endif
    cont.configure();
    cont.setup();

#if ENABLE_GRAPHICS == ON
    w.show();
#else
    cont.rrt();
#endif
    return a.exec();
}
