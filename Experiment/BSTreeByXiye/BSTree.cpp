#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<math.h>
using namespace std;

#define MaxSize 100

typedef int DataType;

//�����������ṹ����
typedef struct node
{
	DataType data;
	struct node *lchild,*rchild;
	int flag;
}BSTNode,*BSTree;

//��ʼ��һ���������������
BSTree InitNode(DataType data)
{
	BSTree Node=(BSTree)malloc(sizeof(BSTNode));
	Node->data=data;
	Node->lchild=NULL;
	Node->rchild=NULL;
	Node->flag=0;
	return Node;
}

//���ڶ����������в����ڹؼ��ֵ���data��Ԫ�أ������Ԫ��
void InsertBST(BSTree *root, DataType data)
{
	if(*root==NULL)
	{
		*root=InitNode(data);
	}
	else 
	{
		if(data<(*root)->data) InsertBST(&((*root)->lchild),data);
		else 
		{
			if(data>(*root)->data) InsertBST(&((*root)->rchild),data);
		}
	}
}

//���ļ�����Ԫ�ص�ֵ��������Ӧ�Ķ���������
void CreateBST(BSTree *root,const char *filename)
{ 
	FILE *fp;
	DataType keynumber;
	*root=NULL;
	fp=fopen(filename,"r+");
	if(fp==NULL) exit(0x01);
	while(EOF!=fscanf(fp,"%d",&keynumber)) InsertBST(root,keynumber);
}

//�������������, rootΪָ�������������ָ��
void PreOrderCleanFlag(BSTree root) 
{
	if(root!=NULL)
	{
		root->flag=0;
		PreOrderCleanFlag(root->lchild);
		PreOrderCleanFlag(root->rchild);
	}
}

//�������������, rootΪָ�������������ָ��
void InOrder(BSTree root) 
{
	if(root!=NULL)
	{
		InOrder(root->lchild);
        printf("%d ",root->data);
		InOrder(root->rchild);
	}
}

//�������������, rootΪָ�������������ָ��
void PostOrder(BSTree root) 
{
	if(root!=NULL)
	{
		PostOrder(root->lchild);
		PostOrder(root->rchild);
        printf("%d ",root->data);
	}
}

//�������, rootΪָ�������������ָ��
void LevelOrder(BSTree root)
{
	//����һ������ 
    BSTree Queue[MaxSize];
    
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

//ɾ�����������, rootΪָ�������������ָ��
void DestroyBST(BSTree root)
{
	if(root!=NULL)
	{
		PreOrderCleanFlag(root->lchild);
		PreOrderCleanFlag(root->rchild);
		free(root);
	}
}

//�ڸ�ָ��root��ָ����������root�ϣ����ҹؼ��ֵ���data�Ľ�㣬�����ҳɹ�������ָ���Ԫ�ؽ��ָ�룬���򷵻ؿ�ָ��
BSTree SearchBST(BSTree root,DataType data)
{ 
	BSTree q;
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

//�ڶ���������root��ɾȥ�ؼ���Ϊvalue�Ľ��
BSTree DeleteBST(BSTree root,DataType value)
{
	BSTNode *p,*f,*s,*q;
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
    //���Ҳ���������ԭ���Ķ���������
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

//�ڸ�ָ��root��ָ�����������н����������� 
void Exchange(BSTree root)
{
    if(root==NULL) return;
    if(root->lchild==NULL && root->rchild==NULL) return;
    BSTree temp=root->lchild;
    root->lchild=root->rchild;
    root->rchild=temp;
    Exchange(root->lchild);
    Exchange(root->rchild);
}

//�ڸ�ָ��root��ָ��������������������� 
int Depth(BSTree root)
{
    if(root==NULL) return 0;
    return 1+max(Depth(root->lchild),Depth(root->rchild));
}

int max(int a,int b)
{
    if (a>b) return a;
    return b;
}

//�ڸ�ָ��root��ָ�����������м����ܽ����� 
int CountBiNode(BSTree root)
{
    if(root==NULL) return 0;
    int left=CountBiNode(root->lchild);
    int right=CountBiNode(root->rchild);
    return left+right+1;
}

//��ָ��root��ָ�����������м���Ҷ�ӽ����� 
int CountLeaf(BSTree root)
{
    if(root==NULL) return 0;
    if(root->rchild==NULL && root->lchild==NULL) return 1;
    return (CountLeaf(root->lchild)+CountLeaf(root->rchild));
}

void DotOrderList(BSTree root,FILE *fp)
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

void DotOrderLink(BSTree root,FILE *fp) 
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

void MakeDot(BSTree root,char *tital=NULL)
{
	FILE *fp=fopen("bstree.gv","w+");
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
	BSTree root;
	CreateBST(&root,"./data.txt");
	MakeDot(root);
	PreOrderCleanFlag(root);
	system("dot.exe -Tpng bstree.gv -o bstree.png");
	
	printf("�ö��������������Ϊ�� %d\n�ö������������ܽ����Ϊ�� %d\n�ö�����������Ҷ�ӽ����Ϊ�� %d\n��������Ľ��Ϊ��\n",Depth(root),CountBiNode(root),CountLeaf(root));
	InOrder(root);
	
	SearchBST(root,62);
	MakeDot(root);
	system("dot.exe -Tpng bstree.gv -o bstree_search(62).png");
	
	PreOrderCleanFlag(root);
	SearchBST(root,98); 
	MakeDot(root);
	system("dot.exe -Tpng bstree.gv -o bstree_search(98).png");
	
	PreOrderCleanFlag(root);
	DeleteBST(root,822);
	MakeDot(root);
	system("dot.exe -Tpng bstree.gv -o bstree_delete(822).png");
	 
	DestroyBST(root);
	return 0;
}
