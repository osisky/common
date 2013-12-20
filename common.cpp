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

//���ܣ���˹��ȥ�������Է����飬�÷���ֻ�ܽⷽ���� = δ֪����Ҳ����aΪ���Ⱦ��󣬲�����������ʽ����Ϊ��������洢��ʽ�����ÿ���ϡ����
//���أ�-1Ϊ�޽⣬0Ϊ���ɹ�
//������x - ����δ֪��
//      a - ϵ������
//		b - ����������
//		n - ������/������л���
long gauss(double *x,double **a,double *b,long n)   
{
	for(long i = 0; i < n-1; i++)					 //������ȥ���õ������Ǿ���U,
	{
		long max_row = pos_max_row(a,i,n);			//�õ�i������ֵ����Ԫ�����ڵ��к�
		if(max_row < SMLL)	
		{
			printf("\nError: - %s %d",__FILE__,__LINE__);
			exit(0);
		}
		swap_row(a,i,max_row,n);					 //����i�к�max_row�� ȷ�����Խ���Ԫ�ص�ֵΪ����,��Ϊ��������洢��ʽ�����ÿ���ϡ����
		swap_vector(b,i,max_row,n);					 //��Ӧ�ĳ���Ҳͬʱ����
		for(long j = i + 1; j < n; j++)
		{
			if(fabs(a[j][i]) < SMLL)	continue;	 //���Ԫ��Ϊ0��˵���÷�����һ��δ֪������Ӱ��
			double mul = a[j][i] / a[i][i];		     //�õ����г����б任�ĳ���
			b[j] -= mul * b[i];						 //���ȶ���Ӧ�ĳ������б任
			add_mulrow(a,-mul,j,i,n);				 //��ϵ��������г����б任-������ӣ�mul�ǳ��ӵ���˼
		}
	}
	for(long i = n - 1; i >= 0; i--)				 //���лش�
	{
		double dsum = 0;
		for(long j = n - 1; j > i; j--)          //jҪ���ڶԽ��ߵĺ�
		{
			dsum += a[i][j] * x[j];				 //ע��x��Ԫ�غ�a��Ԫ���к���ͬ 
		}
		x[i] = (b[i] - dsum) / a[i][i];
	}  

	return 0;
}

//���ܣ���˹��ȥ�������Է����飬�÷���ֻ�ܽⷽ���� = δ֪����Ҳ����aΪ���Ⱦ��󣬲���ϡ��������ڲ���ϡ��������Բ��ܳ��ȱ任���ƻ������ϡ����
//���أ�-1Ϊ�޽⣬0Ϊ���ɹ�
//������x - ����δ֪��
//      s - ϵ������(����ϡ�����Ĵ洢��ʽ)
//		b - ����������
//		n - ������/������л���
//PS:	���ڵ���ϵͳ������ϡ����󣬶Խ���Ԫ��һ�㲻Ϊ0
long gauss(double *x,FSPAR *s,double *b,long n)
{
	for(long i = 0; i < n - 1; i++)								//ѭ���������ǣ�������ȥ
	{
		double *ftemp = (double *)calloc(n,sizeof(double));		//���ڴ��ϡ�����չ������
		if(ftemp == NULL)
		{
			printf("\nError: - %s %d",__FILE__,__LINE__);
			exit(0);
		}
		double diag = get_value_fspar(s,i,i);				//�õ����Խ���Ԫ�ص�ֵ
		if(fabs(diag) < SMLL)
		{
			printf("\nError: - %s %d",__FILE__,__LINE__);
			printf("\n���Խ���Ԫ��Ϊ��");
			exit(0);
		}
		for(long j = i + 1; j < n; j++)						//�ӶԽ���Ԫ����һ��Ԫ�ؿ�ʼ��ȥ
		{
			if(fabs(get_value_fspar(s,j,i)) < SMLL)	
				continue;
			double mul = diag / get_value_fspar(s,j,i);		//�õ�����mul
			b[j] -= mul * b[j];								//�Գ���������б任
			unfspar_row(ftemp,s,j,n);						//��ϡ������j�н���չ��������0���ŵ�ftemp������
			add_mulrow_fspar(s,ftemp,j,-mul);
			fsparfun(s,ftemp,j,n);							//������ftemp����ѹ����ȥ��0Ԫ�أ����滻��ϡ�����s��irow��
		}	
	}
/************************************************************************************************************************
	���µĴ�����Ȼ��ȷ�����Ǻ�2
	for(long i = n - 1; i >= 0; i--)						//���лش�,�����һ�п�ʼ
	{
		double sum = 0;
		for(long j = n - 1; j > i; j--)						//0Ԫ��Ҳ�����˼���
		{
			sum += get_value_fspar(s,i,j) * x[j];
		}
		x[i] = (b[i] - sum) / get_value_fspar(s,i,i);
	}
*************************************************************************************************************************/
// ����������
	for(long i = n - 1; i >= 0; i--)
	{
		double sum = 0;
		for(long j = 0; j < s[i].n; j++)					//ֻ�����0Ԫ��
		{
			double dsum = s[i].value[j];
			long iindex = s[i].index[j];
			if(iindex > i)
				sum += dsum * x[iindex];
		}
		x[i] = (b[i] - sum) / get_value_fspar(s,i,i);
	}

	return 0;
}

//���ܣ�������v����ѹ����ȥ��0Ԫ�أ����滻��ϡ�����s��irow��
//������s - ϡ�����
//		v - ��ѹ��������
//		irow - Ҫ���滻�����±�
//		n - ���鳤��
void fsparfun(FSPAR *s,double *v,long irow,long n)
{	
	long nmax = stat_nozero(v,n);		//ͳ��v�еķ�0Ԫ����
	re_mem_fspar(s,irow,nmax);			//��s�е�irow�����·���ռ�
	for(long i = 0; i < n; i++)			//��v�еķ�0Ԫ�طŵ�s��irow��
	{
		if(fabs(v[i]) > SMLL)
		{
			s[irow].n++;
			s[irow].value[s[irow].n] = v[i];
			s[irow].index[s[irow].n] = i;
		}
	}

	return;
}

//���ܣ����¶�ϡ������irow�н��з���ռ䣬��СΪn
//������s - ϡ�����
//		irow - Ҫ���·������
//		nmax - Ҫ��������ռ�
void re_mem_fspar(FSPAR *s,long irow,long nmax)
{
	s[irow].value = (double *)realloc(s[irow].value,nmax * sizeof(double));
	s[irow].index = (long *)realloc(s[irow].index,nmax * sizeof(long));
	if(s[irow].value == NULL)
	{
		printf("\nError: - %f %d",__FILE__,__LINE__);
		exit(0);
	}
	if(s[irow].index == NULL)
	{
		printf("\nError: - %f %d",__FILE__,__LINE__);
		exit(0);
	}
	s[irow].nmax = nmax;

	return;
}

//���ܣ�ͳ�Ƴ���Ϊn������v���ж��ٸ���0Ԫ��
//������v - ��ͳ�Ƶ�����
//		n - ���鳤��
long stat_nozero(double *v,long n)
{
	long itemp = 0;
	for(long i = 0; i < n; i++)
	{
		if(fabs(v[i]) < SMLL)
			itemp++;
	}

	return itemp;
}

//���ܣ���ϡ�����S��irow�н���չ��������0�����ŵ�v������,Ŀ����Ϊ��irow�н��м���
//������v - չ���������
//		s - ϡ�����
//		irow  - irow��
//		n - ����Ľ���
void unfspar_row(double *v,FSPAR *s,long irow,long n)
{
	initfvector(v,n);
	for(long i = 0; i < s[irow].n; i++)
	{
		double dtemp = s[irow].value[i];
		long dcol = s[irow].index[i];
		v[dcol] = dtemp;
	}

	return;
}

//���ܣ���ʼ������v������Ϊn
//������n - ���鳤��
void initfvector(double *v,long n)
{
	for(long i = 0; i < n; i++)
	{
		v[i] = (double)0;
	}

	return;
}

//���ܣ�ϡ������irow��Ԫ�س���mul��ӵ�����Ϊn������v
//������s - ϡ�����
//		v - ���ӵ�����
//		irow - ϡ�����sҪ�ӵ���
//		mul - ����
void add_mulrow_fspar(FSPAR *s,double *v,long irow,double mul)
{
	for(long i = 0; i < s[irow].n; i++)
	{
		long iindex = s[irow].index[i];
		double fvalue = s[irow].value[i];
		v[iindex] += fvalue * mul;
	}

	return;
}

//���ܣ��Ӿ���a�У��õ�index��������ֵ���к�
//���أ�-1Ϊ�������������±�,
//������a - �����Ҿ���
//		n - ���鳤��
//		index - �������������index�������к�
long pos_max_row(double **a,long index,long n)
{
	if(index > n)	return -1;
	double max_dtemp = fabs(a[index][index]);
	long max_index = index;
	for(long i = index; i < n; i++)
	{
		if(fabs(a[i][index]) > max_dtemp)
		{
			max_dtemp = fabs(a[i][index]);
			max_index = i;
		}
	}

	return max_index;
}

//���ܣ���ϡ������еõ�index�������Ԫ�ص��к�
//���أ�index�������Ԫ�ص��к�
//������s - ϡ�����
//		index - �������
//		n - ����Ľ���
long pos_max_row_fspar(FSPAR *s,long index,long n)
{
	long max_row = index;						//ѭ��ǰ�öԽ���Ԫ��Ϊ���ֵ
	double max_dtemp = get_value_fspar(s,index,index); 
	for(long i = index + 1; i < n; i++)			//�ӶԽ���Ԫ�ؿ�ʼ����
	{
		if(get_value_fspar(s,i,index) > max_dtemp)
			max_row = i;
	}

	return max_row;
}

//���ܣ���ϡ�����s�еõ�i��j��Ԫ��
//���أ�0 -- i��j��Ԫ��Ϊ��Ԫ��
//		����ֵ -- �õ�i��j�е�Ԫ�ص�ֵ
//������s - ϡ�����
//		i - i��
//		j - j��
double get_value_fspar(FSPAR *s,long i,long j)
{
	for(long k = 0; k < s[i].n; k++)
	{
		if(s[i].index[k] == j)
			return s[i].value[k];	
	}

	return 0;
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
	if(i == j)	return;
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

//���ܣ���ʼ��һ��ջ
//������s - ջ
//		stack_size - ջ�Ĵ�С
void init_stack(STACK *s,long stack_size)
{
	s->low = (double *)calloc(stack_size,sizeof(double));
	if(s->low == NULL)
	{
		printf("\nError: - %s %d",__FILE__,__LINE__);
		exit(0);
	}
	s->top = s->low;
	s->spacksize = stack_size;
	
	return;
}

//���ܣ�ѹջ
//������s - ջ
//		x - ��ѹ�������
void push_stack(STACK *s, double x)
{
	if((s->top - s->low) == s->spacksize)
	{
		s->low = (double *)realloc(s->low,(s->spacksize + increase_stack) * sizeof(double));
		if(s->low == NULL)
		{
			printf("\nError: - %s %d",__FILE__,__LINE__);
			exit(0);
		}
		s->top = s->low + increase_stack;
		s->spacksize = s->spacksize + increase_stack;
	}
	*(s->top) = x;
	s->top++;

	return;
}

//���ܣ���ջ
//������s - ջ
//		x - ��ջ��Ԫ��
void pop_stack(STACK *s, double *x)
{
	if(s->top == s->low)
	{
		printf("\nError: - %s %d",__FILE__,__LINE__);
		exit(0);
	}
	s->top--;
	*x = *(s->top);

	return;
}

//���ܣ���ʼ��һ������
//������q - ����
void init_queue(Linkqueue *q)
{
	q = (Linkqueue *)calloc(1,sizeof(Linkqueue));
	if(q == NULL)
	{
		printf("\nError: - %s %d",__FILE__,__LINE__);
		exit(0);
	}
	q->qfront = q->qback;
	q->qfront->next = NULL;

	return;
}

//���ܣ�����β����Ԫ��
//������q - ����
//������x - ������Ԫ��
void insert_queue(Linkqueue *q, double x)
{
	Qnode qtemp;
	qtemp = (Qnode )calloc(1,sizeof(Qnode));
	if(qtemp == NULL)
	{
		printf("\nError: - %s %d",__FILE__,__LINE__);
		exit(0);
	}
	qtemp->data = x;
	qtemp->next = NULL;
	q->qback->next = qtemp;
	q->qback = qtemp;

	return;
}

//���ܣ�ɾ����ͷԪ��
//������q - ����
//		x - ɾ����Ԫ�ط���x��
void delete_queue(Linkqueue *q,double *x)
{
	Qnode qtemp;
	if(q->qback == q->qfront)
		return;
	qtemp = q->qfront->next;
	*x = qtemp->data;
	q->qfront->next = qtemp->next;
	if(q->qback == qtemp)
		q->qback = q->qfront;
	free(qtemp);

	return;
}

//���ܣ����ٶ���
//������q - �����ٵĶ���
void destory_queue(Linkqueue *q)
{
	while(q->qfront)
	{
		q->qback = q->qfront->next; //���ȼ���qfront��next�ڵ�
		free(q->qfront);			//�ͷ�qfront
		q->qfront = q->qback;
	}

	return;
}

//���ܣ�쳲���������
long fib(int a)
{
	if(a < 2)
		return a==0 ? 0 : 1;
	
	return fib(a-1) + fib(a-2);
}

//���ܣ�����һ��n�׸��������ݵ�ϡ����󣬲���ʼ��
//		�þ����д洢����֮�����������͵�˳��ṹ
//������s - ��������ϡ�����
//		n - ����Ľ���
void makefspar(FSPAR *&s,long n)  //�������ô���
{
	s = (FSPAR *)calloc(n,sizeof(FSPAR));
	if(s == NULL)
	{
		printf("\nError: - %f %d",__FILE__,__LINE__);
		exit(0);
	}
	for(long i = 0; i < n; i++)
	{
		s->index = NULL;		//��ʼ��
		s->value = NULL;
		s->nmax = 0;
		s->n = 0;
	}

	return;
}
