#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager(new QNetworkAccessManager)
{
    //setWindowFlags(windowFlags() | Qt::FramelessWindowHint);

    ui->setupUi(this);

    movie = new QMovie("C:/project/MyWeather2/cloudy.gif");
    if(!movie->isValid())
            qDebug() << "invalid gif";

    ui->movieLabel->setMovie(movie);
    ui->movieLabel->setScaledContents(true);
    ui->movieLabel->resize(this->size());
    movie->start();



    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(getData(QNetworkReply*)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete manager;
    delete movie;
}

void MainWindow::parse(QString url)
{
    manager->get(QNetworkRequest(url));
}

void MainWindow::getData(QNetworkReply *reply)
{
    QVector<QString> weatherDataList;
    weatherDataList.clear();

    if(reply->error() == QNetworkReply::NoError)
    {
        QString htmlContent = QString(reply->readAll());
        QStringList list = htmlContent.split("\n");
        QString weatherData;
        QString tempStr;
        QString line;

        unsigned int startIndex = 0;
        unsigned int lastIndex = 0;

        int size = list.length();

        for(int i = 0; i < size; i++) // There we push current date in our Data Vector
        {
            line = list[i];
            if(line.contains("class=\"now-localdate\""))
            {
                 startIndex = line.indexOf("D, j F, G:i\">");
                 lastIndex = line.indexOf("</div><div class=\"now");

                weatherData = line.mid(startIndex + 13, lastIndex - startIndex - 13);
                qDebug() <<"current date/time - " << weatherData << '\n';
                weatherDataList.push_back(weatherData);
                break;
            }
        }

        weatherData = "";

        for(int i = 0; i < size; i++)
        {
            line = list[i];
            if(line.contains("now-weather"))
            {
                startIndex = line.indexOf("now-weather");

                tempStr = line.mid(startIndex,100);

                if(tempStr.indexOf("+") == -1)
                    weatherData.append("-");
                else
                    weatherData.append("+");

                for(auto &x : tempStr)
                {
                    if(x.isDigit())
                        weatherData.append(x);
                }

                qDebug() << "current weather - " << weatherData << '\n';
                weatherDataList.push_back(weatherData);
                break;
            }

        }
        for(int i = 0; i < size; i++)
        {
            line = list[i];

            if(line.contains("<div class=\"now-desc\">"))
            {
                startIndex = line.indexOf("<div class=\"now-desc\">");
                lastIndex = line.indexOf("</div><div class=\"now-info\">");

                weatherData = line.mid(startIndex + 22, lastIndex - startIndex - 22);
                qDebug() << "weather type - " << weatherData;
                weatherDataList.push_back(weatherData);
            }
        }


    }else{
        qDebug() << "reply error";
        return;
    }

    reply->deleteLater();
    showWeather(&weatherDataList);
}


void MainWindow::showWeather(QVector<QString> *weatherDataList)
{
    static int cityNumber = 0;

    QString dateTime = weatherDataList->at(0);
    QString tempture = weatherDataList->at(1);
    QString weatherType = weatherDataList->at(2);

    QString cityName;

    qDebug() << "Show weather working\n" << dateTime << '\n'
             << tempture << '\n' << weatherType;

    switch (cityNumber)
    {
    case 0:
        cityName = "Москва";
        break;
    case 1:
        cityName = "Санкт Питербург";
        break;
    case 2:
        cityName = "Екатиренбург";
        break;
    case 3:
        cityName = "Новосибирск";
        break;
    default:
        qDebug() << "City name error";
        break;
    }


    ui->dateTimeLabel->setText(dateTime);
    ui->dateTimeLabel->setStyleSheet("color: #101414");
    ui->temptureLabel->setText(tempture);
    ui->temptureLabel->setStyleSheet("color: #101414");
    ui->weatherTypeLabel->setText(weatherType);
    ui->weatherTypeLabel->setStyleSheet("color: #101414");
    ui->cityLabel->setText(cityName);
    ui->cityLabel->setStyleSheet("color: #101414");

    cityNumber++;
    if(cityNumber > 3)
        cityNumber = 0;
}

