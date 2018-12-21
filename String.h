#include<stdio.h>
#include<malloc.h>

/*���������⼰���������


*/
typedef struct
{
	char *str;
	int len;
	int maxlen;
}String;

//�ַ����ĳ�ʼ��
void StringInitiate(String *S, int max, char *s)
{

	S->str = (char*)malloc(sizeof(char)*max);
	S->maxlen = max;
	S->len = strlen(s);
	strcpy(S->str, s);
	printf("��ʼ��ʱ�����%s\n", S->str);

}

//�����ַ���
char* getStr1(String *S)
{
	return S->str;
}

//�ַ����Ĳ��룬��S1��β������S2��ǰn���ַ�
int StringInsert(String*S1, String*S2, int n)
{
	int i;
	if (n<0 || n>S2->maxlen)
	{
		printf("����ʱ���������n���Ϸ�\n");
		return 0;
	}
	else if ((S1->len + n) > S1->maxlen)
	{
		printf("����ʱ��������������̫�࣬�����ݲ���\n");
		return 0;
	}
	for (i = 0; i < n; i++)
	{
		S1->str[S1->len + i] = S2->str[i];
	}
	S1->str[S1->len + i] = '\0';
	S1->len += n;
	printf("����ʱ�����%s\n", S1->str);

}

//�����ַ���3���ַ���1�е�λ�ã�����Ҳ�������A�е�mλ�ò���
//��Ϊ��Ŀ�漰���ַ����������кܶ��ظ��Ӵ�������ʹ�������㷨
int StringSearch(String *S1, String* S3,int m)
{
	int i=0,j=0;
	int flag;

	while (i < S1->len && j<S3->len)
	{
		if (S1->str[i] == S3->str[j])
		{
			i++; j++;
		}
		else
		{
			i = i - j + 1;
			j = 0;
		}
	}
	if (j == S3->len)
	{
		flag = i - j;//�ҵ����Ӵ�
		printf("������������ҵ��Ӵ�λ���ˣ���%d��\n", flag);
		return flag;
	}
	else 
	{
		flag = -1;//û�ҵ�
		if (m<0 || m>S1->maxlen)
		{
			printf("���������������m���Ϸ�\n");
			return -11;//��һ��1��û�ҵ����ڶ���1��ʾ����ʧ��
		}
		else if ((S1->len + m) > S1->maxlen)
		{
			printf("��������������������̫�࣬�����ݲ���\n");
			return -11;
		}
		for (i = S1->len; i >= m; i--) //����iû��-1����ΪҪ��ͬ��\0������Ҳ���ƹ�ȥ
		{
			S1->str[S3->len + i] = S1->str[i];
		}//���������Ʋ���
		for (i = 0; i < S3->len; i++)
		{
			S1->str[m + i] = S3->str[i];
		}
		S1->len += S3->len;
		printf("��������������Ҳ����Ӵ������S1�еĵ�%dλ���У����Ϊ��%s\n",m,S1->str);
		//˳������
		return -12;//��һ��1��û�ҵ����ڶ���2��ʾ˳������
	}

	

}