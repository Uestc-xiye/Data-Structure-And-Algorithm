#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

#define ARRAY_LENGTH 12

int maxbit(int a[], int n) //���������������ݵ����λ��
{
    int maxData = a[0]; ///< �����
    /// ������������������λ����������ԭ������ÿ�����ж���λ������΢�Ż��㡣
    for (int i = 1; i < n; ++i)
    {
        if (maxData < a[i])
            maxData = a[i];
    }
    int d = 1;
    int p = 10;
    while (maxData >= p)
    {
        //p *= 10; // Maybe overflow
        maxData /= 10;
        ++d;
    }
    return d;
    /*    int d = 1; //��������λ��
    int p = 10;
    for(int i = 0; i < n; ++i)
    {
        while(data[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;*/
}

void RadixSort(int a[], int n) //��������
{
    int d = maxbit(a, n);
    int *tmp = new int[n];
    int *count = new int[10]; //������
    int i, j, k;
    int radix = 1;
    for (i = 1; i <= d; i++) //����d������
    {
        for (j = 0; j < 10; j++)
            count[j] = 0; //ÿ�η���ǰ��ռ�����
        for (j = 0; j < n; j++)
        {
            k = (a[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
            count[k]++;
        }
        for (j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
        for (j = n - 1; j >= 0; j--)            //������Ͱ�м�¼�����ռ���tmp��
        {
            k = (a[j] / radix) % 10;
            tmp[count[k] - 1] = a[j];
            count[k]--;
        }
        for (j = 0; j < n; j++) //����ʱ��������ݸ��Ƶ�data��
            a[j] = tmp[j];
        radix = radix * 10;
    }
    delete[] tmp;
    delete[] count;
}

int main()
{
    int array[ARRAY_LENGTH] = {23, 15, 12, 35, 46, 19, 20, 14, 8, 74, 86, 25};

    cout << "ԭ���У�";
    for (int i = 0; i < ARRAY_LENGTH; i++)
        cout << array[i] << " ";
    cout << endl
         << endl;

    RadixSort(array, ARRAY_LENGTH);

    cout << endl
         << "���ս����";
    for (int i = 0; i < ARRAY_LENGTH; i++)
        printf("%d ", array[i]);
    cout << endl;
    system("pause");
    return 0;
}