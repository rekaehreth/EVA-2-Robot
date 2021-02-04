#include "robotwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RobotWidget w;
    w.show();
    return a.exec();
}
