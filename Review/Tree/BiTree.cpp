#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;

typedef char DataType;

#define MAXSIZE 100

typedef struct node
{
    DataType data;
    struct node *lchild;
    struct node *rchild;
}BiTreeNode,*BiTree;

//������������
void CreateBiTree(BiTree &root)
{
    char c;
    cin>>c;
    if(c=='#')
    {
        root=NULL;
    }
    else
    {
        root=(BiTree)malloc(sizeof(BiTreeNode));
        root->data=c;
        CreateBiTree(root->lchild);
        CreateBiTree(root->rchild);
    }
}

//�ݹ�ʵ���������
void PreOrder(BiTree root)
{
    if(root!=NULL)
    {
        cout<<root->data<<" ";
        PreOrder(root->lchild);
        PreOrder(root->rchild);
    }
}

//�ݹ�ʵ���������
void InOrder(BiTree root)
{
    if(root!=NULL)
    {
        InOrder(root->lchild);
        cout<<root->data<<" ";
        InOrder(root->rchild);
    }
}

//�ݹ�ʵ�ֺ������
void PostOrder(BiTree root)
{
    if(root!=NULL)
    {
        PostOrder(root->lchild);
        PostOrder(root->rchild);
        cout<<root->data<<" ";
    }
}

//�ǵݹ�ʵ���������
void NonPreOrder(BiTree root)
{
    BiTree S[MAXSIZE];
    BiTree p;
    int top=-1;
    S[++top]=root;
    while(top!=-1)
    {
        p=S[top--];
        cout<<p->data<<" ";
        if(p->rchild!=NULL) S[++top]=p->rchild;
        if(p->lchild!=NULL) S[++top]=p->lchild;
    }
}

//�ǵݹ�ʵ���������
void NonInOrder(BiTree root)
{
    BiTree S[MAXSIZE];
    BiTree p=root;
    int top=-1;
    while(top!=-1 || p!=NULL)
    {
        while(p!=NULL)
        {
            S[++top]=p;
            p=p->lchild;
        }
        if(top!=-1)
        {
            p=S[top--];
            cout<<p->data<<" ";
            p=p->rchild;
        }
    }
}

//����ʵ�ֲ�α���
void LevelOrder(BiTree root)
{
    BiTree Queue[MAXSIZE];
    int front=-1;
    int rear=0;
    Queue[rear]=root;
    while(rear!=front)
    {
        cout<<Queue[++front]->data<<" ";
        if(Queue[front]->lchild) Queue[++rear]=Queue[front]->lchild;
        if(Queue[front]->rchild) Queue[++rear]=Queue[front]->rchild;
    }
}

//������������
int Depth(BiTree root)
{
    if(root==NULL) return 0;
    return max(Depth(root->lchild),Depth(root->rchild))+1;
}

int max(int a,int b)
{
    if(a>b) return a;
    else return b;
}

//��Ҷ�ӽ�������
int LeafCount(BiTree root)
{
    if(root==NULL) return 0;
    if(root->lchild==NULL && root->rchild==NULL) return 1;
    return LeafCount(root->lchild)+LeafCount(root->rchild);
}

//���Ϊ1�Ľ�������
int DegreeOneCount(BiTree root)
{
    if(root==NULL) return 0;
    if((root->lchild!=NULL && root->rchild==NULL) || (root->lchild==NULL && root->rchild!=NULL))
        return DegreeOneCount(root->lchild)+DegreeOneCount(root->rchild)+1;
    return DegreeOneCount(root->lchild)+DegreeOneCount(root->rchild);
}

//���Ϊ2�Ľ�������
int DegreeTwoCount(BiTree root)
{
    if(root==NULL) return 0;
    if(root->lchild!=NULL && root->rchild!=NULL)
        return DegreeTwoCount(root->lchild)+DegreeTwoCount(root->rchild)+1;
    return DegreeTwoCount(root->lchild)+DegreeTwoCount(root->rchild);
}

//�������У�ABD##E##CF###
int main()
{
    BiTree root;
    CreateBiTree(root);

    cout<<"�����������: "<<Depth(root)<<endl;
    cout<<"��������Ҷ�ӽ����: "<<LeafCount(root)<<endl;
    cout<<"��Ϊ1�Ľ����: "<<DegreeOneCount(root)<<endl;
    cout<<"��Ϊ2�Ľ����: "<<DegreeTwoCount(root)<<endl;

    cout<<"�ݹ��������: ";
    PreOrder(root);
    cout<<endl;
    cout<<"�ǵݹ��������: ";
    NonPreOrder(root);
    cout<<endl;

    cout<<"�ݹ��������: ";
    InOrder(root);
    cout<<endl;
    cout<<"�ǵݹ��������: ";
    NonInOrder(root);
    cout<<endl;

    cout<<"�ݹ�������: ";
    PostOrder(root);
    cout<<endl;

    cout<<"��α���: ";
    LevelOrder(root);
    cout<<endl;

    system("pause");
    return 0;
}