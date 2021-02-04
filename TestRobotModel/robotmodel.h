#ifndef ROBOTMODEL_H
#define ROBOTMODEL_H

#include <QObject>
#include <QVector>
#include <QTimer>
#include <QRandomGenerator>

struct Robot {
    int heading = 0;
    int x = 0;
    int y = 0;
};
class RobotModel : public QObject
{
    Q_OBJECT

public:
    QVector<int> field;
    Robot _robot;

    int _size;   // 7 | 11 | 15
    int timeInSec;
    bool gameActive;
    bool robotsLocWasWall = false;

    QString getPaneType(int x, int y);
    QString getElapsedTime();
    void stepRobot(int changeX, int changeY);
    void moveRobot();
    bool placeWall( int index );

    void startNewGame( int size );
    bool isGameOver();

signals:
    void refreshTable();
    void refreshTime();
};

#endif // ROBOTMODEL_H
