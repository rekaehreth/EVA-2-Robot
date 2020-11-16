#include "robotmodel.h"

RobotModel::RobotModel(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    connect( timer, SIGNAL(timeout()), this, SLOT(on_timer_timeOut() ) );
}

QString RobotModel::getPaneType(int x, int y)
{
    switch ( field[ _size * x + y ] ) {
    case 0:
        return "";  // empty
    case 1:
        return "W"; // wall
    case 2:
        return "B"; // broken wall
    default:
        return "R"; // robot
    }
}

QString RobotModel::getElapsedTime()
{
    int minutes = timeInSec / 60;
    int seconds = timeInSec % 60;
    return QString::number( minutes ) + ":" + QString::number( seconds );
}

void RobotModel::stepRobot(int changeX, int changeY)
{
    int x = _robot.x + changeX;
    int y = _robot.y + changeY;
    if ( field[ x * _size + y ] == 0 || field[ x * _size + y ] == 2 ) {
        if( robotsLocWasWall ) {
            field[ _robot.x * _size + _robot.y ] = 2;
            robotsLocWasWall = false;
        }
        else {
            field[ _robot.x * _size + _robot.y ] = 0;
        }
        _robot.x = x;
        _robot.y = y;
        if( field[ x * _size + y ] == 2 ) {
            robotsLocWasWall = true;
        }
        field[ x * _size + y ] = 3;
    } else if ( field[ x * _size + y ] == 1 ) {
        field[ x * _size + y ] = 2;
        _robot.heading = QRandomGenerator::global()->generate() % 4;
    }
}

void RobotModel::moveRobot()
{
    switch( _robot.heading ) {
    case 0:
        // fel
        if ( _robot.x != 0 ) {
            stepRobot( -1, 0 );
        }
        else {
            _robot.heading = QRandomGenerator::global()->generate() % 4;
        }
        break;
    case 1:
        // jobbra
        if ( _robot.y != _size -1 ) {
            stepRobot( 0, 1 );
        }
        else {
            _robot.heading = QRandomGenerator::global()->generate() % 4;
        }
        break;
    case 2:
        // le
        if ( _robot.x != _size - 1 ) {
            stepRobot( 1, 0 );
        }
        else {
            _robot.heading = QRandomGenerator::global()->generate() % 4;
        }
        break;
    default:
        // balra
        if ( _robot.y != 0 ) {
            stepRobot( 0, -1 );
        }
        else {
            _robot.heading = QRandomGenerator::global()->generate() % 4;
        }
        break;
    }
    refreshTable();
}

bool RobotModel::placeWall(int index)
{
    if ( field[ index ] == 0 ) {
        field[ index ] = 1;
        return true;
    }
    else return false;
}

void RobotModel::startNewGame(int size)
{
    field.clear();
    _size = size;
    for (int i = 0; i < _size; ++i ) {
        for (int j = 0; j < _size; ++j ) {
            field.push_back(0);
        }
    }
    do {
        _robot.x = QRandomGenerator::global()->generate() % _size;
        _robot.y = QRandomGenerator::global()->generate() % _size;
        _robot.heading = QRandomGenerator::global()->generate() % 4;
        field[ _robot.x * _size + _robot.y ] = 3;
    } while( isGameOver() );
    gameActive = true;
    timeInSec = 0;
    timer->start( 1000 );
}

void RobotModel::pauseOrResumeGame()
{
    gameActive = !gameActive;
    if ( gameActive ) timer->stop();
    else timer->start( 1000 );
}

bool RobotModel::isGameOver()
{
    if ( field[ _size * ( _size / 2 ) + _size / 2 ] == 3 ) return true;
    else return false;
}

void RobotModel::on_timer_timeOut()
{
    ++timeInSec;
    moveRobot();
    refreshTime();
    timer->start( 1000 );
}
