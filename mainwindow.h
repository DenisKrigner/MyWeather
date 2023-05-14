#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QVector>
#include <QUrl>
#include <QDebug>
#include <QMovie>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void parse(QString);
private slots:
    void getData(QNetworkReply*);


private:
    Ui::MainWindow *ui;
    QNetworkAccessManager* manager;
    QMovie *movie;

    void showWeather(QVector<QString>*);
};
#endif // MAINWINDOW_H
