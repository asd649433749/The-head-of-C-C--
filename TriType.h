#include<stdio.h>
#include<malloc.h>

/*���������⼰���������


*/
#define elemtype int
//��Ԫ��Ԫ��
typedef struct
{
	int i;		//�к�
	int j;		//�к�
	elemtype d;	//Ԫ��ֵ
}DataType;

typedef struct
{
	int id;		//����
	int jd;		//����
	int td;		//����Ԫ�ظ���
}TriType;

//��Ԫ��ĳ�ʼ��
void TriTypeInitiate(TriType *tt,int i,int j)
{
	tt->id = i;
	tt->jd = j;
	tt->td = 0;
}
//�趨����ֵ
int setDataType(TriType *tt, DataType *dt, int i, int j, int d)
{
	if (d != 0) tt->td++;
	if (i > tt->id || j > tt->jd || i < 0 || j < 0)
	{
		printf("�������������\n");
		return 0;
	}
	dt->i = i;
	dt->j = j;
	dt->d = d;
	return 1;
}

//��ӡ����
int printData(TriType tt, DataType dt[])
{
	int n = tt.td;
	int i,j,t;
	int flag=0;

	//�����ȣ���ѭ��
	for (i = 1; i <= tt.id; i++)
	{

		//Ȼ���ٵ��б���
		for (j = 1; j <= tt.jd; j++)
		{
			flag = 0;
			//ѯ����Ԫ���Ƿ񺬸�λԪ��
			for (t = 0; t < n; t++)
			{
				if (dt[t].i == i && dt[t].j == j)
				{
					flag = dt[t].d;
					break;
				}
			}
			printf("%d\t", flag);
		}

		printf("\n");
	}
	return 1;
}

//�������
int addData(TriType Att, DataType Adt[], TriType Btt, DataType Bdt[], TriType* Ctt, DataType(* Cdt)[])
{


	int n1 = Att.td,n2=Btt.td;
	int i, j, t,index=0;
	int flag = 0;
	int id = Att.id, jd = Att.jd;//��ΪAB������������һ���ģ�������A����
	if (Att.id != Btt.id || Att.jd != Btt.jd)
	{
		return 0;//��������һ�����Ͳ������
	}
	Ctt->id = id;
	Ctt->jd = jd;
	Ctt->td = 0;//�����㣬Ȼ�����ÿ����һ�����Զ���1
	//�����ȣ���ѭ��
	for (i = 1; i <= id; i++)
	{

		//Ȼ���ٵ��б���
		for (j = 1; j <= jd; j++)
		{
			flag = 0;
			//ѯ��A�������Ԫ���Ƿ񺬸�λԪ��
			for (t = 0; t < n1; t++)
			{
				if (Adt[t].i == i && Adt[t].j == j)
				{
					flag += Adt[t].d;
					break;
				}
			}
			//ѯ��B�������Ԫ���Ƿ񺬸�λԪ��
			for (t = 0; t < n2; t++)
			{
				if (Bdt[t].i == i && Bdt[t].j == j)
				{
					flag += Bdt[t].d;
					break;
				}
			}

			//printf("%d\t", flag);
			if (flag != 0)
			{
				setDataType(Ctt,&((*Cdt)[index++]),i,j,flag);
			}
		}

		//printf("\n");
	}
}

//����ת��
int Transition(TriType* tt, DataType(*dt)[])
{
	int ij;
	int i, j, d;//����ý��
	int n,flag,t;
	//�������Ʊ�
	ij = tt->id;
	tt->id = tt->jd;
	tt->jd = ij;

	//������
	for (n = 0; n < tt->td; n++)
	{
		flag = 0;
		//ѯ����Ԫ���Ƿ񺬸�λԪ��
		for (t = n; t < tt->td; t++)
		{
			if ((*dt)[t].i == (*dt)[n].j && (*dt)[t].j == (*dt)[n].j)
			{
				flag = (*dt)[t].d;
				(*dt)[t].d = (*dt)[n].d;
				(*dt)[n].d = flag;
				break;
			}
		}
		i = (*dt)[n].i;
		(*dt)[n].i = (*dt)[n].j;
		(*dt)[n].j = i;

	}


	return 1;

}