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
    int num;    //����
    int start;  //���
    int dice;   //���ӵ���
    JosephRing ring;

    QString que;    //��ǰ����
    QString outque; //���ж���

    void paintEvent(QPaintEvent *event);
};

#endif // MAINWINDOW_H
