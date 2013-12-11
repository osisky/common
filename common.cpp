/*********************************************************
Author:xiubin
Date:2013-12-09

*********************************************************/
#include "common.h"

/*********************************************************
冒泡排序-从大到小
n为数组长度
*********************************************************/
void sort_bub(int *a,int n)
{
	int i,j,t;
	for(i=n-1;i>=0;i--)
	{
		for(j=0;j<i;j++)
		{
			if(a[j]<a[j+1])
			{
				t=a[j];
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}
	return;
} 

int quick_sort_key(int *a,int low,int hight)
{
	if(low > hight)	return -1;
	if(low == hight)	return low;
	int key = a[low];
	
	while(low < hight)
	{
		while(low < hight && a[hight] >= key) 
			hight--;
		if(low < hight)
		{
			a[low] = a[hight];
			low++;
		}
		
		while(low < hight && a[low] < key)
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

/*********************************************************
快速排序-从小到大
low和hight为下标
*********************************************************/
void sort_quick(int *a,int low,int hight)
{

	int p;
	if(low < hight)
	{
		p = quick_sort_key(a,low,hight);
		sort_quick(a,low,p-1);
		sort_quick(a,p+1,hight);
	}
	
	return;
}

/*********************************************************
//折半查找
//len为数组长度
//x为要查找的元素
*********************************************************/
int find_half(int *a,int len,int x)
{

	int low = 1;
	int hight = len;
	int mid = (low + len) / 2;
	for(long i= 0;i<len;i++)
	{
		if(a[mid] > x)
		{
			hight  = mid  - 1;
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

