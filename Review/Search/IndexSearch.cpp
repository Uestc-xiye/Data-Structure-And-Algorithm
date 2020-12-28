#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;

#define MAX 16

typedef int DataType;

typedef struct elem
{
    DataType key; //�ؼ���
} Seq;

//�����ṹ
struct index
{
    DataType key; //����ֵ
    long low;     //��ʼλ��
    long high;    //��ֹλ��
};

int IndexSearch(elem e[], DataType key, int n, index idx[], int idx_length)
{
    int k = 0;
    //����˳����ҵķ��������������ҵ��ؼ������ڵĿ�
    while (k <= idx_length && key > idx[k].key)
        k++;
    if (k > idx_length)
        return -1;
    else
    {
        //����˳����ҵķ����ӿ��в��ҹؼ�ֵ
        int i = idx[k].low;

        while (i <= idx[k].high && e[i].key != key)
        {
            i++;
        }

        if (i > idx[k].high)
            return -1;
        else
            return i;
    }
}

int main()
{
    Seq linelist[MAX] = {
        8, 20, 13, 17,
        40, 42, 45, 32,
        49, 58, 50, 52,
        67, 79, 78, 80};

    int n = sizeof(linelist) / sizeof(elem);
    DataType key;

    //����������
    index index_table[4] = {{20, 0, 3}, {45, 4, 7}, {58, 8, 11}, {80, 12, 15}};
    int idx_length = sizeof(index_table) / sizeof(index);

    printf("�������е�Ԫ��Ϊ��\n");
    for (int i = 0; i < n; i++)
    {
        cout << linelist[i].key << " ";
    }
    cout << endl
         << endl;
    cout << "������Ҫ���ҵ�ֵ��";
    cin >> key;

    if (IndexSearch(linelist, key, n, index_table, idx_length) != -1)
    {
        printf("\n�����У��ؼ���%d�����Ա��е�λ���±�Ϊ%d\n\n", key, IndexSearch(linelist, key, n, index_table, idx_length));
    }
    else
        cout << "�鲻����" << endl;

    system("pause");
    return 0;
}