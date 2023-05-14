#include "mainwindow.h"

#include <QApplication>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTimer timer;
    w.setFixedSize(550,450);
    w.show();
    static int cityNumber = 0;
    QObject::connect(&timer, &QTimer::timeout,[&]()
    {
        ++cityNumber;

        switch (cityNumber)
        {
        case 0:
            w.parse("https://www.gismeteo.ru/weather-moscow-4368/now/");
            break;
        case 1:
            w.parse("https://www.gismeteo.ru/weather-sankt-peterburg-4079/now/");
            break;
        case 2:
            w.parse("https://www.gismeteo.ru/weather-yekaterinburg-4517/now/");
        case 3:
            w.parse("https://www.gismeteo.ru/weather-novosibirsk-4690/now/");
        }

        if(cityNumber > 3)
            cityNumber = 0;
    });

    timer.start(7000);


    return a.exec();
}
