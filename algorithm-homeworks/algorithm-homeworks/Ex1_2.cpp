//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include"stdlib.h"
//#include"time.h"
//#include"math.h"
//typedef double(*ptr) (double x);
//
//
//double func(double x)
//{
//	double m = sqrt(1 - pow(x, 2));
//
//	return m;
//}
//
//double HitorMiss(ptr f, long n)
//{
//	long k = 0;
//	double x, y;
//	srand((unsigned int)time);
//	for (long i = 1;i <= n;i++)
//	{
//		x = double(rand() % (RAND_MAX + 1)) / RAND_MAX;
//		y = double(rand() % (RAND_MAX + 1)) / RAND_MAX;
//		if (y <= f(x))
//			k++;
//	}
//
//	return (double)k / n;
//}
//
//
////int main()
////{
////
////	long n;
////	double S;
////	ptr f = func;
////	do
////	{
////		printf("¼üÈën:");
////		scanf("%d", &n);
////		S = 4 * HitorMiss(f, n);
////		printf("   PI¹ÀÖµÎª%.6f\n", S);
////	} while (1);
////
////	return 0;
////}