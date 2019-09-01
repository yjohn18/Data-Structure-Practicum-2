#pragma execution_character_set("utf-8")
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "josephring.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    int num;    //人数
    int start;  //起点
    int dice;   //骰子点数
    JosephRing ring;

    QString que;    //当前队列
    QString outque; //出列队列

    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
