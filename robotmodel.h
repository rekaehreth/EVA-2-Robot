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
private:
    int _size;   // 7 | 11 | 15
    int timeInSec;
    bool gameActive;
    bool robotsLocWasWall = false;
    Robot _robot;

    QVector<int> field;
    QTimer* timer;
public:
    explicit RobotModel(QObject *parent = nullptr);
    QString getPaneType(int x, int y);
    QString getElapsedTime();
    int getSize() {
        return _size;
    }
    bool isActive() {
        return gameActive;
    }
    void stepRobot(int changeX, int changeY);
    void moveRobot();
    bool placeWall( int index );

    void startNewGame( int size );
    void pauseOrResumeGame();
    bool isGameOver();

public slots:
    void on_timer_timeOut();

signals:
    void refreshTable();
    void refreshTime();
};

#endif // ROBOTMODEL_H
