#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVBoxLayout>
#include <QMovie>
#include <QDebug>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void toCheack();

private:
    QLabel *movieLabel;
    QLabel *dateTimeLabel;
    QLabel *temptureLabel;
    QLabel *weatherTypeLabel;

    QVBoxLayout *layout;

    QMovie *movie;
};
#endif // MAINWINDOW_H
