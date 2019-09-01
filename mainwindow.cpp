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

//��ȷ�ϼ���
void MainWindow::on_pushButton_clicked()
{
    bool ok;
    num = ui->lineEdit->text().toInt(&ok);

    if (ui->lineEdit->text().isEmpty()) {
        ui->Prompt->setText("����Ϊ�գ����������룡");
        return;
    }
    else if (!ok) {
        ui->Prompt->setText("�����Ƿ������������룡");
        return;
    }
    else if (num < 2) {
        ui->Prompt->setText("����С��2�����������룡");
        return;
    }
    else if (num > MAXSIZE) {
        ui->Prompt->setText("��������30�����������룡");
        return;
    }
    else {
        ui->Prompt->setText("�������óɹ�����ѡ����Ϸ��㡣");
    }

    //��ʼ��combobox
    ui->comboBox->clear();
    for (int i = 0; i < num; ++i)
        ui->comboBox->addItem(QString::number(i + 1));

    //�����ѡ��
    ui->comboBox->setEnabled(true);
    ui->pushButton_3->setEnabled(true);

    //��ʼ��ѭ������
    ring.CreateRing(num);

//    ui->QueueTxt->setPlainText(ring.toQStr());
    ui->DequeueTxt->clear();
    outque.clear();

    ui->pushButton->setText("��������");
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

//������
void MainWindow::on_pushButton_2_clicked()
{
    QTime t;

    ui->pushButton_2->setEnabled(false);
    ui->pushButton->setEnabled(false);  //��ֹ����Ҫ���鷳 �ڱ����ͳ��еĹ����н�ֹ��������ť

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

    ui->Txt1->setPlainText(QString::number(ring.CurrentData()));    //��һ�α���

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
        this->repaint();//this->update��ϲ�������ʹ��repaint
    }//for

    ui->TxtKilled->setPlainText(QString::number(ring.CurrentData()));
    outque.append(QString::number(ring.CurrentData()) + " ");
    ring.DeleteNode();//����
    ui->DequeueTxt->setPlainText(outque);

    //�ȴ�һ��ʱ��� �ӽ����г���
    t.start();
    while(t.elapsed()<750);
//        QCoreApplication::processEvents();

    this->update();
    ui->pushButton_2->setEnabled(true);
    ui->pushButton->setEnabled(true);//�ָ�������ť
    if (ring.isGameOver()){
        ui->pushButton_2->setEnabled(false);
        ui->Prompt->setText("��Ϸ���������Ϊ" + QString::number(ring.CurrentData()) + "����ʤ����");
    }
}

//���ѡ��
void MainWindow::on_pushButton_3_clicked()
{
    start = ui->comboBox->currentIndex() + 1;
    ring.PreCount(start);
    //�ر����ѡ�񣬿��������Ӽ�
    ui->comboBox->setEnabled(false);
    ui->pushButton_3->setEnabled(false);
    ui->pushButton_2->setEnabled(true);

    ui->Prompt->setText("�밴�������ӡ���ʼ��Ϸ");

    this->update();//�������
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
