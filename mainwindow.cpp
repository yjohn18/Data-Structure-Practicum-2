#include <cstdlib>
#include <ctime>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPoint>
#include <QPainter>
#include <QTime>

const int MAXSIZE = 30;
const qreal PI  =3.141592653589793238463;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(int(time(0)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

//“确认键”
void MainWindow::on_pushButton_clicked()
{
    bool ok;
    num = ui->lineEdit->text().toInt(&ok);

    if (ui->lineEdit->text().isEmpty()) {
        ui->Prompt->setText("人数为空，请重新输入！");
        return;
    }
    else if (!ok) {
        ui->Prompt->setText("人数非法，请重新输入！");
        return;
    }
    else if (num < 2) {
        ui->Prompt->setText("人数小于2，请重新输入！");
        return;
    }
    else if (num > MAXSIZE) {
        ui->Prompt->setText("人数大于30，请重新输入！");
        return;
    }
    else {
        ui->Prompt->setText("人数设置成功，请选择游戏起点。");
    }

    //初始化combobox
    ui->comboBox->clear();
    for (int i = 0; i < num; ++i)
        ui->comboBox->addItem(QString::number(i + 1));

    //打开起点选择
    ui->comboBox->setEnabled(true);
    ui->pushButton_3->setEnabled(true);

    //初始化循环链表
    ring.CreateRing(num);

//    ui->QueueTxt->setPlainText(ring.toQStr());
    ui->DequeueTxt->clear();
    outque.clear();

    ui->pushButton->setText("重新设置");
    ui->pushButton_2->setEnabled(false);
    ui->lcdNumber->display(0);
    ui->Txt1->clear();
    ui->Txt2->clear();
    ui->Txt3->clear();
    ui->Txt4->clear();
    ui->Txt5->clear();
    ui->Txt6->clear();
    ui->TxtKilled->clear();

    this->update();
}

//扔骰子
void MainWindow::on_pushButton_2_clicked()
{
    QTime t;

    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(false);  //防止不必要的麻烦 在报数和出列的过程中禁止这两个按钮

    dice = rand() % 6 + 1;
    ui->lcdNumber->display(dice);
    ui->Txt1->clear();
    ui->Txt2->clear();
    ui->Txt3->clear();
    ui->Txt4->clear();
    ui->Txt5->clear();
    ui->Txt6->clear();
    ui->TxtKilled->clear();

    this->repaint();
    t.start();
    while(t.elapsed()<750);
//        QCoreApplication::processEvents();

    ui->Txt1->setPlainText(QString::number(ring.CurrentData()));    //第一次报数

    for (int i = 2; i <= dice; ++i) {
        t.start();
        while(t.elapsed()<750)
            QCoreApplication::processEvents();
        switch (i) {
            case 2:
                ui->Txt2->setPlainText(QString::number(ring.Counting()));
            break;
            case 3:
                ui->Txt3->setPlainText(QString::number(ring.Counting()));
            break;
            case 4:
                ui->Txt4->setPlainText(QString::number(ring.Counting()));
            break;
            case 5:
                ui->Txt5->setPlainText(QString::number(ring.Counting()));
            break;
            case 6:
                ui->Txt6->setPlainText(QString::number(ring.Counting()));
            break;
        }//switch
        this->repaint();//this->update会合并，所以使用repaint
    }//for

    ui->TxtKilled->setPlainText(QString::number(ring.CurrentData()));
    outque.append(QString::number(ring.CurrentData()) + " ");
    ring.DeleteNode();//出列
    ui->DequeueTxt->setPlainText(outque);

    //等待一段时间后 从界面中出列
    t.start();
    while(t.elapsed()<750);
//        QCoreApplication::processEvents();

    this->update();
    ui->pushButton_2->setEnabled(true);
    ui->pushButton->setEnabled(true);//恢复两个按钮
    if (ring.isGameOver()){
        ui->pushButton_2->setEnabled(false);
        ui->Prompt->setText("游戏结束！编号为" + QString::number(ring.CurrentData()) + "的人胜出！");
    }
}

//起点选择
void MainWindow::on_pushButton_3_clicked()
{
    start = ui->comboBox->currentIndex() + 1;
    ring.PreCount(start);
    //关闭起点选择，开启扔骰子键
    ui->comboBox->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(true);

    ui->Prompt->setText("请按“扔骰子”开始游戏");

    this->update();//将起点标红
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    int *arr = new int[MAXSIZE];
    int size = ring.toArr(arr);
    QPainter painter (this);
    QPointF p;
    const qreal r = 100.0;
    for (int i = 0; i < size; ++i) {
        p.setX(r * sin(2.0 * PI / size * qreal(i)) + 210.0);
        p.setY(-r * cos(2.0 * PI / size * qreal(i)) + 320.0);
        if (arr[i] == ring.CurrentData())
            painter.setPen(Qt::red);
        else
            painter.setPen(Qt::black);
        painter.drawText(p, QString::number(arr[i]));
    }

    delete [] arr;
}
