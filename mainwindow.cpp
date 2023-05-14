#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    movieLabel = new QLabel(this);
    movie = new QMovie("C:/project/MyWeather/cloudy.gif");

    if(!movie->isValid())
        qDebug() <<"Invalid gif\n";
    movieLabel->setMovie(movie);
    movieLabel->resize(this->size());
    movieLabel->setScaledContents(true);
    movie->start();

   // dateTimeLabel = new QLabel("0",this);
    //temptureLabel = new QLabel("0",this);
   // weatherTypeLabel = new QLabel("0",this);

    layout = new QVBoxLayout(movieLabel);
    //layout->addWidget(movieLabel,0,Qt::AlignCenter);
    //layout->addWidget(dateTimeLabel);
   // layout->addWidget(temptureLabel);
    //layout->addWidget(weatherTypeLabel);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);

    setCentralWidget(centralWidget);

    //toCheack();
}

MainWindow::~MainWindow()
{
    delete movie;
}



