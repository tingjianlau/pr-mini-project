//#define _CRT_SECURE_NO_WARNINGS
//#include <iostream>
//#include<ctime>
//using namespace std;
//
//bool place(int x[], int k);//�жϷ��õ�k���ʺ�ʱ�Ƿ��ͻ��
//void lv(int n, int x[], int stepVegas);//LV�㷨�����������stepVegas���ʺ�
//
//int main()
//{
//	int stepVegas, n;
//	do
//	{
//		cout << "queue_num: ";
//		cin >> n;
//		int *x = new int[n + 1];//x[n]���ڴ�Ž�����
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
//		if ((x[i] == x[k]) || (abs(x[i] - x[k]) == abs(i - k)))//��ͬ�У��Ҳ��ڶԽ�����
//			return 0;
//	return 1;
//}
//void lv(int n, int x[], int stepVegas)
//{
//	int k, temp;
//	int *y = new int[n + 1];
//	long num = 0;//num��¼����
//	float start, finish;//��¼��ʼ�ͽ���ʱ��
//	start = clock();//��¼���п�ʼʱ��
//	srand((unsigned)time(NULL));
//	for (k = 1;k<n + 1;k++)
//	{
//		y[k] = k;//��1-n�ŵ�����y��
//	}
//	k = 1;
//	while (k <= stepVegas)
//	{
//		temp = rand() % (n + 1 - k) + 1;
//		x[k] = y[temp];//�ڿ��������������ѡ
//		if (place(x, k))
//		{
//			if (temp != n + 1 - k)//ȡ�ò������һ��������Ҫ��y����������Ҫ�Ǳ������������������ͬ����
//			{
//				y[temp] = y[n + 1 - k];//�����һ�������temp������
//			}
//			k++;
//		}
//	}
//	x[k] = 0;
//	while (k>stepVegas)
//	{
//		x[k] += 1;//ÿ���ʺ󶼴ӵ�һ�п�ʼ��,�����ǻ��ݵ���һ���ʺ�����һ��
//		while ((x[k] <= n) && (!place(x, k)))//��k���ʺ���ó�ͻ
//			x[k] += 1;//������һ��
//		if (x[k] <= n)
//			if (k == n)//�ҵ�һ����
//			{
//				num++;
//				//output(n,x);
//			}
//			else
//				x[++k] = 0;//��ʼ��k+1���ʺ�
//		else//��ʱ���ֵ�k���ʺ�û�п���λ��
//			x[k--] = 0;//�˻�����
//	}
//	finish = clock();//��¼���н���ʱ��
//	
//	cout << "stepVegas = " << stepVegas;
//	cout << " time = " << (float)(finish - start) / 1000 / num << endl;
//	delete[] y;
//}
//
