#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAXSIZE 100

typedef int DataType;

//�ǵݹ�ʵ���۰����
int HalfSearch(DataType array[],DataType n,DataType key)
{
    int low=1;
    int high=n;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(key<array[mid]) high=mid-1;
        else if(key>array[mid]) low=mid+1;
        else return mid;
    }
    return 0;
}

//�ݹ�ʵ��ʵ���۰����
int BinSearch(DataType array[],DataType low,DataType high,DataType key)
{
    if(low>high) return 0;
    int mid=(low+high)/2;
    if(key<array[mid]) return BinSearch(array,low,mid-1,key);
    else if(key>array[mid]) return BinSearch(array,mid+1,high,key);
    else return mid;
}

int main()
{
    int n;
    int key1,key2;
    cout<<"���������鳤�ȣ�";
    cin>>n;
    int a[MAXSIZE];
    cout<<"�Զ��������飺";
    for(int i=1;i<=n;i++)
    {
        a[i]=10*i;
        cout<<a[i]<<" ";
    }
    cout<<endl;

    cout<<"�ǵݹ�ʵ�֣�"<<endl;
    cout<<"������Ҫ���ҵ�ֵ��";
    cin>>key1;
    if(HalfSearch(a,n,key1)) cout<<"�����У�"<<key1<<"���±�Ϊ��"<<HalfSearch(a,n,key1)<<endl;
    else cout<<"�鲻����"<<endl;

    cout<<"�ݹ�ʵ�֣�"<<endl;
    cout<<"������Ҫ���ҵ�ֵ��";
    cin>>key2;
    if(BinSearch(a,1,n,key2)) cout<<"�����У�"<<key2<<"���±�Ϊ��"<<BinSearch(a,1,n,key2)<<endl;
    else cout<<"�鲻����"<<endl;

    system("pause");
    return 0;
}