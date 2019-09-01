#include <QString>
#include "josephring.h"

using namespace std;

JosephRing::JosephRing()
{
    head = new(nothrow) LNode;
    if (head == nullptr)
        exit(-1);

    head->next = head;
    cur = nullptr;
}

JosephRing::~JosephRing()
{
    LNode *q, *p = head;

    do {
        q = p->next;
        delete p;
        p = q;
    } while (p != head);

    head = nullptr;
}

Status JosephRing::CreateRing(const int n)
{
    LNode *q, *p = head->next;

    //先删除原先的结点
    while (p != head) {
        q = p->next;
        delete p;
        p = q;
    }

    cur = nullptr;
    head->next = head;

    int i;
    p = head;
    for (i = 0; i < n; i++) {
        p->next = new(nothrow)LNode;
        if (!p)
            return -1;
        p->next->data = i + 1;
        p = p->next;
    }
    p->next = head;
    return 0;
}

//将cur定位到第n个结点之前
int JosephRing::PreCount(const int n)
{
    cur = head;
    for (int i = 1; i < n; i++) {
        if (cur->next == head)
            i--;
        cur = cur->next;
    }

    return cur->next->data;
}

//cur移向下一位，返回的指向的人的编号
int JosephRing::Counting()
{
    cur = cur->next;
    if (cur->next == head)
        cur = cur->next;
    return cur->next->data;
}

//删除cur指向的结点，并将cur移向下一位
void JosephRing::DeleteNode()
{
    LNode *p = cur->next;
    cur->next = cur->next->next;
    delete p;
    if (cur->next == head)
        cur = cur->next;
}

//将循环链表转换成字符串
QString JosephRing::toQStr()
{
    QString str;
    LNode *p = head->next;
    while (p != head) {
        str.append(QString::number(p->data) + " ");
        p = p->next;
    }

    return str;
}

//返回当前活动人物编号
int JosephRing::CurrentData()
{
    if (cur == nullptr)
        return -1;
    else
        return cur->next->data;
}

bool JosephRing::isEmpty()
{
    return head->next == head;
}

//返回游戏是否结束（即是否只剩下一个人）
bool JosephRing::isGameOver()
{
    return head == head->next->next;
}

//将循环链表转换成整型数组，返回元素个数
int JosephRing::toArr(int *arr)
{
    int i = 0;
    LNode *p = head->next;
    while (p != head) {
        arr[i++] = p->data;
        p = p->next;
    }

    return i;
}
