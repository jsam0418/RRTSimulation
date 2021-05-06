#include "MainWindow.h"

#include <QApplication>
#include "controller.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    controller cont;
    cont.configure();
    cont.setup();
    cont.rrt();
    //MainWindow w;
    //w.show();
    return a.exec();
}
