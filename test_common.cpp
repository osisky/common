#include "common.h"
#include "common.cpp"
void test_gauss()
{
	double a2[3] = {2,1,-1};
	double a3[3] = {-3,-1,2};
	double a4[3] = {-2,1,2};
	double *a1[3] = {a2,a3,a4};

	double b[3] = {8,-11,-3};
	double *x;
	x= (double *)calloc(3,sizeof(double));
	gauss(x,a1,b,3);
	for(long i = 0 ;i < 3; i++)
	{
		printf("\n\n%lf",x[i]);
	}
	return;
}

void test_gauss_fspar()
{

	FSPAR * s = NULL;
	makefspar(s,3);
	set_value_fspar(s,2,0,0);
	set_value_fspar(s,1,0,1);
	set_value_fspar(s,-1,0,2);
	set_value_fspar(s,-3,1,0);
	set_value_fspar(s,-1,1,1);
	set_value_fspar(s,2,1,2);
	set_value_fspar(s,-2,2,0);
	set_value_fspar(s,1,2,1);
	set_value_fspar(s,2,2,2);
	for(long i = 0; i < 3; i++)
	{
		for(long j = 0; j < 3; j++)
			printf("%lf ",s[i].value[j]);
		printf("\n");

	}
	double b[3] = {8,-11,-3};
	double *x;
	x= (double *)calloc(3,sizeof(double));
	gauss(x,s,b,3);
	for(long i = 0 ;i < 3; i++)
	{
		printf("\n\n%lf",x[i]);
	}
	
	free(s);
	free(x);
	return;
}



void main()
{
	double x[2] = {1,1};
	newton_powerflow(x,2);
	for(long i=0; i < 2; i++)
		printf("\n%lf",x[i]);

	return;
}