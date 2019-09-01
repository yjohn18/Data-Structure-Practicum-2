#ifndef JOSEPHRING_H
#define JOSEPHRING_H

#include <QMainWindow>
typedef int Status;
typedef int ElemType;	//可根据需要修改元素的类型

class LinkList;	//提前声明，因为定义友元要用到

class LNode {
protected:
    ElemType data;	//数据域
    LNode   *next;	//指针域
public:
    friend class JosephRing;
    //不定义任何函数，相当于struct LNode
};


/* 带头结点的循环链表 */
/* 需要的操作：初始化、销毁  */
/* 为了便于删除，各种指针都指向目标之前的结点 */
class JosephRing {
protected:
    LNode *head;	//头指针
    LNode *cur;     //当前活动人物 之前的结点
public:
    JosephRing();
    ~JosephRing();
    int PreCount(const int n);  //将cur定位到第n个结点
    int	Counting();             //cur移向下一位，返回的指向的人的编号
    void DeleteNode();          //删除cur指向的结点，并将cur移向下一位
    QString toQStr();           //将循环链表转换成字符串
    int CurrentData();          //返回当前活动人物编号
    Status CreateRing(const int n);//生成长度为n的约瑟夫环
    bool isEmpty();
    bool isGameOver();          //返回游戏是否结束（即是否只剩下一个人）
    int toArr(int *arr);        //将循环链表转换成整型数组，返回元素个数
};

#endif // JOSEPHRING_H
