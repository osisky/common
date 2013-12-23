/*********************************************************
Description: my common
Author: xiubin
Company: OSI
Date: 2013-12-09
*********************************************************/
#ifndef _COMMON_H
#define _COMMON_H
#include "stdio.h"
#include "math.h"
#include "time.h"
#include "string.h"
#include "stdlib.h"
/*********************************************************************************/

#define SMLL    1.0E-10
#define increase_stack 20
#define NO		-1
#define powerflow_eps 0.00000001			//收敛精度	
#define ceil10(n) ((n/10 + 1) * 10)
/*********************************************************************************/

//定义栈的结构
typedef struct 
{
	double *top;
	double *low;
	long spacksize;

}STACK;

//定义队列每个节点的结构，注意队列用链表来表示，可以动态增加长度，不用插进去一个，就必须先出来一个。
typedef struct qnode
{
	double data;
	struct qnode *next;

}*Qnode;

//由于队列链表包含队头和队尾两个指针，所以用结构体表示
typedef struct  
{
	Qnode qfront;
	Qnode qback;
}Linkqueue;

//定义存储浮点型数据的稀疏矩阵，以顺序结构存储
typedef struct
{
	double *value;
	long *index;
	long nmax;
	long n;
}FSPAR;

/*********************************************************************************/
//功能：斐波那契数列
long fib(int a);

//功能：把j行的元素乘以mul加到i行
void add_mulrow(double **a,double mul,long i,long j,long n);

//功能：稀疏矩阵的irow行元素乘于mul后加到长度为n的数组v
void add_mulrow_fspar(FSPAR *s,double *v,long irow,double mul);

//功能：把x加到稀疏矩阵s的irow行icol列
void add_value_fspar(FSPAR *s,double x,long irow,long icol);

//功能：在目标串strdest中，查找源字符串strsrc是否在其中，类似strstr
char *bf(char *strdest,char *strsrc);

//功能：删除队头元素
void delete_queue(Linkqueue *q,double *x);

//功能：删除稀疏矩阵s的一个元素
void dele_element_fspar(FSPAR *s,long irow,long icol);

//功能：在长度为n的数组中删除index元素
void dele_felement_vector(double *v,long index,long n);
void dele_ielement_vector(long *v,long index,long n);

//功能：销毁队列
void destory_queue(Linkqueue *q);

//功能：折半查找，对已经排序过的数组进行查找
long find_half(long *a,long len,long x);

//功能：对数组v进行压缩，去掉0元素，并替换掉稀疏矩阵s的irow行
void fsparfun(FSPAR *s,double *v,long irow,long n);

//功能：高斯消去法解线性方程组，该方法只能解方程数 = 未知数，也就是a为满秩矩阵，采用满矩阵形式
long gauss(double *x,double **a,double *b,long n); 

//功能：高斯消去法解线性方程组，该方法只能解方程数 = 未知数，也就是a为满秩矩阵，采用稀疏矩阵
long gauss(double *x,FSPAR *s,double *b,long n);

//功能：在稀疏矩阵s中得到i行j列元素
double get_value_fspar(FSPAR *s,long i,long j);

//功能：往队尾插入元素
void insert_queue(Linkqueue *q, double x);

//功能：初始化一个栈
void init_stack(STACK *s,long stack_size);

//功能：初始化数组v，长度为n
void initfvector(double *v,long n);

//功能：在稀疏矩阵s中查找irow行和icol列的元素在value的下标vi
long lookup(FSPAR *s,long irow,long icol);

//功能：在长度为n的数组中，找到数值为icol的元素下标
long lookup(long *v,long icol,long n);

//功能：从矩阵a中，得到index列从对角线元素开始后的最大的数值的行号
long pos_max_row(double **a,long index,long n);

//功能：从稀疏矩阵中得到index列中最大元素的行号
long pos_max_row_fspar(FSPAR *s,long index,long n);

//功能：从长度为n的数组中找到绝对值最大的数的下标
long pos_absmax_vector(double *x,long n);

//功能：压栈
void push_stack(STACK *s, double x);

//功能：找到把数组a分成小和大两部分的键值的下标，例如-小数值 key 大数值。这时候小数值部分不一定是按小到大排序，它只是比key值小的部分
long quick_sort_key(long *a,long low,long hight);

//功能：重新对稀疏矩阵的irow行进行分配空间，大小为n
void re_mem_fspar(FSPAR *s,long irow,long n);

//功能：对稀疏矩阵s的irow行重新分配内存，大小为ceil10(s[i].n)，ceil10意思为大于或等于取整数，ceil(0到9) = 10 ceil(10到19) = 20;
//		只要s[irow].n发生了改变，就要对irow重新分配内存;
void re_mem_fspar(FSPAR *s,long irow);


//功能：往稀疏矩阵的i行j列元素设置成x
void set_value_fspar(FSPAR *s,double x,long i,long j);

//功能：快速排序-从小到大
void sort_quick(long *a,long low,long hight);

//功能：冒泡排序从小到大
void sort_bub(long *a,long n);

///功能：交换矩阵a的i行和j行，i和j为下标
void swap_row(double **a,long i,long j,long n);

//功能：统计长度为n的数组v中有多少个非0元素
long stat_nozero(double *v,long n);

//功能：交换向量i和j元素，
void swap_vector(double *a,long i,long j,long n);

//功能：对稀疏矩阵S的irow行进行展开，补齐0，并放到v数组中
void unfspar_row(double *v,FSPAR *s,long irow,long n);

/*********************************************************************************/
//测试函数

void printfs(FSPAR *s);

#endif