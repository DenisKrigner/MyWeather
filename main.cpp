#include "mainwindow.h"
#include "network.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NetWork net;
    QTimer timer;
    static int cityNumber = 0;
    QObject::connect(&timer, &QTimer::timeout,[&]()
    {
        switch (cityNumber)
        {
        case 0:
            net.parse("https://www.gismeteo.ru/weather-moscow-4368/now/");
            break;
        case 1:
            net.parse("https://www.gismeteo.ru/weather-sankt-peterburg-4079/now/");
            break;
        case 2:
            net.parse("https://www.gismeteo.ru/weather-yekaterinburg-4517/now/");
        case 3:
            net.parse("https://www.gismeteo.ru/weather-novosibirsk-4690/now/");
        }
        ++cityNumber;
        if(cityNumber > 3)
            cityNumber = 0;
    });
    timer.start(3000);


    MainWindow w;
    w.setFixedSize(600,450);
    w.show();
    return a.exec();
}
