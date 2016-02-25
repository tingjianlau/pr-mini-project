#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"stdlib.h"
#include"math.h"
#include"time.h"
typedef double(*ptr)(double); 

long k = 0;

double func(double x)
{
	return  2*x*x+1;
}

double PA(long n, float a, float b, float c, float d, ptr f)
{
	double x, y;
	double S;
	long i = 1;
	srand((unsigned int)time);
	for (;i <= n;i++)
	{
		x = double(rand()*(b - a)) / RAND_MAX + a;
		y = double(rand()*(d - c)) / RAND_MAX + c;
		if (y <= f(x))k++;
	}
	S = k*(d - c)*(b - a) / n + c*(b - a);
	return S;
}


//int main()
//{
//	long n;
//	float a = 1, b=3, c=5, d=12;   
//	ptr f;
//	do
//	{
//		printf("¼üÈën: ");
//		scanf("%ld", &n);
//		f = func;
//		printf("    ½á¹û: %.6f \n", PA(n, a, b, c, d, f));
//	} while (1);
//	
//	return 0;
//}