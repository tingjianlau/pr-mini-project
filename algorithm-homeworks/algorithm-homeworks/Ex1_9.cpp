//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include<ctime>
//using namespace std;
//
//bool place(int x[], int k);//判断放置第k个皇后时是否冲突。
//void lv(int n, int x[], int stepVegas);//LV算法，先随机放置stepVegas个皇后
//
//int main()
//{
//	int stepVegas, n;
//	do
//	{
//		cout << "queue_num: ";
//		cin >> n;
//		int *x = new int[n + 1];//x[n]用于存放解向量
//		for (stepVegas = 1;stepVegas<n / 2;stepVegas++)
//		{
//			lv(n, x, stepVegas);
//		}
//		delete[] x;
//	} while (1);
//	
//	return 1;
//}
//
//bool place(int x[], int k)
//{
//	for (int i = 1;i<k;i++)
//		if ((x[i] == x[k]) || (abs(x[i] - x[k]) == abs(i - k)))//不同列，且不在对角线上
//			return 0;
//	return 1;
//}
//void lv(int n, int x[], int stepVegas)
//{
//	int k, temp;
//	int *y = new int[n + 1];
//	long num = 0;//num记录解数
//	float start, finish;//记录开始和结束时间
//	start = clock();//记录运行开始时间
//	srand((unsigned)time(NULL));
//	for (k = 1;k<n + 1;k++)
//	{
//		y[k] = k;//把1-n放到数组y中
//	}
//	k = 1;
//	while (k <= stepVegas)
//	{
//		temp = rand() % (n + 1 - k) + 1;
//		x[k] = y[temp];//在可行数据域中随机选
//		if (place(x, k))
//		{
//			if (temp != n + 1 - k)//取得不是最后一个数，需要对y进行整理，主要是避免用随机数产生了相同的数
//			{
//				y[temp] = y[n + 1 - k];//把最后一个数与第temp个交换
//			}
//			k++;
//		}
//	}
//	x[k] = 0;
//	while (k>stepVegas)
//	{
//		x[k] += 1;//每个皇后都从第一列开始试,或者是回溯到上一个皇后尝试下一列
//		while ((x[k] <= n) && (!place(x, k)))//第k个皇后放置冲突
//			x[k] += 1;//尝试下一列
//		if (x[k] <= n)
//			if (k == n)//找到一个解
//			{
//				num++;
//				//output(n,x);
//			}
//			else
//				x[++k] = 0;//开始第k+1个皇后
//		else//此时发现第k个皇后没有可行位置
//			x[k--] = 0;//退回重试
//	}
//	finish = clock();//记录运行结束时间
//	
//	cout << "stepVegas = " << stepVegas;
//	cout << " time = " << (float)(finish - start) / 1000 / num << endl;
//	delete[] y;
//}
//
