#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

#define MaxSize 100

typedef int DataType;

typedef struct node
{
	DataType data;
	int bf;
	int flag;
	struct node *lchild,*rchild;
}AVLNode,*AVLTree;

//��ʼ��һ��ƽ����������
AVLTree InitNode(DataType data)
{
	AVLTree Node=(AVLTree)malloc(sizeof(AVLNode));
	Node->data=data;
	Node->lchild=NULL;
	Node->rchild=NULL;
	Node->bf=0;
	Node->flag=0;
}

//��ƽ��������в���ֵΪdata��Ԫ�أ�ʹ֮��Ϊһ���µ�ƽ�����������
void InsertAVL(AVLTree *root,DataType data)
{
	AVLNode *s;
	AVLNode *a,*fa,*p,*fp,*b,*c;
	s=InitNode(data);
	if(*root==NULL) *root=s;
	else 
	{ 
		//���Ȳ���S�Ĳ���λ��fp��ͬʱ��¼��S�Ĳ���λ�������ƽ�����Ӳ�����0������-1��1���Ľ��A��AΪ���ܵ�ʧ����
		a=*root; 
		fa=NULL;
		p=*root; 
		fp=NULL;
		while(p!=NULL)
		{ 
			if(p->bf!=0) 
			{
				a=p;
				fa=fp;
			}
			fp=p;
			if (data<p->data) p=p->lchild;
			else if(data>p->data) p=p->rchild;
			else
			{
				free(s);
				return;			
			}
		}
		//����S
		if(data<fp->data) fp->lchild=s;
		else fp->rchild=s;
		//ȷ�����B�����޸�A��ƽ������
		if (data<a->data)
		{
			b=a->lchild;
			a->bf=a->bf+1;
		}
		else
		{
			b=a->rchild;
			a->bf=a->bf-1;
		}
		//�޸�B��S·���ϸ�����ƽ�����ӣ�ԭֵ��Ϊ0��
		p=b;
		while(p!=s)
			if(data<p->data)
			{
				p->bf=1;
				p=p->lchild;
			}
			else
			{
				p->bf=-1;
				p=p->rchild;
			}
		//�ж�ʧ�����Ͳ�����Ӧ����
		if(a->bf==2 && b->bf==1)       /* LL�� */
		{
			b=a->lchild;
			a->lchild=b->rchild;
			b->rchild=a;
			a->bf=0;
			b->bf=0;
			if(fa==NULL) *root=b;
			else 
			{
				if(a==fa->lchild) fa->lchild=b;
				else fa->rchild=b;
			}
		}
		else if(a->bf==2 && b->bf==-1)       /* LR�� */
		{
			b=a->lchild;
			c=b->rchild;
			b->rchild=c->lchild;
			a->lchild=c->rchild;
			c->lchild=b;
			c->rchild=a;
			if(s->data<c->data)
			{ 
				a->bf=-1;
				b->bf=0;
				c->bf=0;
			}
			else if(s->data>c->data)
			{
				a->bf=0;
				b->bf=1;
				c->bf=0;
			}
			else
			{ 
				a->bf=0;
				b->bf=0;
			}
			if(fa==NULL) *root=c;
			else if(a==fa->lchild) fa->lchild=c;
			else fa->rchild=c;
			}
		else if(a->bf==-2 && b->bf==1)       /* RL�� */
		{
			b=a->rchild;
			c=b->lchild;
			b->lchild=c->rchild;
			a->rchild=c->lchild;
			c->lchild=a;
			c->rchild=b;
			if(s->data<c->data) 
			{ 
				a->bf=0;
				b->bf=-1;
				c->bf=0;
			}
			else if(s->data>c->data)
			{
				a->bf=1;
				b->bf=0;
				c->bf=0;
			}
			else 
			{ 
				a->bf=0;
				b->bf=0;
			}
			if (fa==NULL) *root=c;
			else if(a==fa->lchild) fa->lchild=c;
			else fa->rchild=c;
		}
		else if(a->bf==-2 && b->bf==-1)       /* RR�� */
		{
			b=a->rchild;
			a->rchild=b->lchild;
			b->lchild=a;
			a->bf=0;
			b->bf=0;
			if(fa==NULL) *root=b;
			else if(a==fa->lchild) fa->lchild=b;
			else fa->rchild=b;
		}
	}
}

//��ƽ�������root��ɾȥ�ؼ���Ϊvalue�Ľ��
AVLTree DeleteAVL(AVLTree root,DataType value)
{
	AVLNode *p,*f,*s,*q;
	p=root; 
	f=NULL;
    //���ҹؼ���Ϊvalue�Ĵ�ɾ���p
	while(p)
	{
        //�ҵ�������ѭ��,fָ��p����˫�׽��
		if(p->data==value) break;
		f=p;
		if(p->data>value) p=p->lchild;
		else p=p->rchild;
	}
    //���Ҳ���������ԭ����ƽ�������
	if(p==NULL)  return root;
    //��p��������
	if(p->lchild==NULL)
	{ 
		if(f==NULL) root=p->rchild;
		else 
        {
			if(f->lchild==p) f->lchild=p->rchild;
			else f->rchild=p->rchild;
            //�ͷű�ɾ���Ľ��p
			free(p);
        }
	}
    //��p��������
	else
	{ 
		q=p; 
		s=p->lchild;
		while(s->rchild)
		{
			q=s; 
			s=s->rchild;
		}
		if(q==p) 
			q->lchild=s->lchild;
		else 
			q->rchild=s->lchild;
		p->data=s->data;
		free(s);
	}
	return root;
}

//���ļ�����Ԫ�ص�ֵ��������Ӧ��ƽ�������
void CreateAVL(AVLTree *root,const char *filename)
{ 
	FILE *fp;
	DataType keynumber;
	*root=NULL;
	fp=fopen(filename,"r+");
	while(EOF!=fscanf(fp,"%d",&keynumber)) InsertAVL(root,keynumber);
}

//�������������, rootΪָ�������������ָ��
void PreOrderCleanFlag(AVLTree root) 
{
	if(root!=NULL)
	{
		//printf("%d(%d)\t",root->data,root->bf);
		root->flag=0;
		PreOrderCleanFlag(root->lchild);
		PreOrderCleanFlag(root->rchild);
	}
}

//�������������, rootΪָ�������������ָ��
void InOrder(AVLTree root) 
{
	if(root!=NULL)
	{
		InOrder(root->lchild);
        printf("%d ",root->data);
		InOrder(root->rchild);
	}
}

//�������������, rootΪָ�������������ָ��
void PostOrder(AVLTree root) 
{
	if(root!=NULL)
	{
		PostOrder(root->lchild);
		PostOrder(root->rchild);
        printf("%d ",root->data);
	}
}

//�������, rootΪָ�������������ָ��
void LevelOrder(AVLTree root)
{
	//����һ������ 
    AVLTree Queue[MaxSize];
    
    int front=-1,rear=0;
    // ��������Ϊ�գ��������� 
    if(root==NULL) return;
    //����������� 
    Queue[rear]=root;
    //�����в�Ϊ�գ����������򣬱������� 
    while(rear!=front)
	{
		//���ӣ���ӡ���ӽ���ֵ 
        front++;
        printf("%d ",Queue[front]->data);
        //�������ӣ����ӽ������ 
        if(Queue[front]->lchild!=NULL)
		{
            rear++;
            Queue[rear]=Queue[front]->lchild;
        }
        //�����Һ��ӣ��Һ��ӽ������ 
        if(Queue[front]->rchild!=NULL)
		{
            rear++;
            Queue[rear]=Queue[front]->rchild;
        }
    }
}

//ɾ��ƽ�������, rootΪָ�������������ָ��
void DestroyAVL(AVLTree root)
{
	if(root!=NULL)
	{
		PreOrderCleanFlag(root->lchild);
		PreOrderCleanFlag(root->rchild);
		free(root);
	}
}

//�ڸ�ָ��root��ָƽ�������root�ϣ����ҹؼ��ֵ���data�Ľ�㣬�����ҳɹ�������ָ���Ԫ�ؽ��ָ�룬���򷵻ؿ�ָ��
AVLTree SearchAVL(AVLTree root,DataType data)
{ 
	AVLTree q;
	q=root;
	while(q)
	{
		q->flag=1;
		if(q->data==data)
		{
			q->flag=2;
			return q;		
		}
		if(q->data>data) q=q->lchild;
		else q=q->rchild;
	}
	return NULL;
}

//�ڸ�ָ��root��ָƽ��������н����������� 
void Exchange(AVLTree root)
{
    if(root==NULL) return;
    if(root->lchild==NULL && root->rchild==NULL) return;
    AVLTree temp=root->lchild;
    root->lchild=root->rchild;
    root->rchild=temp;
    Exchange(root->lchild);
    Exchange(root->rchild);
}

//�ڸ�ָ��root��ָƽ������������������ 
int Depth(AVLTree root)
{
    if(root==NULL) return 0;
    return 1+max(Depth(root->lchild),Depth(root->rchild));
}

int max(int a,int b)
{
    if (a>b) return a;
    return b;
}

//�ڸ�ָ��root��ָƽ��������м����ܽ����� 
int CountBiNode(AVLTree root)
{
    if(root==NULL) return 0;
    int left=CountBiNode(root->lchild);
    int right=CountBiNode(root->rchild);
    return left+right+1;
}

//��ָ��root��ָƽ��������м���Ҷ�ӽ����� 
int CountLeaf(AVLTree root)
{
    if(root==NULL) return 0;
    if(root->rchild==NULL && root->lchild==NULL) return 1;
    return (CountLeaf(root->lchild)+CountLeaf(root->rchild));
}

void DotOrderList(AVLTree root,FILE *fp)
{
	if(root==NULL)
		return;
	char lpoint=root->lchild ? ' ' : ' ';
	char rpoint=root->rchild ? ' ' : ' ';
	if(root->flag==1)
	{
		fprintf(fp,"%d[label = \"<l>%c|<d>%d|<r>%c\",color=green];\n",root->data,lpoint,root->data,rpoint);
	}
	else if(root->flag==2)
	{
		fprintf(fp,"%d[label = \"<l>%c|<d>%d|<r>%c\",color=red,fontcolor=red];\n",root->data,lpoint,root->data,rpoint);
	}
	else
		fprintf(fp,"%d[label = \"<l>%c|<d>%d|<r>%c\"];\n",root->data,lpoint,root->data,rpoint);
	DotOrderList(root->lchild,fp);
	DotOrderList(root->rchild,fp);
}

void DotOrderLink(AVLTree root,FILE *fp) 
{
	if(root==NULL)
		return;
	
	if(root->lchild)
		fprintf(fp,"%d:l:sw -> %d:d;\n",root->data,root->lchild->data);
	
	if(root->rchild)
		fprintf(fp,"%d:r:se -> %d:d;\n",root->data,root->rchild->data);

	DotOrderLink(root->lchild,fp);
	DotOrderLink(root->rchild,fp);
}

void MakeDot(AVLTree root,char *tital=NULL)
{
	FILE *fp=fopen("avltree.gv","w+");
	fprintf(fp,"digraph BSTree {\n");
	if(tital != NULL)
	{
		fprintf(fp,"labelloc = t; labeljust = l;\n");
		fprintf(fp,"label = \"%s\";\n",tital);		
	}
	fprintf(fp,"node [fontname = Verdana, color=navy, shape=record, height=.1];\n");
	fprintf(fp,"edge [fontname = Verdana, color=navy, style=solid];\n");
	DotOrderList(root,fp);
	DotOrderLink(root,fp);
	fprintf(fp,"}\n\n");
	fclose(fp);
}

int main()
{
	AVLTree root;
	CreateAVL(&root,"./data.txt");
	MakeDot(root);
	PreOrderCleanFlag(root);
	system("dot.exe -Tpng avltree.gv -o avltree.png");
	
	printf("��ƽ������������Ϊ�� %d\n��ƽ����������ܽ����Ϊ�� %d\n��ƽ���������Ҷ�ӽ����Ϊ�� %d\n��������Ľ��Ϊ��\n",Depth(root),CountBiNode(root),CountLeaf(root));
	InOrder(root);
	
	SearchAVL(root,709);
	MakeDot(root);
	system("dot.exe -Tpng avltree.gv -o avltree_search(709).png");
	
	PreOrderCleanFlag(root);
	SearchAVL(root,98); 
	MakeDot(root);
	system("dot.exe -Tpng avltree.gv -o avltree_search(98).png");

	PreOrderCleanFlag(root);
	DeleteAVL(root,340);
	MakeDot(root);
	system("dot.exe -Tpng avltree.gv -o avltree_delete(340).png");
	
	DestroyAVL(root);
	return 0;
}
