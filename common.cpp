/*********************************************************
Description: my common
Author: xiubin
Company: OSI
Date: 2013-12-09
*********************************************************/
#include "common.h"

/*******************************************�������㷨***********************************************/
//���ܣ�ð�������С����
//����a������������
//����n�����鳤��
void sort_bub(long *a,long n)
{
	long i,j,t;
	for(i = n - 1; i > 0; i--) //����������һ��λ�ÿ�ʼ��ÿ��ѭ�����������ŵ���λ��
	{
		for(j = 0; j < i; j++) 
		{
			if(a[j] > a[j+1])
			{
				t = a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}

	return;
} 

//���ܣ��ҵ�������a�ֳ�С�ʹ������ֵļ�ֵ���±꣬����-С��ֵ key ����ֵ����ʱ��С��ֵ���ֲ�һ���ǰ�С����������ֻ�Ǳ�keyֵС�Ĳ���
//����a������������
//����low����С��ֵ�±�
//����hight�������ֵ�±�
long quick_sort_key(long *a,long low,long hight)
{
	if(low > hight)	return -1;
	if(low == hight)	return low;
	long key = a[low];
	
	while(low < hight)
	{
		while(low < hight && a[hight] >= key)   //�����������ҵ�С��key��ֵ���±�
			hight--;
		if(low < hight)
		{
			a[low] = a[hight];                
			low++;
		}
		
		while(low < hight && a[low] < key)      //������ǰ����ҵ�����keyֵ���±�
			low++;
		if(low < hight)
		{
			a[hight] = a[low];
			hight--;	
		}
	}
	a[low] = key;
	
	return low;
}


//���ܣ���������-��С����
//����a������������
//����low����С�������±�
//����hight�����������±�
void sort_quick(long *a,long low,long hight) //���÷���˼��
{
	long p;
	if(low < hight)
	{
		p = quick_sort_key(a,low,hight); //�ҵ�������a�ֳ�С�ʹ������ֵļ�ֵ���±꣬���磺С��ֵ���� < key < ����ֵ����
		sort_quick(a,low,p-1);           //С��ֵ���ּ����ֽ�
		sort_quick(a,p+1,hight);         //����ֵ���ּ����ֽ�
	}
	
	return;
}

//���ܣ��۰���ң����Ѿ��������������в���
//���أ��±�+1
//������a   - ˳������
//	    len - ���鳤��
//		x   - �����ҵ�����
long find_half(long *a,long len,double x)
{

	long low = 1;        
	long hight = len;
	long mid = (low + len) / 2;   //���ȵõ�������м�λ��
	for(long i= 0;i<len;i++)
	{
		if(a[mid] > x)         
		{  
			hight  = mid  - 1;   //��������м��ֵ�ȴ��������ݴ���Ѳ���������������ó� mid - 1
			mid = (low + hight) / 2;
		}
		else if(a[mid] < x)
		{
			low = mid  + 1;
			mid = (low + hight) / 2;
		}
		else
		{
			return mid;
		}
	}
	
	return -1 ;
	
}
/*******************************************�������㷨***********************************************/

//���ܣ���˹��ȥ�������Է����飬�÷���ֻ�ܽⷽ���� = δ֪����Ҳ����aΪ���Ⱦ���
//���أ�-1Ϊ�޽⣬0Ϊ���ɹ�
//������x - ����δ֪��
//      a - ϵ������
//		b - ����������
//		n - ������/������л���
long gauss(double *x,double **a,double *b,long n)   
{
	for(long i = 0; i < n-1; i++)					 //������ȥ���õ������Ǿ���
	{
		long max_row = pos_max_row_index(a,i,n);	 //�õ�i������ֵ����Ԫ�����ڵ��к�
		if(max_row < SMLL)	
		{
			printf("\nError: - %s %d",__FILE__,__LINE__);
			exit(0);
		}
		swap_row(a,i,max_row,n);					 //����i�к�max_row��
		swap_vector(b,i,max_row,n);					 //��Ӧ�ĳ���Ҳͬʱ����
		for(long j = i + 1; j < n; j++)
		{
			if(fabs(a[j][i]) < SMLL)	continue;	 //���Ԫ��Ϊ0��˵���÷�����һ��δ֪������Ӱ��
			double mul = a[j][i] / a[i][i];		     //�õ����г����б任�ĳ���
			b[j] -= mul * b[i];						 //���ȶ���Ӧ�ĳ������б任
			add_mulrow(a,-mul,j,i,n);				 //��ϵ����������б任
		}
	}
	for(long i = n-1; i >=0; i--)
	{
		
	}



	return 0;
}

//���ܣ��Ӿ���a�У��õ�index��������ֵ���к�
//���أ�-1Ϊ�������������±�,
//������a - �����Ҿ���
//		n - ���鳤��
//		index - �������������index�������к�
long pos_max_row_index(double **a,long index,long n)
{
	if(index > n)	return -1;
	double max_dtemp = fabs(a[index][index]);
	long max_index = index;
	for(long i = index; i < n; i++)
	{
		if(fabs(a[i][index]) > max_dtemp)
		{
			max_dtemp = a[i][index];
			max_index = i;
		}
	}

	return max_index;
}

///���ܣ���������a��i�к�j�У�i��jΪ�±�
//������a - ����
//		i - ����������i
//		j - ����������j
//		n - ����Ľ���
void swap_row(double **a,long i,long j,long n)
{
	double temp;
	if(i == j)	return;
	for(long k = 0; k < n; k++)
	{
		temp = a[i][k];
		a[i][k] = a[j][k];
		a[j][k] = temp;
	}

	return;
}
//���ܣ���������i��jԪ�أ�
//������i - iԪ��
//		j - jԪ��
//		n - ����n��Ԫ�ظ���
void swap_vector(double *a,long i,long j,long n)
{
	if(i = j)	return;
	if(i > n || j > n)	
	{
		printf("\nError: - %s %d",__FILE__,__LINE__);
	}
	double dtemp;
	dtemp = a[i];
	a[i] = a[j];
	a[j] = dtemp;

	return;
}

//���ܣ���j�е�Ԫ�س���mul�ӵ�i��
//������a - ����
//		mul - ����
//		i - Ŀ����
//		j - �ͳ��������
//		n - �������
void add_mulrow(double **a,double mul,long i,long j,long n)
{
	for(long k = 0; k < n; k++)
	{
		a[i][k] += mul * a[j][k];
	}

	return;
}