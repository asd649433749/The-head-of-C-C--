#include<stdio.h>
#include<malloc.h>

/*���������⼰���������


*/
//�˴�ʵ�����˳��ѭ�����У�����һ���洢��λ��
#define MaxSize 10//��������9����ĸ����һ������10λ
typedef char DataType;
typedef struct 
{
	DataType queue[MaxSize];
	int rear;					//��β
	int front;					//��ͷ
}Queue;



//��ʼ������
void QueueInitiate(Queue *Q)
{
	Q->rear = 0;
	Q->front = 0;

}

//���
int QueueAppend(Queue *Q, DataType x)
{
	if ((Q->rear + 1 )% MaxSize == Q->front)
	{
		printf("�����Ѿ�����");
		return 0;
	}
	else
	{
		Q->queue[Q->rear] = x;
		Q->rear = (Q->rear + 1) % MaxSize;
		return 1;
	}
}

//����
int QueueDelete(Queue *Q, DataType *x)
{
	if (Q->rear == Q->front)
	{
		printf("����Ϊ�գ�");
		return 0;
	}
	else
	{
		*x=Q->queue[Q->front];
		Q->front = (Q->front + 1) % MaxSize;
		return 1;
	}
}
