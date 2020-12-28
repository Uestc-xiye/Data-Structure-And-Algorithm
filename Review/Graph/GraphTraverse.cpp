#include<iostream>
#include<stdio.h>
#include<string>
#include<queue>
#include<string.h>
using namespace std;

#define INFINITY 0X7fffffff
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAX_VERTEX_NUM 30

typedef char InfoType;
typedef int Status;
typedef int Boolean;
typedef string VertexType;
typedef enum {DG,DN,UDG,UDN} GraphKind;

Boolean visited[MAX_VERTEX_NUM];

typedef struct ArcCell///��(�ڽӾ���)
{
    int adj;
    InfoType *info;
} ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct graph
{
    string vexs[MAX_VERTEX_NUM];//�����
    AdjMatrix arcs;             //�ڽӾ���
    int vexnum,arcnum;          //�����������
    GraphKind kind;
}Graph;

Status (*VisitFunc)(Graph G,int v);

Status LocateVex(Graph G,string name)//��ȡ�����
{
    for(int i=0; i<G.vexnum; i++)
        if(name==G.vexs[i]) return i;
    return -1;
}

Status CreateDG(Graph &G)//�ڽӾ���(������Ȩ����ͼ)
{
    int IncInfo;
    printf("������Ȩ����ͼ�������������ܽ�������ܱ������Ƿ������Ϣ:\n");
    scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
    printf("��Ϊ��1��n���������:\n");
    for(int i=0; i<G.vexnum; i++)
        cin>>G.vexs[i];
    for(int i=0; i<G.vexnum; i++)
        for(int j=0; j<G.vexnum; j++)
        {
            G.arcs[i][j].adj=INFINITY;
            G.arcs[i][j].info=NULL;
        }
    string v1,v2;
    printf("������%d������ָ���ҵ������:\n",G.arcnum);
    for(int k=0; k<G.arcnum; k++)
    {
        cin>>v1>>v2;
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        G.arcs[i][j].adj=TRUE;//��Ȩ
        if(IncInfo) scanf("%s",G.arcs[i][j].info);
    }
    return OK;
}

Status CreateDN(Graph &G)//�ڽӾ���(������Ȩ������)
{
    int IncInfo;
    printf("������Ȩ�������������������ܽ�������ܱ������Ƿ������Ϣ:\n");
    scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
    printf("��Ϊ��1��n���������:\n");
    for(int i=0; i<G.vexnum; i++)
        cin>>G.vexs[i];
    for(int i=0; i<G.vexnum; i++)
        for(int j=0; j<G.vexnum; j++)G.arcs[i][j].adj=INFINITY,G.arcs[i][j].info=NULL;
    string v1,v2;
    int w;
    printf("������%d������ָ���ҵ���������Ȩ:\n",G.arcnum);
    for(int k=0; k<G.arcnum; k++)
    {
        cin>>v1>>v2>>w;
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        G.arcs[i][j].adj=w;//��Ȩ
        if(IncInfo) scanf("%s",G.arcs[i][j].info);
    }
    return OK;
}

Status CreateUDG(Graph &G)//�ڽӾ���(������Ȩ����ͼ)
{
    int IncInfo;
    printf("������Ȩ����ͼ�������������ܽ�������ܱ������Ƿ������Ϣ:\n");
    scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
    printf("��Ϊ��1��n���������:\n");
    for(int i=0; i<G.vexnum; i++)
        cin>>G.vexs[i];
    for(int i=0; i<G.vexnum; i++)
        for(int j=0; j<G.vexnum; j++)
            G.arcs[i][j].adj=INFINITY,G.arcs[i][j].info=NULL;
    string v1,v2;
    printf("������%d���໥�����������:\n",G.arcnum);
    for(int k=0; k<G.arcnum; k++)
    {
        cin>>v1>>v2;
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        G.arcs[i][j].adj=TRUE;//��Ȩ
        if(IncInfo) scanf("%s",G.arcs[i][j].info);
        G.arcs[j][i]=G.arcs[i][j];//����ͼ,�ṹ�帳ֵ
    }
    return OK;
}

Status CreateUDN(Graph &G)//�ڽӾ���(������Ȩ������)
{
    int IncInfo;
    printf("������Ȩ�������������������ܽ�������ܱ������Ƿ������Ϣ:\n");
    scanf("%d%d%d",&G.vexnum,&G.arcnum,&IncInfo);
    printf("��Ϊ��1��n���������:\n");
    for(int i=0; i<G.vexnum; i++)
        cin>>G.vexs[i];
    for(int i=0; i<G.vexnum; i++)
        for(int j=0; j<G.vexnum; j++)
            G.arcs[i][j].adj=INFINITY,G.arcs[i][j].info=NULL;
    string v1,v2;
    printf("������%d���໥��������������Ȩ:\n",G.arcnum);
    int w;//��Ȩ
    for(int k=0; k<G.arcnum; k++)
    {
        cin>>v1>>v2>>w;
        int i=LocateVex(G,v1);
        int j=LocateVex(G,v2);
        G.arcs[i][j].adj=w;//��Ȩ
        if(IncInfo) scanf("%s",G.arcs[i][j].info);
        G.arcs[j][i]=G.arcs[i][j];//����ͼ,�ṹ�帳ֵ
    }
    return OK;
}

void DFS(Graph G,int v)//�ڽӾ���DFS
{
    visited[v]=TRUE;
    VisitFunc(G,v);
    for(int w=0; w<G.vexnum; w++)
        if(G.arcs[v][w].adj!=INFINITY&&!visited[w])
            DFS(G,w);
}

void DFSTraverse(Graph G,Status (*Visit)(Graph G,int v))
{
    VisitFunc=Visit;
    printf("�������������������ʼ���:\n");
    for(int v=0; v<G.vexnum; v++)
        visited[v]=FALSE;
    string st;
    cin>>st;
    int tmp=LocateVex(G,st);
    printf("�������������������:\n");
    DFS(G,tmp);
    for(int v=0; v<G.vexnum; v++)
        if(!visited[v])
            DFS(G,v);
    printf("\n");
}

void BFSTraverse(Graph G,Status (*Visit)(Graph G,int v))//�ڽӾ���BFS
{
    for(int v=0; v<G.vexnum; v++)visited[v]=FALSE;
    queue<int>Q;
    printf("������������������ʼ���:\n");
    string st;
    cin>>st;
    printf("�������������������:\n");
    int temp=LocateVex(G,st);
    Visit(G,temp);
    Q.push(temp);
    visited[temp]=TRUE;
    while(!Q.empty())
    {
        int tmp=Q.front();
        Q.pop();
        for(int w=0; w<G.vexnum; w++)
        {
            if(!visited[w]&&G.arcs[tmp][w].adj!=INFINITY)
            {
                visited[w]=TRUE;
                Visit(G,w);
                Q.push(w);
            }
        }
    }
    for(int v=0; v<G.vexnum; v++)//ʣ����ͨ����
    {
        if(!visited[v])
        {
            visited[v]=TRUE;
            Visit(G,v);
            Q.push(v);
            while(!Q.empty())
            {
                int tmp=Q.front();
                Q.pop();
                for(int w=0; w<G.vexnum; w++)
                {
                    if(!visited[w]&&G.arcs[tmp][w].adj!=INFINITY)
                    {
                        visited[w]=TRUE;
                        Visit(G,w);
                        Q.push(w);
                    }
                }
            }
        }
    }
    printf("\n");
}

Status CreateGraph(Graph &G)///�ڽӾ���
{
    printf("�����뽨ͼ����(1:��Ȩ����ͼ��2:��Ȩ��������3:��Ȩ����ͼ��4:��Ȩ������):\n");
    scanf("%d",&G.kind);///����ͼ������
    switch(G.kind-1)
    {
        case DG:
            return CreateDG(G);
        case DN:
            return CreateDN(G);
        case UDG:
            return CreateUDG(G);
        case UDN:
            return CreateUDN(G);
        default:
            return ERROR;
    }
}

Status visit(Graph G,int v)///�ڽӾ������
{
    cout<<G.vexs[v]<<" ";
}

int main()
{
    while(true)
    {
        Graph g;
        CreateGraph(g);///�ڽӾ���
        DFSTraverse(g,visit);///�����ڽӾ���
        BFSTraverse(g,visit);///�����ڽӾ���
    }
    system("pause");
    return 0;
}
/*
�������룺
3
8 9 0
V1 V2 V3 V4 V5 V6 V7 V8

V1 V2
V2 V4
V4 V8
V8 V5
V2 V5
V1 V3
V3 V6
V3 V7
V6 V7

V1

V1
*/
