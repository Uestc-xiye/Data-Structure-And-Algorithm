#include<iostream>
#include<stack>
#include<fstream>

using namespace std;

typedef struct node
{
    int **edges;//�ڽӾ���
    int n;//������
    int e;//����
}Graph;

//��ʼ��ͼ
Graph CreateGraph(int n,int e)
{
	Graph graph;
	graph.n=n;
	graph.e=e;
	graph.edges=(int **)malloc(sizeof(int *)*graph.n);

	for(int i=0;i<graph.n;i++)
	{
		graph.edges[i]=(int *)malloc(sizeof(int)*graph.n);
	}

	for(int i=0;i<graph.n;i++)
    {
		for(int j=0;j<graph.n;j++)
        {
			graph.edges[i][j]=0;
		}
	}

	return graph;
}

//��ʼ��dist
int *CreateDist(int size)
{
	int *dist=new int[size];
	return dist;
}

//��ʼ��path
int *CreatePath(int size)
{
	int *path=new int[size];
	return path;
}

//��ʼ��visited
bool *CreateVisited(int size)
{
	bool *visited=(bool *)malloc(sizeof(bool)*size);
	return visited;
}

//�ͷ��ڽӾ���ռ�
void FreeGraph(Graph g)
{
	for(int i=0;i<g.n;i++)
	{
		free(g.edges[i]);
	}
	free(g.edges);
}

void DijkstraDot(Graph g,int *path,bool *visited,int vs)
{
	FILE *fp=fopen("dijkstra.gv","w+");
	fprintf(fp,"digraph Dijkstra {\nnode [shape=ellipse];\n");
	fprintf(fp,"v%d[shape=diamond,color=red,fontcolor=red];\n",vs);

	for(int i=0;i<g.n && i!=vs;i++)
	{
		fprintf(fp,"v%d;\n",i);
	}
		
	for(int i=0;i<g.n;i++)  
	{  
		for(int j=0;j<g.n;j++)  
 		{  
 			if(g.edges[i][j])
			{
				if(visited[i] && visited[j] && path[j]==i)
				{
					fprintf(fp,"v%d[fontcolor=red,color=red];\n",i);
					fprintf(fp,"v%d[fontcolor=red,color=red];\n",j);
					fprintf(fp,"v%d->v%d[style=bold,label=%d,fontcolor=red,color=red];\n",i,j,g.edges[i][j]);
				}
				else
				{
					fprintf(fp,"v%d->v%d[style=bold,label=%d];\n",i,j,g.edges[i][j]);	
				}
			}
  		}  
   	} 
 	fprintf(fp,"}\n");
 	fclose(fp);
}

//vs��ʾԴ���� 
void DijkstraPath(Graph g,int *dist,int *path,int vs)
{
    bool *visited=CreateVisited(g.n);
	//��ʼ��
    for(int i=0;i<g.n;i++)
    {
        if(g.edges[vs][i]>0 && i!=vs)
        {
            dist[i]=g.edges[vs][i];
			//path��¼���·���ϴ�vs��i��ǰһ������
            path[i]=vs; 
        }
        else
        {
			//��i����vsֱ�����ڣ���Ȩֵ��Ϊ�����
            dist[i]=INT_MAX;
            path[i]=-1;
        }
        visited[i]=false;
        path[vs]=vs;
        dist[vs]=0;
    }
    FILE *fp=fopen("dijkstra.gv","w+");
	fprintf(fp,"digraph Dijkstra {\nnode [shape=ellipse];\n");
	fprintf(fp,"v%d[shape=diamond,color=red,fontcolor=red];\n",vs);

	for(int i=0;i<g.n && i!=vs;i++)
	{
		fprintf(fp,"v%d; ",i);
	}

	for(int i=0;i<g.n;i++)  
  	{  
       	for(int j=0;j<g.n;j++)  
       	{  
       		if(g.edges[i][j])
			{
				fprintf(fp,"v%d->v%d[style=bold,label=%d];\n",i,j,g.edges[i][j]);
			}
  		}  
   	}
	fprintf(fp,"}\n");
	fclose(fp);
	system("sfdp.exe -Tpng dijkstra.gv -o DijkSetp01.png");
    visited[vs]=true;
	//ѭ����չn-1��
    for(int i=1;i<g.n;i++) 
    {
        int min=INT_MAX;
        int u;
		//Ѱ��δ����չ��Ȩֵ��С�Ķ���
        for(int j=0;j<g.n;j++)
        {
            if(!visited[j] && dist[j]<min)
            {
                min=dist[j];
                u=j;        
            }
        } 
        visited[u]=true;
		//����dist�����ֵ��·����ֵ
        for(int k=0;k<g.n;k++) 
        {
            if(!visited[k] && g.edges[u][k]>0 && min+g.edges[u][k]<dist[k])
            {
                dist[k]=min+g.edges[u][k];
                path[k]=u; 
            }
        }
		DijkstraDot(g,path,visited,vs);
	 	char orderstr[128];
		sprintf(orderstr,"sfdp.exe -Tpng dijkstra.gv -o DijkSetp%02d.png",i+1);
		system(orderstr);        
    } 
}

//��ӡԴ����vs�����������·��
void PrintPath(Graph g,int *dist,int *path,int vs)
{
	for(int i=0;i<g.n;i++)
	{
		if(vs!=i)
		{
			printf("v%d -> v%d, minDist: %d, path: v%d <- ",vs,i,dist[i],i);
			int temp=path[i];
			while(vs!=temp)
			{
				printf("v%d <- ",temp);
				temp=path[temp];
		    }
		    printf("v%d",vs);
			printf("\n");
		}
	}
}

//��ӡ�ڽӾ���
void PrintGraph(Graph g)
{
	for(int i=0;i<g.n;i++)
	{
		for(int j=0;j<g.n;j++)
		{
			printf("%2d ",g.edges[i][j]);
		}
		printf("\n");
	}
}

int main(int argc,char *argv[])
{
    if(argc<3) return 0x01;

	Graph g=CreateGraph(atoi(argv[1]),atoi(argv[2]));
	int *dist=CreateDist(g.n);
    int *path=CreatePath(g.n);
	int maxsinglearch,edgeCounter;
	
	if(g.e>=g.n)
	{
		maxsinglearch=g.n;
		for(int i=0;i<g.n;i++)
		{
			g.edges[i][(i+1)%g.n]=g.n/2+rand()%maxsinglearch;
		}
		edgeCounter=g.n;		
	}
	else edgeCounter=0;
	
	maxsinglearch=g.n;
   	while(edgeCounter<g.e)
   	{
   		rand();
	   	int s=rand()%g.n;
	   	int t=rand()%g.n;
	   	
		//�������û��˫�򻡵�����ͼ
	   	if( s!=t && !g.edges[s][t] && (g.e>3*g.n || !g.edges[t][s]))  
	   	{
	   		g.edges[s][t]=rand()%maxsinglearch;
	   		edgeCounter++;
	   	}
 	}

	printf("������ɵ��ڽӾ���\n");
	PrintGraph(g);
	printf("\n");

	int vs=0;
	
    FILE *fp=fopen("DijkInitGraph.gv","w+");
	fprintf(fp,"digraph DijkInitGraph {\nnode [shape=ellipse];\n");
	fprintf(fp,"v%d[shape=diamond];\n",vs);

	for(int i=0;i<g.n && i!=vs;i++)
	{
		fprintf(fp,"v%d; ",i);
	}

 	for(int i=0;i<g.n;i++)
    {
		for(int j=0;j<g.n;j++)  
        {
			if(g.edges[i][j])
			{
				fprintf(fp,"v%d->v%d[style=bold,label=%d];\n",i,j,g.edges[i][j]);
			}
		}
	}

 	fprintf(fp,"}\n");
 	fclose(fp);
 	system("sfdp.exe -Tpng DijkInitGraph.gv -o DijkInitGraph.png");

    //0��ʾ�����0�Žڵ㿪ʼ 
    DijkstraPath(g,dist,path,vs);

    //��ӡԴ����vs�����������·��
	printf("Դ����v0�����������·��Ϊ�� \n");
	PrintPath(g,dist,path,vs);
	printf("\n");

	//�ͷŽ��
	FreeGraph(g);
		
    return 0;
}
