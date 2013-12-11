#ifndef _COMMON_H
#define _COMMON_H
#include "stdio.h"
#include "math.h"
#include "time.h"
#include "string.h"
#include "stdlib.h"
int find_half(int *a,int len,int x);
void sort_quick(int *a,int low,int hight);
int quick_sort_key(int *a,int low,int hight);
void sort_bub(int *a,int n);
#endif