#include "robotwidget.h"

void RobotWidget::generateTable()
{
    if(fields.size() != 0){
       deleteTable();
    }
    for ( int i = 0; i < viewModel->getSize(); ++i ) {
        for ( int j = 0; j < viewModel->getSize(); ++j ) {
            QPushButton* button = new QPushButton();
            button->setFixedSize(30, 30);
            fields.push_back( button );
            playingArea->addWidget( button, i, j );
            connect( button, SIGNAL(clicked()), this, SLOT( on_fieldButtonClicked() ) );
        }
    }
    mainLayout->addLayout( playingArea );
    setLayout( mainLayout );
}

void RobotWidget::deleteTable()
{
    foreach ( QPushButton* button, fields ) {
        playingArea->removeWidget( button );
        delete button;
    }
    fields.clear();
}

RobotWidget::RobotWidget(QWidget *parent)
    : QWidget(parent)
{
    viewModel = new RobotModel();
    playingArea = new QGridLayout();
    pauseLayout = new QHBoxLayout();
    sizeLayout = new QHBoxLayout();
    mainLayout = new QVBoxLayout();
    timerLabel = new QLabel();
    timerLabel->setText("Elapsed time: ");
    pauseButton = new QPushButton();
    pauseButton->setText( "Pause" );
    smallGameButton = new QPushButton();
    smallGameButton->setText( "7x7" );
    mediumGameButton = new QPushButton();
    mediumGameButton->setText( "11x11" );
    largeGameButton = new QPushButton();
    largeGameButton->setText( "15x15" );

    pauseLayout->addWidget( timerLabel );
    pauseLayout->addWidget( pauseButton );

    mainLayout->addLayout( pauseLayout );

    sizeLayout->addWidget( smallGameButton );
    sizeLayout->addWidget( mediumGameButton );
    sizeLayout->addWidget( largeGameButton );

    mainLayout->addLayout( sizeLayout );

    connect( smallGameButton, SIGNAL( clicked() ), this, SLOT( on_smallButton_clicked() ) );
    connect( mediumGameButton, SIGNAL( clicked() ), this, SLOT( on_mediumButton_clicked() ) );
    connect( largeGameButton, SIGNAL( clicked() ), this, SLOT( on_largeButton_clicked() ) );
    connect( pauseButton, SIGNAL( clicked() ), this, SLOT( on_pauseButton_clicked() ) );

    connect( viewModel, SIGNAL( refreshTable() ), this, SLOT( on_refreshTable() ) );
    connect( viewModel, SIGNAL( refreshTime() ), this, SLOT( on_refresTimer() ) );

    on_smallButton_clicked();
}

RobotWidget::~RobotWidget()
{
}

void RobotWidget::on_smallButton_clicked()
{
    viewModel->startNewGame(7);
    generateTable();
}

void RobotWidget::on_mediumButton_clicked()
{
    viewModel->startNewGame(11);
    generateTable();
}

void RobotWidget::on_largeButton_clicked()
{
    viewModel->startNewGame(15);
    generateTable();
}

void RobotWidget::on_pauseButton_clicked()
{
    viewModel->pauseOrResumeGame();
    if ( viewModel->isActive() ) {
        pauseButton->setText( "Pause" );
        foreach( QPushButton* button, fields )
        {
            button->setEnabled( true );
        }
    }
    else {
        pauseButton->setText( "Restart" );
        foreach( QPushButton* button, fields )
        {
            button->setEnabled( false );
        }
    }
}

void RobotWidget::on_fieldButtonClicked()
{
    QPushButton* senderButton = qobject_cast<QPushButton*>(sender());
    if ( !( viewModel->placeWall( playingArea->indexOf( senderButton ) ) ) ) {
        QMessageBox* errorBox = new QMessageBox();
        errorBox->setText("Can't place wall on selected field, there's already something on it.");
    }
}

void RobotWidget::on_refreshTable()
{
    for ( int i = 0; i < viewModel->getSize(); ++i ) {
        for ( int j = 0; j < viewModel->getSize(); ++j ) {
            if ( fields.size() != 0 )
                fields[ i * viewModel->getSize() + j ]->setText( viewModel->getPaneType( i, j ) );
        }
    }
    if ( viewModel->isGameOver() ) {
        QMessageBox* endGameBox = new QMessageBox();
        endGameBox->setText("Congratulation, you've won the game.\nYour time is: " + viewModel->getElapsedTime() );
    }
}

void RobotWidget::on_refresTimer()
{
    timerLabel->setText("Elapsed time: " + viewModel->getElapsedTime() );
}

