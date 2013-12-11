#include "common.h"
#include "common.cpp"
void main()
{
	int a[6] = {3,5,6,2,1,8};
	sort_quick(a,0,5);
	//sort_bub(a,6);
	for(long i=0;i<6;i++)
		printf("%d ",a[i]);
	return;
}