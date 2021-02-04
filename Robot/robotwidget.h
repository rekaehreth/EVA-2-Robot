#ifndef ROBOTWIDGET_H
#define ROBOTWIDGET_H

#include "robotmodel.h"
#include <QMainWindow>
#include <QPushButton>
#include <QVector>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>

class RobotWidget : public QWidget
{
    Q_OBJECT
private:
    RobotModel* viewModel;

    QVector< QPushButton* > fields;
    QGridLayout* playingArea;
    QHBoxLayout* pauseLayout;
    QHBoxLayout* sizeLayout;
    QVBoxLayout* mainLayout;
    QLabel* timerLabel;
    QPushButton* pauseButton;
    QPushButton* smallGameButton;
    QPushButton* mediumGameButton;
    QPushButton* largeGameButton;

    void generateTable();
    void deleteTable();
public:
    RobotWidget(QWidget *parent = nullptr);
    ~RobotWidget();
public slots:
    void on_smallButton_clicked();
    void on_mediumButton_clicked();
    void on_largeButton_clicked();

    void on_pauseButton_clicked();

    void on_fieldButtonClicked();

    void on_refreshTable();
    void on_refresTimer();
};
#endif // ROBOTWIDGET_H
