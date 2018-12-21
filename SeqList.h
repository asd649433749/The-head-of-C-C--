#pragma once
#include<stdio.h>
#define Maxsize 100

//�����������͸��ṹ��
typedef char DataType;//DataType ����Ӧ�����Լ��ıȽϴ�С�ĺ���������Ϊ����ʹ��int��
typedef struct
{
	DataType list[Maxsize];
	int size;

}SeqList;

//��ʼ��˳���
void ListInitiate(SeqList *L)
{
	L->size = 0;
}
//��˳���Ԫ�ظ���
int ListLength(SeqList *L)//��ֵ�����ȴ���ṹ��Ҫ��Ч
{
	return L->size;
}

//ȡ����Ԫ��(��0��ʼ)
int ListGet(SeqList *L, int index, DataType *x)
{
	if (index >= L->size || index<0)
	{
		return 0;//ȡԪ��λ��index����
	}
	*x = L->list[index];
	return 1;
}

//����˳���
int ListInsert(SeqList *L, DataType x)
{
	int i, flag = 0;
	DataType m;//DataType ����Ӧ�����Լ��ıȽϴ�С�ĺ���������Ϊ����ʹ��int��
			   //���ú��ƱȽ�
	for (i = L->size; i >= 0; i--)
	{
		if (ListGet(L, i - 1, &m))//��mȡ��i-1λ�õ�Ԫ��,���i-1��>=0����ȡ������ƻ����
			if (m>x)
			{
				L->list[i] = m;//�������ʹ�ò���ȫ�ķ�ʽ������������ô�Ͻ���ȡֵ��ʽ�γ��������ĶԱ�
			}
			else
			{
				flag = 1;
				L->list[i] = x;
				break;//����ѭ��;
			}
		else//���mȡֵȡ����0����������ʵi��ʱΪ0������x��Ҫ����i��λ��
		{
			flag = 1;
			L->list[i] = x;
			break;//����ѭ��;
		}
	}
	if (flag == 1)
	{
		L->size++;
		return 1;
	}
	else return 0;
}

//ɾ��Ԫ�أ�������x���أ����ҿ���ȱʡ
int ListDelete(SeqList *L, int index, DataType *x)
{
	int i;
	if (L->size == 0)
	{
		return 0;//�Ѿ�û��Ԫ�ؿ���ɾ����
	}
	if (index >= L->size || index<0)
	{
		return 0;//ȡԪ��λ��index����
	}
	//�Ȱ�Ԫ�ش���
	if (x != NULL)*x = L->list[index];
	//ѭ��ǰ��ɾ��
	for (i = index; i<L->size - 1; i++)
	{
		L->list[i] = L->list[i + 1];//ǰ������ú���������ǵ�
	}
	L->size--;
	L->list[L->size] = 0;//Ϊ�˲�����ȫ�������һ����0��ɾ�������һ������
	return 1;
}

//�ϲ�����
int ListMerge(SeqList *L1, SeqList *L2, SeqList *L3)
{
	int i;
	DataType x;
	//L3->size = L2->size + L1->size;//��ֵsize ��������
	if (L1 == NULL || L2 == NULL)
	{
		return 0;//�������󣬺ϲ�ʧ��
	}
	for (i = 0; i < L1->size; i++)
	{
		ListGet(L1, i, &x);
		ListInsert(L3, x);// L2->list[i]
	}
	for (i = 0; i < L2->size; i++)
	{
		ListGet(L2, i, &x);
		ListInsert(L3, x);
	}

	return 1;
}