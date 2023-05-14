#ifndef NETWORK_H
#define NETWORK_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QVector>
#include <QUrl>
#include <QDebug>

#include "mainwindow.h"

class NetWork : public QObject
{
    Q_OBJECT
public:
    NetWork(QObject *parent = nullptr);
    ~NetWork();

    void parse(QString);
private slots:
    void getData(QNetworkReply*);
signals:
    void sendData(QVector<QString>*);

private:
    QNetworkAccessManager* manager;
    MainWindow mw;
};

#endif // NETWORK_H
