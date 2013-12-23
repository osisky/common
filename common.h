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
#define powerflow_eps 0.00000001			//��������	
#define ceil10(n) ((n/10 + 1) * 10)
/*********************************************************************************/

//����ջ�Ľṹ
typedef struct 
{
	double *top;
	double *low;
	long spacksize;

}STACK;

//�������ÿ���ڵ�Ľṹ��ע���������������ʾ�����Զ�̬���ӳ��ȣ����ò��ȥһ�����ͱ����ȳ���һ����
typedef struct qnode
{
	double data;
	struct qnode *next;

}*Qnode;

//���ڶ������������ͷ�Ͷ�β����ָ�룬�����ýṹ���ʾ
typedef struct  
{
	Qnode qfront;
	Qnode qback;
}Linkqueue;

//����洢���������ݵ�ϡ�������˳��ṹ�洢
typedef struct
{
	double *value;
	long *index;
	long nmax;
	long n;
}FSPAR;

/*********************************************************************************/
//���ܣ�쳲���������
long fib(int a);

//���ܣ���j�е�Ԫ�س���mul�ӵ�i��
void add_mulrow(double **a,double mul,long i,long j,long n);

//���ܣ�ϡ������irow��Ԫ�س���mul��ӵ�����Ϊn������v
void add_mulrow_fspar(FSPAR *s,double *v,long irow,double mul);

//���ܣ���x�ӵ�ϡ�����s��irow��icol��
void add_value_fspar(FSPAR *s,double x,long irow,long icol);

//���ܣ���Ŀ�괮strdest�У�����Դ�ַ���strsrc�Ƿ������У�����strstr
char *bf(char *strdest,char *strsrc);

//���ܣ�ɾ����ͷԪ��
void delete_queue(Linkqueue *q,double *x);

//���ܣ�ɾ��ϡ�����s��һ��Ԫ��
void dele_element_fspar(FSPAR *s,long irow,long icol);

//���ܣ��ڳ���Ϊn��������ɾ��indexԪ��
void dele_felement_vector(double *v,long index,long n);
void dele_ielement_vector(long *v,long index,long n);

//���ܣ����ٶ���
void destory_queue(Linkqueue *q);

//���ܣ��۰���ң����Ѿ��������������в���
long find_half(long *a,long len,long x);

//���ܣ�������v����ѹ����ȥ��0Ԫ�أ����滻��ϡ�����s��irow��
void fsparfun(FSPAR *s,double *v,long irow,long n);

//���ܣ���˹��ȥ�������Է����飬�÷���ֻ�ܽⷽ���� = δ֪����Ҳ����aΪ���Ⱦ��󣬲�����������ʽ
long gauss(double *x,double **a,double *b,long n); 

//���ܣ���˹��ȥ�������Է����飬�÷���ֻ�ܽⷽ���� = δ֪����Ҳ����aΪ���Ⱦ��󣬲���ϡ�����
long gauss(double *x,FSPAR *s,double *b,long n);

//���ܣ���ϡ�����s�еõ�i��j��Ԫ��
double get_value_fspar(FSPAR *s,long i,long j);

//���ܣ�����β����Ԫ��
void insert_queue(Linkqueue *q, double x);

//���ܣ���ʼ��һ��ջ
void init_stack(STACK *s,long stack_size);

//���ܣ���ʼ������v������Ϊn
void initfvector(double *v,long n);

//���ܣ���ϡ�����s�в���irow�к�icol�е�Ԫ����value���±�vi
long lookup(FSPAR *s,long irow,long icol);

//���ܣ��ڳ���Ϊn�������У��ҵ���ֵΪicol��Ԫ���±�
long lookup(long *v,long icol,long n);

//���ܣ��Ӿ���a�У��õ�index�дӶԽ���Ԫ�ؿ�ʼ���������ֵ���к�
long pos_max_row(double **a,long index,long n);

//���ܣ���ϡ������еõ�index�������Ԫ�ص��к�
long pos_max_row_fspar(FSPAR *s,long index,long n);

//���ܣ��ӳ���Ϊn���������ҵ�����ֵ���������±�
long pos_absmax_vector(double *x,long n);

//���ܣ�ѹջ
void push_stack(STACK *s, double x);

//���ܣ��ҵ�������a�ֳ�С�ʹ������ֵļ�ֵ���±꣬����-С��ֵ key ����ֵ����ʱ��С��ֵ���ֲ�һ���ǰ�С����������ֻ�Ǳ�keyֵС�Ĳ���
long quick_sort_key(long *a,long low,long hight);

//���ܣ����¶�ϡ������irow�н��з���ռ䣬��СΪn
void re_mem_fspar(FSPAR *s,long irow,long n);

//���ܣ���ϡ�����s��irow�����·����ڴ棬��СΪceil10(s[i].n)��ceil10��˼Ϊ���ڻ����ȡ������ceil(0��9) = 10 ceil(10��19) = 20;
//		ֻҪs[irow].n�����˸ı䣬��Ҫ��irow���·����ڴ�;
void re_mem_fspar(FSPAR *s,long irow);


//���ܣ���ϡ������i��j��Ԫ�����ó�x
void set_value_fspar(FSPAR *s,double x,long i,long j);

//���ܣ���������-��С����
void sort_quick(long *a,long low,long hight);

//���ܣ�ð�������С����
void sort_bub(long *a,long n);

///���ܣ���������a��i�к�j�У�i��jΪ�±�
void swap_row(double **a,long i,long j,long n);

//���ܣ�ͳ�Ƴ���Ϊn������v���ж��ٸ���0Ԫ��
long stat_nozero(double *v,long n);

//���ܣ���������i��jԪ�أ�
void swap_vector(double *a,long i,long j,long n);

//���ܣ���ϡ�����S��irow�н���չ��������0�����ŵ�v������
void unfspar_row(double *v,FSPAR *s,long irow,long n);

/*********************************************************************************/
//���Ժ���

void printfs(FSPAR *s);

#endif