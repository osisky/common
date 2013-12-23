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
		b[i] = x[i];
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
			double mul = get_value_fspar(s,j,i) / diag;		//�õ�����mul
			b[j] -= mul * b[i];								//�Գ���������б任
			unfspar_row(ftemp,s,j,n);						//��ϡ������j�н���չ��������0���ŵ�ftemp������
			add_mulrow_fspar(s,ftemp,i,-mul);
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
		b[i] = x[i];
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
	s[irow].n = 0;
	for(long i = 0; i < n; i++)			//��v�еķ�0Ԫ�طŵ�s��irow��
	{
		if(fabs(v[i]) > SMLL)
		{
			s[irow].n++;
			s[irow].value[s[irow].n - 1] = v[i];
			s[irow].index[s[irow].n - 1] = i;
		}
	}

	return;
}

//���ܣ����¶�ϡ������irow�н��з���ռ䣬��СΪn,�����滻irow�е�ʱ�����
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


//���ܣ���ϡ�����s��irow�����·����ڴ棬��СΪceil10(s[i].n)��ceil10��˼Ϊ���ڻ����ȡ������ceil(0��9) = 10 ceil(10��19) = 20;
//		ֻҪs[irow].n�����˸ı䣬�ͼ��ռ��Ƿ��㹻�������Ļ���irow���·����ڴ�;
void re_mem_fspar(FSPAR *s,long irow)
{
	long nmax = ceil10(s[irow].n);					//ceil10��˼Ϊ���ڻ����ȡ������ceil(0��9) = 10 ceil(10��19) = 20;
	if(nmax != s[irow].nmax)
	{
		s[irow].index = (long *)realloc(s[irow].index,nmax * sizeof(long));			//���·���ռ�
		s[irow].value = (double *)realloc(s[irow].value,nmax * sizeof(double));
		if(s[irow].index == NULL)
		{
			printf("\n Error: - %s %d",__FILE__,__LINE__);
			exit(0);
		}
		if(s[irow].value == NULL)
		{
			printf("\n Error: - %s %d",__FILE__,__LINE__);
			exit(0);
		}
		s[irow].nmax = nmax;														//���¶������ռ�
	}

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
		if(fabs(v[i]) > SMLL)
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

//���ܣ��Ӿ���a�У��õ�index�дӶԽ���Ԫ�ؿ�ʼ���������ֵ���к�,
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
//���ܣ��ӳ���Ϊn���������ҵ�����ֵ���������±�
//������x - ����������
//		n - ���鳤��
long pos_absmax_vector(double *x,long n)
{
	long index = 0;
	double tempv = fabs(x[index]);
	for(long i = 1; i < n; i++)
	{
		if(fabs(x[i]) > tempv)
		{
			index = i;
		}
	}

	return index;
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
		s->top = s->low + s->spacksize;
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
		s[i].index = NULL;		//��ʼ��
		s[i].value = NULL;
		s[i].nmax = 0;
		s[i].n = 0;
	}

	return;
}

//���ܣ���ϡ������i��j��Ԫ�����ó�x
//������s - ϡ�����
//		x - �����õ�ֵ
//		i - ���±�
//		j - ���±�
void set_value_fspar(FSPAR *s,double x,long i,long j)
{
	if(fabs(x) < SMLL)				//�����ϡ������Ԫ����0�����൱��ɾ�����Ԫ��
	{
		dele_element_fspar(s,i,j);
		return;
	}
	long vi = lookup(s,i,j);
	if(vi == NO)				   //�����ԭϡ�������û�и�Ԫ�أ����൱������Ԫ��
	{
		s[i].n++;
		re_mem_fspar(s,i);         //ÿ������Ԫ�ص����ж����鳤�ȹ�����������Ԫ�أ����ж�Ԫ�ظ������ٺ󣬸������������Ƿ�仯���Ǹ�λ��������ʮλ������������������仯�������·���ռ�
		s[i].value[s[i].n -1] = x; //ע�������-1
		s[i].index[s[i].n -1] = j;
	}
	else
	{
		s[i].value[vi] = x;
	}

	return;
}

//���ܣ�ɾ��ϡ�����s��һ��Ԫ��,�����ϡ������Ԫ����0�����൱�ڰ����Ԫ��ɾ��
//������s - ϡ�����
//		irow - irow���±�
//		icol - icol���±�
void dele_element_fspar(FSPAR *s,long irow,long icol)
{
	long vi = lookup(s,irow,icol);                         //�ҵ�icol����index��λ��
	if(vi == NO)
	{
		printf("\nError: - %s %d",__FILE__,__LINE__);
		exit(0);
	}
	else
	{
		dele_ielement_vector(s[irow].index,vi,s[irow].n);	//ɾ��vi�±��Ԫ��
		dele_felement_vector(s[irow].value,vi,s[irow].n);	
		s[irow].n--;										//����-1
		re_mem_fspar(s,irow);								//���ȱ仯���ڴ�ռ�ҲҪ�仯
	}

	return;
}

//���ܣ��ڳ���Ϊn��������ɾ��indexԪ��
//������v - ����
//		index - ��ɾ��Ԫ�ص��±�
//		n - ���鳤��
void dele_felement_vector(double *v,long index,long n)
{
	for(long i = index; i < n - 1; i++)
	{
		v[index] = v[index + 1];
	}

	return;
}

void dele_ielement_vector(long *v,long index,long n)
{
	for(long i = index; i < n - 1; i++)
	{
		v[index] = v[index + 1];
	}

	return;
}


//���ܣ���ϡ�����s�в���irow�к�icol�е�Ԫ����value���±�vi
long lookup(FSPAR *s,long irow,long icol)
{
	long vi = NO;
	for(long i = 0; i < s[irow].n; i++)
	{
		if(s[irow].index[i] == icol)
			vi = i;
	}
	return vi;
}

//���ܣ��ڳ���Ϊn�������У��ҵ���ֵΪicol��Ԫ���±�
long lookup(long *v,long icol,long n)
{
	long vi = NO;

	for(long i = 0; i <n; i++)
	{
		if(v[i] == icol)
			vi = i;
	}
	return vi;
}

//���ܣ���x�ӵ�ϡ�����s��irow��icol��
//������s - ϡ�����
//		x - ����ֵ
//		irow - �������±�
//		icol - �������±�
void add_value_fspar(FSPAR *s,double x,long irow,long icol)
{
	double dtemp = get_value_fspar(s,irow,icol);	
	set_value_fspar(s,dtemp + x,irow,icol);

	return;
}
void printfs(FSPAR *s)
{
	printf("\n");
	for(long i = 0; i < 3; i++)
	{
		for(long j = 0; j < 3; j++)
			printf("%lf ",s[i].value[j]);
		printf("\n");

	}
	return;
}

//���ܣ���Ŀ�괮strdest�У�����Դ�ַ���strsrc�Ƿ������У�����strstr
//���أ�����������򷵻�NULL�������򷵻س��ֵ���ʼָ��
char *bf(char *strdest,char *strsrc)
{
	char *srcret = NULL;
	long len_dest = strlen(strdest);
	long len_src = strlen(strsrc);
	if(!len_src)	return srcret;

	for(long i = 0; i <= len_dest - len_src; i++)
	{
		long cur_len_src = 0;
		char *strsrc_ = strsrc;
		char *strdest_ = strdest + i;
		char *curstrdest = strdest + i;
		while(*strsrc_++ == *strdest_++)
		{
			cur_len_src++;
			if(*strsrc_ == '\0' || *strsrc_ == '\0')
				break;
		}
		if(cur_len_src == len_src)
		{
			srcret = curstrdest;
			break;
		}
	}

	return srcret;
}

void add_vector(double *x,double *y,long n)
{
	for(long i =0; i < n; i++)
		x[i] += y[i];
}

void newton_powerflow(double *x,long n)
{
	FSPAR *J  = NULL;
	makefspar(J,2);
	double max_eps;
	do 
	{
		double J11 = 4 * x[0];
		double J12 = 1;
		double J21 = 2 * x[0];
		double J22 = 2 * x[1];
		set_value_fspar(J,J11,0,0);
		set_value_fspar(J,J12,0,1);
		set_value_fspar(J,J21,1,0);
		set_value_fspar(J,J22,1,1);
		double *b = NULL;
		b = (double *)calloc(2 ,sizeof(double));
		double *y = NULL;
		y = (double *)calloc(2 ,sizeof(double));
		b[0] = 4 - 2 * x[0] * x[0] - x[1];
		b[1] = 5 - x[0] * x[0] - x[1] * x[1];
		gauss(y,J,b,n);
		add_vector(x,y,n);
		max_eps = y[pos_absmax_vector(y,n)];				
	} 
	while (max_eps > powerflow_eps);

	return;
}


