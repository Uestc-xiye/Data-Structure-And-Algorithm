#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

typedef int DataType;

#define MAXSIZE 100

typedef struct seq
{
    DataType key;
}Seq;

int SeqSearch(Seq array[],int n,DataType key)
{
    int i=n;
    array[0].key=key;
    while(array[i].key!=key) i--;
    return i;
}

int main()
{
    int n;
    int key;
    Seq q[MAXSIZE];
    cout<<"���������鳤�ȣ�";
    cin>>n;
    cout<<"���������ݣ�";
    for(int i=1;i<=n;i++)
    {
        int x;
        cin>>x;
        q[i].key=x;
    }
    cout<<"������Ҫ���ҵ�ֵ��";
    cin>>key;
    if(SeqSearch(q,n,key)) cout<<"�����У�"<<key<<"���±�Ϊ��"<<SeqSearch(q,n,key)<<endl;
    else cout<<"�鲻����"<<endl;
    
    system("pause");
    return 0;
}