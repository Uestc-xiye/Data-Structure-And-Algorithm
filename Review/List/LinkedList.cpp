#include<iostream>
#include<time.h>
#include<stdlib.h>

using namespace std;

#define OK          1
#define ERROR       0
#define OVERFLOW   -1
#define N           5
typedef int ElemType;
typedef int Status;
typedef struct LNode
{
	ElemType data;
	LNode *next;
}LNode, *LinkList;

//InitList(*L) : ��ʼ������������һ���յ����Ա�L��
Status InitList(LinkList &L)
{
	L= (LNode *)malloc(sizeof(LNode));//����һ���µ�ͷ��㣬��ͷָ��Lָ��ͷ���
	L->next = NULL;  //ͷ����ָ����ָ��NULL
	return OK;
}
//CreateListHead(LinkList L, int n)����ͷ�巨����������
void CreateListHead(LinkList &L, int n)
{
	LNode *p;//�������
	int i;
	srand(time(0));   // ��ʼ�����������
	for (int i = 0; i < n; i++)
	{
		p =(LinkList)malloc(sizeof(LNode));  //�����½��
		p->data= rand() % 100 + 1;
		p->next = L->next;
		L->next = p;
	}
}
//void CreateListTail(LinkList L, int n)����β�巨����������
void CreateListTail(LinkList &L, int n)
{
	LNode *p,*r;
	int i;
	srand(time(0));
	r = L;
	for (int i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(LNode));  //�����½��
		p->data = rand() % 100 + 1;
		r->next = p;
		r = p;
	}
	r->next = NULL;
}
//����Ų��ҽ��ֵ
Status GetElem(LinkList L, int i, ElemType *e)
{
	int j=1;
	LNode *p;
	p = L->next;
	while (p && j < i)
	{
		p = p->next;
		++j;
	}

	if (!p || j > i)
	{
		return ERROR;
	}

	*e = p->data;

	return OK;
}
//��ֵ���ұ���
int LocateElem(LinkList L, ElemType e)
{
	LNode *p = L->next;
	int i = 1;
	while (p)
	{
		if (p->data == e)
		{
			return i;
		}
		p = p->next;
		i++;
	}
	return 0;
}

//���������
Status ListInsert(LinkList &L, int i, ElemType e)
{
	LinkList P;
	LNode *s;
	int j = 1;
	P= L;
	while (P&&j < i)
	{
		P = P->next;
		j++;
	}
	if (!P || j > i)
		return ERROR;
	s = (LNode *)malloc(sizeof(LNode));
	s->data = e;
	s->next = P->next;
	P->next = s;
	return OK;
}

//ɾ��������
Status ListDelete(LinkList &L, int i, ElemType *e)
{
	int j = 1;
	LinkList P = L;
	LNode *s;
	while (P->next&&j < i)
	{
		P = P->next;
		j++;
	}
	if (!P->next || j > i)
		return ERROR;
	s = P->next;
	P->next = s->next;
	*e = s->data;
	s->next = NULL;
	return OK;
}
//�������
int GetLength(LinkList L)
{
	int i = 0;
	LinkList P = L;
	while (P->next)
	{
		++i;
		P = P->next;
	}
	return i;
}
//ClearList(*L): �����Ա���ա�
Status ClearList(LinkList &L)
{
	LNode *p, *q;
	p = L->next;
	while (p)
	{
		q = p->next;
		free(p);
		p = q;
	}
	L->next = NULL;
	return OK;
}
//��ӡ������
void PrintList(LinkList L)
{
	LinkList p;
	//cout<<
	p = L->next;
	if (p == NULL)
	{
		cout << "������Ϊ�գ�" << endl;
	}
	while (p != NULL)
	{
		cout << p->data << " ";
		p = p->next;
	}
	cout << endl;
}
int main()
{
	LinkList L=NULL;
	int choose=1;
	InitList(L);
	cout << "��ѡ��������Ž��в���" << endl;
	cout << "1.����ͷ�巨����������" << endl;
	cout << "2.����β�巨����������" << endl;
	cout << "3.����Ų��ҽ��ֵ" << endl;
	cout << "4.��ֵ���ұ���" << endl;
	cout << "5.���������" << endl;
	cout << "6.ɾ��������" << endl;
	cout << "7.�������" << endl;
	cout << "8.�����Ա���ա�" << endl;
	cout << "0.�˳���" << endl;
	while (choose)
	{
		cin >> choose;
		switch (choose)
		{
		case 1:
		{
			int n;
			cout << "������Ҫ����������ĳ���" << endl;
			cin >> n;
			CreateListHead(L, n);
			cout << "��ͷ�巨����������ɹ�" << endl;
			PrintList(L);
		}
		break;
		case 2:
		{
			int n;
			cout << "������Ҫ����������ĳ���" << endl;
			cin >> n;
			CreateListTail(L, n);
			cout << "��β�巨����������ɹ�" << endl;
			PrintList(L);
		}
		break;
		case 3:
		{
			int result,index;
			cout << "������Ҫ���ҵ�λ��" << endl;
			cin >> index;
			if (GetElem(L, index, &result))
			{
				cout << "��"<< index<<"����Ԫ��ֵΪ ��"<<result<< endl;
			}
			else
			{
				cout << "����ʧ�ܣ�" << endl;
			}
		}
		break;
		case 4:
		{
			int data;
			cout << "������Ҫ���ҵ�Ԫ��ֵ" << endl;
			cin >> data;
			int re = LocateElem(L, data);
			if (re)
			{
				cout << data << "λ�������еĵ�" << re << "��λ��" << endl;
			}
			else
			{
				cout << "Ҫ���ҵ�Ԫ��λ�ò�����" << endl;
			}
		}
		break;
		//���������
		//Status ListInsert(LinkList &L, int i, ElemType e)
		case 5:
		{
			int i;
			ElemType e;
			cout << "������Ҫ����Ԫ�ص�Ԫ��ֵ�Լ�λ��";
			cin >> e >> i;
			if (ListInsert(L, i, e))
			{
				cout << "����ɹ�����" << endl;
				PrintList(L);
			}
			else
			{
				cout << "Ԫ�ز���ʧ�ܣ�����" << endl;
				cout << "��ʾ��" << "��������Ϊ" << GetLength(L) << " ������Ч��λ�ò�������" << endl;
			}
		}
		break;
		//ɾ��������
		//Status ListDelete(LinkList &L, int i, ElemType *e)
		case 6:
		{
			int i;
			ElemType e;
			cout << "������Ҫɾ��Ԫ�ص�λ��";
			cin >> i;
			if (ListDelete(L,i,&e))
			{
				cout << "ɾ���ɹ�����" << endl;
				PrintList(L);
			}
			else
			{
				cout << "Ԫ��ɾ��ʧ�ܣ�����" << endl;
				cout << "��ʾ��" << "��������Ϊ" << GetLength(L) << " ������Ч��λ��ɾ������" << endl;
			}
		}
		break;
		case 7:
		{
			cout << "��Ϊ :"<<GetLength(L) << endl;
		}
		break;
		case 8:
		{
			ClearList(L);
			cout << "���������" << endl;
			PrintList(L);
		}
		break;
		case 0: break;
		default:
			break;
		}
	}
	system("pause");
	return 0;

}

