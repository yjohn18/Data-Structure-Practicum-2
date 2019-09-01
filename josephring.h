#ifndef JOSEPHRING_H
#define JOSEPHRING_H

#include <QMainWindow>
typedef int Status;
typedef int ElemType;	//�ɸ�����Ҫ�޸�Ԫ�ص�����

class LinkList;	//��ǰ��������Ϊ������ԪҪ�õ�

class LNode {
protected:
    ElemType data;	//������
    LNode   *next;	//ָ����
public:
    friend class JosephRing;
    //�������κκ������൱��struct LNode
};


/* ��ͷ����ѭ������ */
/* ��Ҫ�Ĳ�������ʼ��������  */
/* Ϊ�˱���ɾ��������ָ�붼ָ��Ŀ��֮ǰ�Ľ�� */
class JosephRing {
protected:
    LNode *head;	//ͷָ��
    LNode *cur;     //��ǰ����� ֮ǰ�Ľ��
public:
    JosephRing();
    ~JosephRing();
    int PreCount(const int n);  //��cur��λ����n�����
    int	Counting();             //cur������һλ�����ص�ָ����˵ı��
    void DeleteNode();          //ɾ��curָ��Ľ�㣬����cur������һλ
    QString toQStr();           //��ѭ������ת�����ַ���
    int CurrentData();          //���ص�ǰ�������
    Status CreateRing(const int n);//���ɳ���Ϊn��Լɪ��
    bool isEmpty();
    bool isGameOver();          //������Ϸ�Ƿ���������Ƿ�ֻʣ��һ���ˣ�
    int toArr(int *arr);        //��ѭ������ת�����������飬����Ԫ�ظ���
};

#endif // JOSEPHRING_H
