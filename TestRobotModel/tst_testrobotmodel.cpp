#include <QtTest>

// add necessary includes here
#include "robotmodel.h"

class testRobotModel : public QObject
{
    Q_OBJECT
private:
    RobotModel* model;
public:
    testRobotModel();
    ~testRobotModel();

private slots:
    void initTestCase();
    void cleanupTestCase();

    void testGetPaneType();
    void testGetElapsedTime();

    void testMoveRobot_outOfPlayingArea();
    void testMoveRobot_toEmptyFields();
    void testMoveRobot_toWallFields();
    void testMoveRobot_toBrokenWallFields();

    void testPlaceWall_onEmptyField();
    void testPlaceWall_onRobot();
    void testPlaceWall_onWall();
    void testPlaceWall_onBrokenWall();

    void testStartNewGame_Small();
    void testStartNewGame_Medium();
    void testStartNewGame_Large();

    void testIsGameOver();

};

testRobotModel::testRobotModel()
{

}

testRobotModel::~testRobotModel()
{

}

void testRobotModel::initTestCase()
{
    model = new RobotModel();
}

void testRobotModel::cleanupTestCase()
{
    delete model;
}

void testRobotModel::testGetPaneType()
{
    model->startNewGame( 7 );
    QCOMPARE( model->getPaneType( model->_robot.x, model->_robot.y ), "R" );
    model->field[ model->_robot.x * model->_size + model->_robot.y ] = 0;
    QCOMPARE( model->getPaneType( model->_robot.x, model->_robot.y ), "" );
    model->field[ 4 * model->_size + 2 ] = 1;
    QCOMPARE( model->getPaneType( 4, 2 ), "W" );
    model->field[ 3 * model->_size ] = 2;
    QCOMPARE( model->getPaneType( 3, 0 ), "B" );
}

void testRobotModel::testGetElapsedTime()
{
    model->timeInSec = 72;
    QCOMPARE( model->getElapsedTime(), "1:12" );
    model->timeInSec = 16;
    QCOMPARE( model->getElapsedTime(), "0:16" );
}

void testRobotModel::testMoveRobot_outOfPlayingArea()
{
    model->startNewGame( 7 );
    model->field[model->_robot.x * model->_size + model->_robot.y] = 0;

    model->field[ 0 ] = 3;
    model->_robot.x = 0;
    model->_robot.y = 0;

    // fel
    model->_robot.heading  = 0;
    model->moveRobot();
    QCOMPARE( model->_robot.x, 0 );
    QCOMPARE( model->_robot.y, 0 );
    // balra
    model->_robot.heading  = 3;
    model->moveRobot();
    QCOMPARE( model->_robot.x, 0 );
    QCOMPARE( model->_robot.y, 0 );

    model->field[ 0 ] = 0;

    model->field[ model->field.size() - 1 ] = 3;
    model->_robot.x = model->_size - 1;
    model->_robot.y = model->_size - 1;

    // jobb
    model->_robot.heading  = 1;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size - 1 );
    QCOMPARE( model->_robot.y, model->_size - 1 );
    // le
    model->_robot.heading  = 2;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size - 1 );
    QCOMPARE( model->_robot.y, model->_size - 1 );

    model->field[ model->field.size() - 1 ] = 0;
}

void testRobotModel::testMoveRobot_toEmptyFields()
{
    model->startNewGame( 7 );
    model->field[model->_robot.x * model->_size + model->_robot.y] = 0;

    model->field[ model->_size * ( model->_size / 2 ) + model->_size / 2 ] = 3;
    model->_robot.x = model->_size / 2;
    model->_robot.y = model->_size / 2;

    model->_robot.heading  = 0;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 - 1 );
    QCOMPARE( model->_robot.y, model->_size / 2 );

    model->_robot.heading  = 1;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 - 1 );
    QCOMPARE( model->_robot.y, model->_size / 2 + 1 );

    model->_robot.heading  = 2;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 );
    QCOMPARE( model->_robot.y, model->_size / 2 + 1);

    model->_robot.heading  = 3;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 );
    QCOMPARE( model->_robot.y, model->_size / 2 );

    model->field[ model->_size * ( model->_size / 2 ) + model->_size / 2 ] = 0;
}

void testRobotModel::testMoveRobot_toWallFields()
{
    model->startNewGame( 7 );
    model->field[model->_robot.x * model->_size + model->_robot.y] = 0;

    model->field[ model->_size * ( model->_size / 2 ) + model->_size / 2 ] = 3;
    model->_robot.x = model->_size / 2;
    model->_robot.y = model->_size / 2;

    model->field[ model->_size * ( model->_size / 2 - 1 ) + ( model->_size / 2 ) ] = 1;
    model->field[ model->_size * ( model->_size / 2 ) + ( model->_size / 2 + 1 ) ] = 1;
    model->field[ model->_size * ( model->_size / 2 + 1 ) + ( model->_size / 2 ) ] = 1;
    model->field[ model->_size * ( model->_size / 2 ) + ( model->_size / 2 - 1 ) ] = 1;

    model->_robot.heading  = 0;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 );
    QCOMPARE( model->_robot.y, model->_size / 2 );
    QCOMPARE( model->field[ model->_size * ( model->_size / 2 - 1 ) + ( model->_size / 2 ) ], 2 );

    model->_robot.heading  = 1;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 );
    QCOMPARE( model->_robot.y, model->_size / 2 );
    QCOMPARE( model->field[ model->_size * ( model->_size / 2 ) + ( model->_size / 2 + 1 ) ], 2 );

    model->_robot.heading  = 2;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 );
    QCOMPARE( model->_robot.y, model->_size / 2 );
    QCOMPARE( model->field[ model->_size * ( model->_size / 2 + 1 ) + ( model->_size / 2 ) ], 2 );

    model->_robot.heading  = 3;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 );
    QCOMPARE( model->_robot.y, model->_size / 2 );
    QCOMPARE( model->field[ model->_size * ( model->_size / 2 ) + ( model->_size / 2 - 1 ) ], 2 );

    model->field[ model->_size * ( model->_size / 2 ) + model->_size / 2 ] = 0;

    model->field[ model->_size * ( model->_size / 2 - 1 ) + ( model->_size / 2 ) ] = 0;
    model->field[ model->_size * ( model->_size / 2 ) + ( model->_size / 2 + 1 ) ] = 0;
    model->field[ model->_size * ( model->_size / 2 + 1 ) + ( model->_size / 2 ) ] = 0;
    model->field[ model->_size * ( model->_size / 2 ) + ( model->_size / 2 - 1 ) ] = 0;
}

void testRobotModel::testMoveRobot_toBrokenWallFields()
{
    model->startNewGame( 7 );
    model->field[model->_robot.x * model->_size + model->_robot.y] = 0;

    model->field[ model->_size * ( model->_size / 2 ) + model->_size / 2 ] = 3;
    model->_robot.x = model->_size / 2;
    model->_robot.y = model->_size / 2;

    model->field[ model->_size * ( model->_size / 2 - 1 ) + ( model->_size / 2 ) ] = 2;
    model->field[ model->_size * ( model->_size / 2 - 1 ) + ( model->_size / 2 + 1 ) ] = 2;
    model->field[ model->_size * ( model->_size / 2 ) + ( model->_size / 2 + 1 ) ] = 2;
    model->field[ model->_size * ( model->_size / 2 + 1 ) + ( model->_size / 2 ) ] = 2;

    model->_robot.heading  = 0;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 - 1 );
    QCOMPARE( model->_robot.y, model->_size / 2 );

    model->_robot.heading  = 1;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 - 1 );
    QCOMPARE( model->_robot.y, model->_size / 2 + 1 );

    model->_robot.heading  = 2;
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 );
    QCOMPARE( model->_robot.y, model->_size / 2 + 1);

    model->_robot.heading  = 3;
    model->moveRobot();
    model->moveRobot();
    QCOMPARE( model->_robot.x, model->_size / 2 );
    QCOMPARE( model->_robot.y, model->_size / 2 - 1 );

    model->field[ model->_size * ( model->_size / 2 ) + model->_size / 2 ] = 0;

    model->field[ model->_size * ( model->_size / 2 - 1 ) + ( model->_size / 2 ) ] = 0;
    model->field[ model->_size * ( model->_size / 2 - 1 ) + ( model->_size / 2 + 1 ) ] = 0;
    model->field[ model->_size * ( model->_size / 2 ) + ( model->_size / 2 + 1 ) ] = 0;
    model->field[ model->_size * ( model->_size / 2 + 1 ) + ( model->_size / 2 ) ] = 0;
}

void testRobotModel::testPlaceWall_onEmptyField()
{
    model->startNewGame( 7 );
    model->field[ model->_robot.x * model->_size + model->_robot.y ] = 0;
    QCOMPARE( model->placeWall( model->_robot.x * model->_size + model->_robot.y ), true );
    QCOMPARE( model->field[ model->_robot.x * model->_size + model->_robot.y ], 1 );
}

void testRobotModel::testPlaceWall_onRobot()
{
    model->startNewGame( 7 );
    QCOMPARE( model->placeWall( model->_robot.x * model->_size + model->_robot.y ), false );
    QCOMPARE( model->field[ model->_robot.x * model->_size + model->_robot.y ], 3 );
}

void testRobotModel::testPlaceWall_onWall()
{
    model->startNewGame( 7 );
    model->field[ model->_robot.x * model->_size + model->_robot.y ] = 0;
    model->field[ 5 * model->_size ] = 1;
    QCOMPARE( model->placeWall( 5 * model->_size ), false );
    QCOMPARE( model->field[ 5 * model->_size ], 1 );
}

void testRobotModel::testPlaceWall_onBrokenWall()
{
    model->startNewGame( 7 );
    model->field[ model->_robot.x * model->_size + model->_robot.y ] = 0;

    model->field[ 4 * model->_size + 2 ] = 2;
    QCOMPARE( model->placeWall( 4 * model->_size + 2 ), false );
    QCOMPARE( model->field[ 4 * model->_size + 2 ], 2 );
}

void testRobotModel::testStartNewGame_Small()
{
    model->startNewGame( 7 );
    QCOMPARE( model->timeInSec, 0 );
    QCOMPARE( model->field.size(), model->_size * model->_size );
    QCOMPARE( model->field[ model->_robot.x * model->_size + model->_robot.y ], 3 );
    model->field[ model->_robot.x * model->_size + model->_robot.y ] = 0;
    for (int i = 0; i < model->field.size(); ++i ) {
        QCOMPARE( model->field[ i ], 0 );
    }
}

void testRobotModel::testStartNewGame_Medium()
{
    model->startNewGame( 11 );
    QCOMPARE( model->timeInSec, 0 );
    QCOMPARE( model->field.size(), model->_size * model->_size );
    QCOMPARE( model->field[ model->_robot.x * model->_size + model->_robot.y ], 3 );
    model->field[ model->_robot.x * model->_size + model->_robot.y ] = 0;
    for (int i = 0; i < model->field.size(); ++i ) {
        QCOMPARE( model->field[ i ], 0 );
    }
}

void testRobotModel::testStartNewGame_Large()
{
    model->startNewGame( 15 );
    QCOMPARE( model->timeInSec, 0 );
    QCOMPARE( model->field.size(), model->_size * model->_size );
    QCOMPARE( model->field[ model->_robot.x * model->_size + model->_robot.y ], 3 );
    model->field[ model->_robot.x * model->_size + model->_robot.y ] = 0;
    for (int i = 0; i < model->field.size(); ++i ) {
        QCOMPARE( model->field[ i ], 0 );
    }
}

void testRobotModel::testIsGameOver()
{
    model->startNewGame( 7 );
    model->field[ model->_robot.x * model->_size + model->_robot.y ] = 0;
    QCOMPARE( model->isGameOver(), false );
    model->field[ model->_size * ( model->_size / 2 ) + model->_size / 2 ] = 3;
    model->_robot.x = model->_size / 2;
    model->_robot.y = model->_size / 2;
    QCOMPARE( model->isGameOver(), true );
}

QTEST_APPLESS_MAIN(testRobotModel)

#include "tst_testrobotmodel.moc"
