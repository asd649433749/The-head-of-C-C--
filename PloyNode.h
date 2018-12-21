#include<stdio.h>
#include<malloc.h>

/*���������⼰���������
	��main����������ʹ�õ���PloyNode PN
	���Ƿ����ڲ��뺯��PNInsert�У������µ���Ԫ�ڵ��ǳ��Ѵ���
	�������޸�������ĳ�ʼ�� �����ڳ�ʼ����ʱ��Ų����ڴ�����


*/
//�˴�ʵ�����ѭ������
typedef struct node
{
	float coef;			//ϵ����
	int exp;			//ָ����
	struct node *next;	//ָ����
}PloyNode;

//��ʼ��������,������һ���ڵ㸳ֵ
void PNInitiate(PloyNode **h, float a, int n)
{
	*h= (PloyNode*)malloc(sizeof(PloyNode)); //��ͷָ��ָ��һ��յ��ڴ�������Ϊmain�����е��Ǻ���ָ��
	(*h)->coef = a;
	(*h)->exp = n;
	(*h)->next = *h;//ָ���Լ����һ��ѭ��������
}

//��������Ԫ�أ����������򣬺ϲ�ͬ����
int PNInsert(PloyNode **h, float a, int n)
{
	/*�������룬�ȷ��ţ����Կ�������Ҫ*/
	//while(p->next!=h) p=p->next;
	//p->coef=a;
	//p->exp=n;
	//p->next=(PloyNode*)malloc(sizeof(PloyNode)); //�����µĽڵ㣬����ĩ�ڵ��nextָ���½ڵ�
	//p=p->next ;//ָ��ָ���½ڵ�
	//p->next=h;//���½ڵ��nextָ��ͷ�ڵ㣬ά��ѭ��������

	PloyNode *p = (*h), *p1;
	if (*h == NULL)return 0;

	//ͷ�ڵ�
	if ((*h)->exp>n)//����Ҫ����ͷ�ڵ�λ��
	{
		p1 = (PloyNode*)malloc(sizeof(PloyNode));
		p1->next = (*h);					//�½ڵ�ָ��ԭͷ�ڵ�
		while (p->next != (*h)) p = p->next; //ȡ��β�ڵ�
		p->next = p1;//β�ڵ�ָ���½ڵ㣬���ά��ѭ��������
		(*h) = p1;//���½ڵ��Ϊͷ�ڵ�
			   //��ֵ
		(*h)->coef = a;
		(*h)->exp = n;
		return 1;
	}
	//�˴�Ӧ���ҵ�ָ����>= n��,�����ͷ�ڵ�����Ľڵ�
	while (p->next != (*h) && (p->next->exp<n)) p = p->next;
	if (p->next->exp == n)
	{
		p->next->coef += a; //�ϲ�ͬ����
		return 1;//��ɲ���������Ҫ�����½ڵ㣬���غ�������
	}
	else
	{
		p1 = (PloyNode*)malloc(sizeof(PloyNode));//�������ǵ���β�ڵ㣨�½ڵ�ָ����󣩻����ҵ��˺��ʵ�λ��
		p1->next = p->next;  //�½ڵ�ָ���¸��ڵ�
		p->next = p1;			//ԭ�ڵ�ָ���½ڵ�	//ά����ѭ������
								//��ֵ
		p1->coef = a;
		p1->exp = n;
	}

	return 1;
}

//������Ԫ�صĸ���������-1Ϊ����
int PNlength(PloyNode *h)
{
	PloyNode *p = h;
	int j = 1;
	if (h == NULL)return -1;//������-1�����
	if (h->coef==0.0)return 0;//���ϵ����Ϊ0����ô��Ԫ���ڶ���ʽ�е��ڲ����ڣ���ô�ҿ�����Ϊͷ�ڵ��ǳ�ʼ�����״̬
	while (p->next != h)
	{
		p = p->next;
		j++;//��λ�ִ��һ�ξʹ�����һ��Ԫ�أ�û��ִ�й�Ҳ������ͷ�ڵ�һ��Ԫ��
	}
	return j;
}

//ȡ����Ԫ��(��a��n��������)
int PNGet(PloyNode *h, int i, float *a, int *n)
{
	int j = 0;
	PloyNode *p = h;

	if (h == NULL)return 0;
	if (i<0 || i>PNlength(h))return 0;
	while (j<i)
	{
		p = p->next;
		j++;
	}
	*a = p->coef;
	*n = p->exp;
	return 0;
}

//ɾ��Ԫ��
int PNDelete(PloyNode *h, int i, float *a, int *n)
{
	int j = 0;
	PloyNode *p = h;
	PloyNode * q=p;
	if (h == NULL)return 0;
	if (i<0 || i>PNlength(h))return 0;
	while (j<i)
	{
		q = p;
		p = p->next;
		j++;
	}
	*a = p->coef;
	*n = p->exp;
	q->next = p->next;
	free(p);
	return 1;
}