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

//功能：高斯消去法解线性方程组，该方法只能解方程数 = 未知数，也就是a为满秩矩阵
//返回：-1为无解，0为求解成功
//参数：x - 求解的未知量
//      a - 系数矩阵
//		b - 常数列向量
//		n - 方程数/矩阵的行或列
long gauss(double *x,double **a,double *b,long n)   
{
	for(long i = 0; i < n-1; i++)					 //按列消去，得到上三角矩阵
	{
		long max_row = pos_max_row_index(a,i,n);	 //得到i列中数值最大的元素所在的行号
		if(max_row < SMLL)	
		{
			printf("\nError: - %s %d",__FILE__,__LINE__);
			exit(0);
		}
		swap_row(a,i,max_row,n);					 //交换i行和max_row行
		swap_vector(b,i,max_row,n);					 //相应的常量也同时交换
		for(long j = i + 1; j < n; j++)
		{
			if(fabs(a[j][i]) < SMLL)	continue;	 //如果元素为0，说明该方程少一个未知量，不影响
			double mul = a[j][i] / a[i][i];		     //得到进行初等行变换的乘子
			b[j] -= mul * b[i];						 //首先对相应的常量进行变换
			add_mulrow(a,-mul,j,i,n);				 //对系数矩阵进行行变换
		}
	}
	for(long i = n-1; i >=0; i--)
	{
		
	}



	return 0;
}

//功能：从矩阵a中，得到index列最大的数值的行号
//返回：-1为错误；最大的数的下标,
//参数：a - 待查找矩阵
//		n - 数组长度
//		index - 矩阵的列索引，index是数组列号
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