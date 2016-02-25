//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include"stdlib.h"
//#include<time.h>
//#include"math.h"
//
//#define PI 3.1415926
//#define N 10000
//
//int SetCount(int X[], int n)
//{
//	int x, i;
//	int k = 0;
//	int* rec = (int*)calloc(n, sizeof(int));
//	//printf("%d \n", X[n - 1]);
//	srand((unsigned)time(NULL));
//	do {
//		x = rand() % (n - 1);
//		for (i = 0;i <= k;i++)
//		{
//			if (k == 0)
//			{
//				rec[i] = X[x];
//			}
//			else if (X[x] == rec[i])
//				break;
//		}
//
//		if (i == k + 1)
//		{
//			rec[i - 1] = X[x];
//			k++;
//		}
//		else break;
//	} while (1);
//
//	return int(2 * k*k / PI);
//}
//
//int main()
//{
//	int n;
//	
//	do
//	{
//		printf("键入n: ");
//		scanf("%d", &n);
//		int* X = (int*)calloc(n, sizeof(int));
//		for (int i = 0; i < n; i++)
//		{
//			X[i] = i;
//		}
//		printf("  答案是：%d\n", SetCount(X, n));
//		free(X);
//	} while (1);
//
//	return 0;
//}
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include"stdlib.h"
#include<time.h>
#include"math.h"

#define Bool int

int pw_1(int a, int t)
{
	for (int i = 1;i<t;i++)
	{
		a = a*a;
	}
	return a;

}


Bool Btest(int a, int n)
{

	int s = 0, t = n - 1;
	int i;
	while (t % 2 == 0)
	{
		s++;
		t = t / 2;
	}
	int x = pw_1(a, t) % n;
	if (x == 1 || x == n - 1)
		return true;
	for (i = 1;i<s;i++)
	{
		x = (x*x) % n;
		if (x == n - 1)
			return true;
	}
	return false;

}

int lg(int n)
{
	int i = 0;

	while (n>10)
	{
		i++;
		n = n / 10;

	}
	return i;
}

Bool MillRab(int n)
{
	srand((unsigned int)time);
	int a = 2 + rand() % (n - 4);     
	return Btest(a, n);

}
Bool RepeatMillRab(int n, int k)
{
	for (int i = 1;i <= k;i++)
	{
		if (MillRab(n) == false)
			return false;
	}
	return true;
}

void printPrimes()
{
	int n = 5;
	printf("10000以内的素数有:\n");
	printf("2 3 ");
	while (n <= 10000)
	{

		if (RepeatMillRab(n, lg(n)))
			printf("%d ", n);
		n += 2;
	}

}

int main()
{
	printPrimes();

	return 0;
}

