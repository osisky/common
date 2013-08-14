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
/*********************************************************************************/
void add_mulrow(double **a,double mul,long i,long j,long n);
long find_half(long *a,long len,long x);
void get_col_vector(double *x,double **a,long index,long n);
long pos_max_row_index(double **a,long index,long n);
long quick_sort_key(long *a,long low,long hight);
void sort_quick(long *a,long low,long hight);
void sort_bub(long *a,long n);
void swap_row(double **a,long i,long j,long n);
void swap_vector(double *a,long i,long j,long n);
#endif