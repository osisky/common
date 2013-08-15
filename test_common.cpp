#include "common.h"
#include "common.cpp"
void main()
{
	double a2[3] = {2,1,-1};
	double a3[3] = {-3,-1,2};
	double a4[3] = {-2,1,2};
	double *a1[3] = {a2,a3,a4};
	//111
	double b[3] = {8,-11,-3};
	double *x;
	x= (double *)calloc(3,sizeof(double));
	gauss(x,a1,b,3);
	for(long i = 0 ;i < 3; i++)
	{
		printf("\n\n%lf",x[i]);
	}
	//get_col_vector(temp,(double**)a,0,3);
	return;
}