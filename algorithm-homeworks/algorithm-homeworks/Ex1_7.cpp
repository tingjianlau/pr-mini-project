//#define _CRT_SECURE_NO_WARNINGS
//#include	<stdio.h>
//#include	"stdlib.h"
//#include	<time.h>
//
//#define MAX_LENGTH 2
//
//int dirSearch(int x, int i, int val[], int length, int ptr[])//ֱ������
//{
//	while (x>val[i] && i<length)
//		i = ptr[i];
//
//	return i;
//}
//
//int sherwoodSearch(int x, int L, int LVal[], int LPtr[]) // sherwood����
//{
//	int j = LPtr[0];
//	for (int i = 0;i<L - 1;i++)
//		if (x>	LVal[i])
//		{
//			if (LVal[i]<LVal[i + 1])
//				j = LPtr[i + 1];
//		}
//
//	return j;
//}
//
//int main()
//{
//	
//	int L, x;
//	int val[] = { 2,3,13,1,5,21,8 };
//	int ptr[] = { 2,5,6,1,7,0,3 };
//	printf("����L:");
//	scanf("%d", &L);
//	printf("\n");
//	printf("����x:");
//	scanf("%d", &x);
//	printf("\n");
//	int length = sizeof(val) / sizeof(val[0]);
//	int LVal[MAX_LENGTH], LPtr[MAX_LENGTH];
//	int i, j, k;
//	int s, t, u;
//	srand((unsigned int)time);
//	// Ԥ����
//	for (i = 0;i<L;i++)
//	{
//		k = rand() % (length - 1);
//		LVal[i] = val[k];
//		LPtr[i] = ptr[k];
//	}
//
//	s = sherwoodSearch(x, L, LVal, LPtr);
//	printf("����ΪLС��x�����ֵΪ: %d\n", s);
//	for (t = 0;t<length;t++)
//	{
//		if (ptr[t] == s)
//		{
//			u = t;
//			break;
//		}
//	}
//	printf("��val[ptr[u]]��ʼ,�ҵ�Ŀ��λ��ptr[u]��%d\n", dirSearch(x, u, val, length, ptr));
//	
//	return 0;
//}