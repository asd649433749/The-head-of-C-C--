#include<stdio.h>
#include<malloc.h>

/*���������⼰���������


*/
#define DataType char
#define MaxStackSize 20
#define MaxQueueSize 50
//��׺���ʽ��ֵ ��ʽջ�ṹ
typedef struct CTI
{
	DataType node[8];//8λ��ʮ������
	struct CTI * next;

}CharToInt;

//����ջ
typedef struct
{
	DataType stack[MaxStackSize];
	int top;

}Stack;

//��׺���ʽ����
typedef struct
{
	DataType queue[MaxQueueSize];
	int rear;
	int front;
}Queue;

//��ʼ������	ʱ�临�Ӷ�ΪO(1)
void QueueInitiate(Queue *Q)
{
	Q->rear = 0;
	Q->front = 0;
}

//���зǿշ� 	ʱ�临�Ӷ�ΪO(1)
int QueueNotEmpty(Queue Q)
{
	if (Q.rear == Q.front)
		return 0;
	else return 1;
}

//�������	ʱ�临�Ӷ�ΪO(1)
int QueueAppend(Queue *Q, DataType x)
{
	if ((Q->rear + 1) % MaxQueueSize == Q->front)
	{
		printf("�����Ѿ�����");
		return 0;
	}
	else
	{
		Q->queue[Q->rear] = x;
		Q->rear = (Q->rear + 1) % MaxQueueSize;
		return 1;
	}
}

//���г���	ʱ�临�Ӷ�ΪO(1)
int QueueDelete(Queue *Q, DataType *x)
{
	if (Q->rear == Q->front)
	{
		printf("����Ϊ�գ�");
		return 0;
	}
	else
	{
		*x = Q->queue[Q->front];
		Q->front = (Q->front + 1) % MaxQueueSize;
		return 1;
	}
}

//˳��ջ��ʼ��	ʱ�临�Ӷ�ΪO(1)
void StackInitiate(Stack *s)
{
	s->top = 0;
}

//˳��ջ�ǿշ�	ʱ�临�Ӷ�ΪO(1)
int StackNotEmpty(Stack s)
{
	if (s.top <= 0)
		return 0;
	else return 1;
}

//˳��ջ��ջ	ʱ�临�Ӷ�ΪO(1)
int StackPush(Stack *s, DataType x)
{
	if (s->top >= MaxStackSize)
	{
		printf("��ջ�Ѿ����ˣ�\n");
		return 0;
	}
	else
	{
		s->stack[s->top] = x;
		s->top++;
		return 1;
	}
}

//˳��ջ��ջ	ʱ�临�Ӷ�ΪO(1)
int StackPop(Stack *s, DataType *d)
{
	if (s->top <= 0)
	{
		printf("��ջ�ѿ�������Ԫ�أ�\n");
		return 0;
	}
	else
	{
		s->top--;
		*d =s->stack[s->top];
		return 1;
	}
}

//ȡջ������Ԫ�� ʱ�临�Ӷ�ΪO(1)
int StackTop(Stack *s, DataType *d)
{
	if (s->top <= 0)
	{
		printf("��ջ�ѿ�������Ԫ�أ�\n");
		return 0;
	}
	else
	{
		*d = s->stack[s->top-1];
		return 1;
	}
}


//��ͷ�����ʽ��ջ CharToInt
//ͷ����������ĵ�һλ�Ǳ�־λ
//��ʼ��
void CharToIntInitiate(CharToInt **head)
{
	*head = (CharToInt*)malloc(sizeof(CharToInt));
	(*head)->next = NULL;
}

//�ǿշ�
int CharToIntNotEmpty(CharToInt *head)
{
	if (head->next == NULL)return 0;
	else return 1;
}

//�ַ���ת��������
int STI(DataType c[])
{
	int i = 0;
	int x = 0;
	for (i = 0; c[i] != '\0'; i++)
	{
		x = x * 10 + c[i] - '0';
	}
	return x;
}

//����������ջ�в����㣬�����Ϊ������ʽ��
int CharToIntPush(CharToInt *head, DataType x)
{
	CharToInt *p;
	int x1,x2,sum,n,i;
	char c[MaxQueueSize];
	if (head->next == NULL)
	{
		p = (CharToInt *)malloc(sizeof(CharToInt));
		head->node[0] = '1';
		p->node[0] = x;
		p->next = head->next;
		head->next = p;
	}
	else
	{
		if (x >= '0'&&x <= '9')//���������
		{	
			if (head->node[0] != '0')//���ͷ����־λ��0�������µĽڵ�
			{
				head->next->node[(int)(head->node[0] - '0')] = x;
				head->node[0] = head->node[0] + 1;
			}
			else //�µĽڵ�
			{
				p = (CharToInt *)malloc(sizeof(CharToInt));
				head->node[0] = '1';
				p->node[0] = x;
				p->next = head->next;
				head->next = p;
			}
		}
		else if (x == '/' || x == '*' || x == '-' || x == '+' )//��������λ����������
		{
			
			//head->next->node[(int)(head->node[0] - '0')] = '\0';
			head->node[0] = '0';
			x2 = STI(head->next->node);
			x1= STI(head->next->next->node);
			switch (x)
			{
			case'+': {
				sum = x1 + x2; break;
			}
			case'-': {
				sum = x1 - x2; break;
			}
			case '*':{
				sum = x1 * x2; break;
			 }
			case '/': {
				if (x2 == 0)
				{
					printf("����Ϊ0����\n");
					return 0;
				}
				else {
					sum = x1 / x2;
					break;
				}
			}
			default:
				break;
			}
			//switch ������
			p = head->next;
			head->next = p->next->next;//ջ��ָ��ջ����3������
			free(p->next);//�ͷ�ջ��2������
			free(p);
			p = (CharToInt *)malloc(sizeof(CharToInt));

			//������ת���ַ�����Ȼ��Żؽڵ���
			n = sum; i = 0;
			while (n != 0)
			{
				c[i] = n%10+'0';
				n /= 10;
				i++;
			}
			head->node[0] = i  + '0';
			for (i = i - 1,n=0; i >= 0; i--,n++)
			{
				p->node[n] = c[i];
			}
			p->node[n] = '\0';
			//p->node[0] = x;
			p->next = head->next;
			head->next = p;
		}
		else if(x==' ')//���ڿո����Ϊ�����ֿ�������������
		{
			head->next->node[(int)(head->node[0] - '0')] = '\0';
			head->node[0] = '0';

		}
	}
	return 1;
}


//�������һ���ڵ㷵���������ݣ���������������ֻʣһ���ڵ㣩
int CharToIntGetInt(CharToInt *head)
{
	return STI(head->next->node);//������������ֻ��һ���ڵ㣬����ýڵ�
}