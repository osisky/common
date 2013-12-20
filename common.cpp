/*********************************************************
Description: my common
Author: xiubin
Company: OSI
Date: 2013-12-09
*********************************************************/
#include "common.h"

/*******************************************↓排序算法***********************************************/
//功能：冒泡排序从小到大
//参数a：待排序数组
//参数n：数组长度
void sort_bub(long *a,long n)
{
	long i,j,t;
	for(i = n - 1; i > 0; i--) //从数组的最后一个位置开始，每次循环把最大的数放到该位置
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

//功能：找到把数组a分成小和大两部分的键值的下标，例如-小数值 key 大数值。这时候小数值部分不一定是按小到大排序，它只是比key值小的部分
//参数a：待排序数组
//参数low：最小数值下标
//参数hight：最大数值下标
long quick_sort_key(long *a,long low,long hight)
{
	if(low > hight)	return -1;
	if(low == hight)	return low;
	long key = a[low];
	
	while(low < hight)
	{
		while(low < hight && a[hight] >= key)   //从数组后面查找到小于key的值的下标
			hight--;
		if(low < hight)
		{
			a[low] = a[hight];                
			low++;
		}
		
		while(low < hight && a[low] < key)      //从数组前面查找到大于key值的下标
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


//功能：快速排序-从小到大
//参数a：待排序数组
//参数low：最小的数组下标
//参数hight：最大的数组下标
void sort_quick(long *a,long low,long hight) //采用分治思想
{
	long p;
	if(low < hight)
	{
		p = quick_sort_key(a,low,hight); //找到把数组a分成小和大两部分的键值的下标，例如：小数值部分 < key < 大数值部分
		sort_quick(a,low,p-1);           //小数值部分继续分解
		sort_quick(a,p+1,hight);         //大数值部分继续分解
	}
	
	return;
}

//功能：折半查找，对已经排序过的数组进行查找
//返回：下标+1
//参数：a   - 顺序数组
//	    len - 数组长度
//		x   - 待查找的数据
long find_half(long *a,long len,double x)
{

	long low = 1;        
	long hight = len;
	long mid = (low + len) / 2;   //首先得到数组的中间位置
	for(long i= 0;i<len;i++)
	{
		if(a[mid] > x)         
		{  
			hight  = mid  - 1;   //如果数组中间的值比待查找数据大，则把查找区间的上限设置成 mid - 1
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
/*******************************************↑排序算法***********************************************/

//功能：高斯消去法解线性方程组，该方法只能解方程数 = 未知数，也就是a为满秩矩阵，采用满矩阵形式，因为是满矩阵存储形式，不用考虑稀疏性
//返回：-1为无解，0为求解成功
//参数：x - 求解的未知量
//      a - 系数矩阵
//		b - 常数列向量
//		n - 方程数/矩阵的行或列
long gauss(double *x,double **a,double *b,long n)   
{
	for(long i = 0; i < n-1; i++)					 //按列消去，得到上三角矩阵U,
	{
		long max_row = pos_max_row(a,i,n);			//得到i列中数值最大的元素所在的行号
		if(max_row < SMLL)	
		{
			printf("\nError: - %s %d",__FILE__,__LINE__);
			exit(0);
		}
		swap_row(a,i,max_row,n);					 //交换i行和max_row行 确保主对角线元素的值为大数,因为是满矩阵存储形式，不用考虑稀疏性
		swap_vector(b,i,max_row,n);					 //相应的常量也同时交换
		for(long j = i + 1; j < n; j++)
		{
			if(fabs(a[j][i]) < SMLL)	continue;	 //如果元素为0，说明该方程少一个未知量，不影响
			double mul = a[j][i] / a[i][i];		     //得到进行初等行变换的乘子
			b[j] -= mul * b[i];						 //首先对相应的常量进行变换
			add_mulrow(a,-mul,j,i,n);				 //对系数矩阵进行初等行变换-两行相加，mul是乘子的意思
		}
	}
	for(long i = n - 1; i >= 0; i--)				 //按行回带
	{
		double dsum = 0;
		for(long j = n - 1; j > i; j--)          //j要大于对角线的号
		{
			dsum += a[i][j] * x[j];				 //注意x的元素和a的元素列号相同 
		}
		x[i] = (b[i] - dsum) / a[i][i];
	}  

	return 0;
}

//功能：高斯消去法解线性方程组，该方法只能解方程数 = 未知数，也就是a为满秩矩阵，采用稀疏矩阵，由于采用稀疏矩阵，所以不能初等变换，破坏矩阵的稀疏性
//返回：-1为无解，0为求解成功
//参数：x - 求解的未知量
//      s - 系数矩阵(采用稀疏矩阵的存储方式)
//		b - 常数列向量
//		n - 方程数/矩阵的行或列
//PS:	对于电力系统分析的稀疏矩阵，对角线元素一般不为0
long gauss(double *x,FSPAR *s,double *b,long n)
{
	for(long i = 0; i < n - 1; i++)								//循环的作用是：按列消去
	{
		double *ftemp = (double *)calloc(n,sizeof(double));		//用于存放稀疏矩阵展开的行
		if(ftemp == NULL)
		{
			printf("\nError: - %s %d",__FILE__,__LINE__);
			exit(0);
		}
		double diag = get_value_fspar(s,i,i);				//得到主对角线元素的值
		if(fabs(diag) < SMLL)
		{
			printf("\nError: - %s %d",__FILE__,__LINE__);
			printf("\n主对角线元素为零");
			exit(0);
		}
		for(long j = i + 1; j < n; j++)						//从对角线元素下一个元素开始消去
		{
			if(fabs(get_value_fspar(s,j,i)) < SMLL)	
				continue;
			double mul = diag / get_value_fspar(s,j,i);		//得到乘子mul
			b[j] -= mul * b[j];								//对常量数组进行变换
			unfspar_row(ftemp,s,j,n);						//对稀疏矩阵的j行进行展开，补齐0，放到ftemp数组中
			add_mulrow_fspar(s,ftemp,j,-mul);
			fsparfun(s,ftemp,j,n);							//对数组ftemp进行压缩，去掉0元素，并替换掉稀疏矩阵s的irow行
		}	
	}
/************************************************************************************************************************
	以下的代码虽然正确，但是很2
	for(long i = n - 1; i >= 0; i--)						//按行回代,从最后一行开始
	{
		double sum = 0;
		for(long j = n - 1; j > i; j--)						//0元素也参与了计算
		{
			sum += get_value_fspar(s,i,j) * x[j];
		}
		x[i] = (b[i] - sum) / get_value_fspar(s,i,i);
	}
*************************************************************************************************************************/
// 瞅瞅优秀代码
	for(long i = n - 1; i >= 0; i--)
	{
		double sum = 0;
		for(long j = 0; j < s[i].n; j++)					//只计算非0元素
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

//功能：对数组v进行压缩，去掉0元素，并替换掉稀疏矩阵s的irow行
//参数：s - 稀疏矩阵
//		v - 待压缩的数组
//		irow - 要被替换的行下标
//		n - 数组长度
void fsparfun(FSPAR *s,double *v,long irow,long n)
{	
	long nmax = stat_nozero(v,n);		//统计v中的非0元个数
	re_mem_fspar(s,irow,nmax);			//对s中的irow行重新分配空间
	for(long i = 0; i < n; i++)			//把v中的非0元素放到s的irow行
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

//功能：重新对稀疏矩阵的irow行进行分配空间，大小为n
//参数：s - 稀疏矩阵
//		irow - 要重新分配的行
//		nmax - 要分配的最大空间
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

//功能：统计长度为n的数组v中有多少个非0元素
//参数：v - 待统计的数组
//		n - 数组长度
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

//功能：对稀疏矩阵S的irow行进行展开，补齐0，并放到v数组中,目的是为了irow行进行计算
//参数：v - 展开后的数组
//		s - 稀疏矩阵
//		irow  - irow行
//		n - 矩阵的阶数
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

//功能：初始化数组v，长度为n
//参数：n - 数组长度
void initfvector(double *v,long n)
{
	for(long i = 0; i < n; i++)
	{
		v[i] = (double)0;
	}

	return;
}

//功能：稀疏矩阵的irow行元素乘于mul后加到长度为n的数组v
//参数：s - 稀疏矩阵
//		v - 被加的数组
//		irow - 稀疏矩阵s要加的行
//		mul - 乘子
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

//功能：从矩阵a中，得到index列最大的数值的行号
//返回：-1为错误；最大的数的下标,
//参数：a - 待查找矩阵
//		n - 数组长度
//		index - 矩阵的列索引，index是数组列号
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

//功能：从稀疏矩阵中得到index列中最大元素的行号
//返回：index列中最大元素的行号
//参数：s - 稀疏居中
//		index - 矩阵的列
//		n - 矩阵的阶数
long pos_max_row_fspar(FSPAR *s,long index,long n)
{
	long max_row = index;						//循环前置对角线元素为最大值
	double max_dtemp = get_value_fspar(s,index,index); 
	for(long i = index + 1; i < n; i++)			//从对角线元素开始查找
	{
		if(get_value_fspar(s,i,index) > max_dtemp)
			max_row = i;
	}

	return max_row;
}

//功能：在稀疏矩阵s中得到i行j列元素
//返回：0 -- i行j列元素为零元素
//		其他值 -- 得到i行j列的元素的值
//参数：s - 稀疏矩阵
//		i - i行
//		j - j列
double get_value_fspar(FSPAR *s,long i,long j)
{
	for(long k = 0; k < s[i].n; k++)
	{
		if(s[i].index[k] == j)
			return s[i].value[k];	
	}

	return 0;
}

///功能：交换矩阵a的i行和j行，i和j为下标
//参数：a - 矩阵
//		i - 待交换的行i
//		j - 待交换的行j
//		n - 矩阵的阶数
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
//功能：交换向量i和j元素，
//参数：i - i元素
//		j - j元素
//		n - 向量n的元素个数
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

//功能：把j行的元素乘以mul加到i行
//参数：a - 矩阵
//		mul - 乘子
//		i - 目标行
//		j - 和乘子相乘行
//		n - 矩阵阶数
void add_mulrow(double **a,double mul,long i,long j,long n)
{
	for(long k = 0; k < n; k++)
	{
		a[i][k] += mul * a[j][k];
	}

	return;
}

//功能：初始化一个栈
//参数：s - 栈
//		stack_size - 栈的大小
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

//功能：压栈
//参数：s - 栈
//		x - 被压入的数据
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

//功能：出栈
//参数：s - 栈
//		x - 出栈的元素
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

//功能：初始化一个队列
//参数：q - 队列
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

//功能：往队尾插入元素
//参数：q - 队列
//参数：x - 待插入元素
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

//功能：删除队头元素
//参数：q - 队列
//		x - 删除的元素放在x中
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

//功能：销毁队列
//参数：q - 待销毁的队列
void destory_queue(Linkqueue *q)
{
	while(q->qfront)
	{
		q->qback = q->qfront->next; //首先记下qfront的next节点
		free(q->qfront);			//释放qfront
		q->qfront = q->qback;
	}

	return;
}

//功能：斐波那契数列
long fib(int a)
{
	if(a < 2)
		return a==0 ? 0 : 1;
	
	return fib(a-1) + fib(a-2);
}

//功能：创建一个n阶浮点型数据的稀疏矩阵，并初始化
//		该矩阵按行存储，行之间是数组类型的顺序结构
//参数：s - 待创建的稀疏矩阵
//		n - 矩阵的阶数
void makefspar(FSPAR *&s,long n)  //采用引用传递
{
	s = (FSPAR *)calloc(n,sizeof(FSPAR));
	if(s == NULL)
	{
		printf("\nError: - %f %d",__FILE__,__LINE__);
		exit(0);
	}
	for(long i = 0; i < n; i++)
	{
		s->index = NULL;		//初始化
		s->value = NULL;
		s->nmax = 0;
		s->n = 0;
	}

	return;
}
