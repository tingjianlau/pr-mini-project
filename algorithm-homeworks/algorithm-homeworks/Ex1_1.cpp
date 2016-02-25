#define _CRT_SECURE_NO_WARNINGS
#include	<stdio.h>
#include	"stdlib.h"
#include	"time.h"

double Darts(long n)
{
	long k = 0;
	double x, y;
	srand((unsigned int)time(NULL));
	for (long i = 1;i <= n;i++)
	{
		x = double(rand() % (RAND_MAX + 1)) / RAND_MAX;
		y = x;
		if ((x*x + y*y) <= 1)
			k++;
	}
	return (double(4 * k) / n);
}


//int main()
//{
//	long n;
//	do {
//		printf("¼üÈën:");
//		scanf("%d", &n);
//		printf("   ¹ÀÖµÎª%.6f\n", Darts(n));
//	} while (1);
//
//	return 0;
//}