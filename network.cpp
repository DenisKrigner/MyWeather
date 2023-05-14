#include "network.h"
#include <QDebug>

NetWork::NetWork(QObject *parent) : QObject(parent), manager(new QNetworkAccessManager)
{

    connect(manager, SIGNAL(finished(QNetworkReply*)), SLOT(getData(QNetworkReply*)));
    connect(this, SIGNAL(sendData(QVector<QString>*)), &mw, SLOT(setValues(QVector<QString>*)));

}

void NetWork::parse(QString url)
{
    manager->get(QNetworkRequest(url));
}



void NetWork::getData(QNetworkReply *reply)
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

                /*if(tempStr.indexOf("+") == -1){
                    index = tempStr.indexOf("-");
                }else{
                    index = tempStr.indexOf("+");
                }
                weatherData.append(tempStr[index] + " ");
                Вот я напридумывал конечно  XD
                */

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


    }else
        qDebug() << "reply error";

    emit sendData(&weatherDataList);
    reply->deleteLater();
}



NetWork::~NetWork()
{
    delete manager;
}
