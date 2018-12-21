#include<stdio.h>
#include<malloc.h>

#define DataType char

//���Ľڵ�ṹ��
typedef struct  Node
{
	DataType data;
	struct Node* leftChild;
	struct Node* rightChild;
}BiTreeNode;
//��ʼ�����ڵ�
void Initiate(BiTreeNode **root,DataType x)
{
	*root = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	(*root)->leftChild = NULL;
	(*root)->rightChild = NULL;
	(*root)->data = x;

}
//�����ڵ�(�ɹ������²���ڵ�ָ�룩
BiTreeNode* InsertLeftNode(BiTreeNode *curr, DataType x)
{
	BiTreeNode *s, *t;
	if (curr == NULL)return NULL;
	t = curr->leftChild;
	s = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	s->data = x;
	s->leftChild = t;
	s->rightChild = NULL;
	curr->leftChild = s;
	return curr->leftChild;
}
//�Ҳ���ڵ�(�ɹ������²���ڵ�ָ��
BiTreeNode* InsertRightNode(BiTreeNode *curr, DataType x)
{
	BiTreeNode *s, *t;
	if (curr == NULL)return NULL;
	t = curr->rightChild;
	s = (BiTreeNode*)malloc(sizeof(BiTreeNode));
	s->data = x;
	s->rightChild = t;
	s->leftChild = NULL;
	curr->rightChild = s;
	return curr->rightChild;
}
//����������
void Destroy(BiTreeNode **root)
{
	if ((*root) != NULL && (*root)->leftChild != NULL)
		Destroy(&(*root)->leftChild);
	if ((*root) != NULL && (*root)->rightChild != NULL)
		Destroy(&(*root)->rightChild);
	free(*root);
}
//��ɾ���ڵ㣨�ɹ�����˫�׽ڵ�
BiTreeNode* DeleteLeftTree(BiTreeNode *curr)
{
	if (curr == NULL || curr->leftChild == NULL)return NULL;
	Destroy(&curr->leftChild);
	curr->leftChild = NULL;
	return curr;
}
//��ɾ���ڵ㣨�ɹ�����˫�׽ڵ�
BiTreeNode* DeleteRightTree(BiTreeNode *curr)
{
	if (curr == NULL || curr->rightChild == NULL)return NULL;
	Destroy(&curr->rightChild);
	curr->rightChild = NULL;
	return curr;
}

//�����ջ�Ķ��壬����Ķ�ջ��Ϊ�˷����������
//Ϊ����������Ķ�ջ�Ľṹ��
typedef struct stack
{
	BiTreeNode* data;
	struct stack *next;
}BiTreeStack;
//��ջ�ĳ�ʼ��
void StackInitiate(BiTreeStack **head)
{
	*head = (BiTreeStack*)malloc(sizeof(BiTreeStack));
	(*head)->next = NULL;
}
//��ջ�ǿշ�
int StackNotEmpty(BiTreeStack *head)
{
	if (head->next == NULL)
		return 0;
	else return 1;
}
//��ջ
void StackPush(BiTreeStack *head, BiTreeNode* x)
{
	BiTreeStack *p;
	p = (BiTreeStack*)malloc(sizeof(BiTreeStack));
	p->data = x;
	p->next = head->next;
	head->next = p;
}
//��ջ
int StackPop(BiTreeStack *head, BiTreeNode **d)
{
	BiTreeStack *p = head->next;
	if (p == NULL)
	{
		printf("��ջ�Ѿ�����");
		return 0;
	}
	head->next = p->next;
	*d = p->data;
	free(p);
	return 1;
}
//ȡջ��Ԫ��
int StackTop(BiTreeStack* head, BiTreeNode **d)
{
	BiTreeStack* p = head->next;
	if (p == NULL)
	{
		printf("��ջ�Ѿ�����");
		return 0;
	}
	*d = p->data;
	return 0;
}
//����������ջ
void StackDestroy(BiTreeStack* head)
{
	BiTreeStack *p, *p1;
	p = head;
	while (p != NULL)
	{
		p1 = p;
		p = p->next;
		free(p1);
	}
}

//�ص�������
//�ڵ����
void Visit(DataType item)
{
	printf("%c ", item);
}
//�ǵݹ鷽ʽ���������
void DLR_not_digui(BiTreeNode *root, void fangwen(DataType item))
{
	BiTreeStack *BTS;
	BiTreeNode *p;
	StackInitiate(&BTS);
	StackPush(BTS, root);
	while (StackNotEmpty(BTS))
	{
		StackPop(BTS, &p);
		fangwen(p->data);
		if (p->rightChild != NULL)
			StackPush(BTS, p->rightChild);
		if (p->leftChild != NULL)
			StackPush(BTS, p->leftChild);
	}

	StackDestroy(BTS);
}

//�ǵݹ鷽ʽ���������
void LDR_not_digui(BiTreeNode *root, void fangwen(DataType item))
{
	BiTreeStack *BTS;
	BiTreeNode *p=root;
	StackInitiate(&BTS);
	//StackPush(BTS, root);
	while (p!=NULL||StackNotEmpty(BTS))
	{
		while (p != NULL)
		{
			StackPush(BTS, p);
			p = p->leftChild;

		}

		if (StackNotEmpty(BTS))
		{
			StackPop(BTS, &p);
			fangwen(p->data);
			p = p->rightChild;
		}
	}
}

//�ݹ�ĺ������
void LRD_digui(BiTreeNode *root, void fangwen(DataType item))
{
	if (root == NULL)return;
	LRD_digui(root->leftChild,fangwen);
	LRD_digui(root->rightChild,fangwen);
	fangwen(root->data);
}


//�����Ƕ��е�Դ�룬����Ϊ�˷����α���
#define MaxQueueSize 25
typedef struct queue
{
	BiTreeNode* queue[MaxQueueSize];
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
int QueueAppend(Queue *Q, BiTreeNode* x)
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
int QueueDelete(Queue *Q, BiTreeNode* *x)
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

//�������Ĳ�α���
void cengci_bianli(BiTreeNode* root, void fangwen(DataType item))
{
	Queue Q;
	BiTreeNode *p=root;

	QueueInitiate(&Q);

	if (root == NULL)
	{
		printf("����Ϊ��\n");
		return;
	}
	QueueAppend(&Q,p);
	while (QueueNotEmpty(Q))
	{
		QueueDelete(&Q, &p);
		fangwen(p->data);
		//��Ϊ�Ƚ��ȳ��������Ƚ����
		if (p->leftChild != NULL)
		{
			QueueAppend(&Q, p->leftChild);
		}
		if (p->rightChild != NULL)
		{
			QueueAppend(&Q, p->rightChild);
		}
	}

}

//����������
int GetTreeDepth(BiTreeNode* root)
{
	int left,right,ret;

	if (root == NULL)
		return 0;
	left = GetTreeDepth(root->leftChild);
	right = GetTreeDepth(root->rightChild);
	ret = (left>right?left:right) + 1;
	return ret;
}

//�޸ĺ����������ʹ����������Ҷ�ڵ��Ҷ�ڵ�
//�ݹ�ĺ������
//����Ҷ�ڵ����
int LRD_Ye_Node_Num(BiTreeNode *root)
{
	int left, right,ret;
	if (root == NULL)return 0;
	//����˽ڵ�ΪҶ�ڵ�
	if (root->leftChild == NULL && root->rightChild == NULL)
	{
		return 1;
	}
	left= LRD_Ye_Node_Num(root->leftChild);
	right= LRD_Ye_Node_Num(root->rightChild);
	ret = left + right;
	return ret;
}
//��ȡ�ܵĽڵ���
int Get_Node_Num(BiTreeNode* root)
{
	int left, right, ret;
	if (root == NULL)
		return 0;

	left = Get_Node_Num(root->leftChild);
	right = Get_Node_Num(root->rightChild);
	ret = left + right + 1;
	return ret;
}

//����ȷ����Ŀ��˼�����Ҷ�ڵ��ֵ�������Ӻ���
//�������������Ҷ�ӽڵ�
void Get_Ye_LRD_digui(BiTreeNode *root, void fangwen(DataType item))
{
	if (root == NULL)return;
	Get_Ye_LRD_digui(root->leftChild, fangwen);
	Get_Ye_LRD_digui(root->rightChild, fangwen);
	//ֻ�е�ΪҶ�ڵ�ʱ�ŷ���
	if(((root->leftChild)==NULL)&&((root->rightChild)==NULL))
	fangwen(root->data);
}
//��Ҷ�ڵ�����
void Get_NotYe_LRD_digui(BiTreeNode *root, void fangwen(DataType item))
{
	if (root == NULL)return;
	Get_NotYe_LRD_digui(root->leftChild, fangwen);
	Get_NotYe_LRD_digui(root->rightChild, fangwen);
	//ֻ�е�Ϊ��Ҷ�ڵ�ʱ�ŷ���
	if ((root->leftChild) != NULL || (root->rightChild) != NULL)
		fangwen(root->data);
}