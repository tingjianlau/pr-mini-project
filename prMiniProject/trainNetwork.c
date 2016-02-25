#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>

#define FEATURES_CNT 4		//样本特征数
#define HIDE_NEURON_CNT 20		// 表示隐藏层神经元的数量
#define OUTPUT_CNT 2		//表示输出层的输出个数
#define TRAIN_CNT 500		//来表示训练的次数
#define	ACCURACY 0.1
#define A  0.1	// 调节参数
#define B  0.4
#define a  0.2
#define b  0.3

double	*sampleInput; //存储SAMPLE_CNT个样本的特征值
int		*realNumIndex; // 真实值
int		*desireOutput;	//存储SAMPLE_CNT个样本车牌号的实际值的概率，只有一个元素为1，其余为0	
double	inputLayerWeight[HIDE_NEURON_CNT][FEATURES_CNT];		// 表示某个输入对某个神经元的权重
double	outputLayerWeight[OUTPUT_CNT][HIDE_NEURON_CNT];		// 来表示某个神经元对某个输出的权重
double	hideOutput[HIDE_NEURON_CNT];					// 隐含层的激活值
double	networkOutput[OUTPUT_CNT];						//存储BP神经网络的输出
double	maxIn[FEATURES_CNT], minIn[FEATURES_CNT];
double	maxOut[OUTPUT_CNT], minOut[OUTPUT_CNT];
double	outputLayerWeightDiff[OUTPUT_CNT][HIDE_NEURON_CNT];	//某个神经元对某个输出的权重的修正量
double	inputLayerWeightDiff[HIDE_NEURON_CNT][FEATURES_CNT];	//输入对某个神经元的权重的修正量
double	e;	//误差
												
void	loadData(const char* src, const int sampleCnt);
void	initNetwork(const int sampleCnt);
void	trainNetwork(int sampleCnt);
void	writeWeight(const char* weightSrc);
FILE*	openTextFile(const char* filename, char* mode);
void	loadWeight(const char* src);
int		testNetworkMain(const char* featrueSrc, const char* weightSrc, int sampleCnt);
void	frontCompute(int var);
int		getExtremumIndex(const double nums[], int numsSize, int mode);

int  trainNetworkMain(const char* featrueSrc, const char* weightSrc, int sampleCnt)
{
	printf("dddd\n");
	loadData(featrueSrc, sampleCnt);
	
	initNetwork(sampleCnt);

	trainNetwork(sampleCnt);

	writeWeight(weightSrc);

	free(realNumIndex);
	free(sampleInput);
	free(desireOutput);
	
	return 0;
}

int  testNetworkMain(const char* featrueSrc, const char* weightSrc, int sampleCnt)
{
	int	i, iClass, errCnt=0;
	
	loadData(featrueSrc, sampleCnt);
	
	loadWeight(weightSrc);
	
	for (i = 0; i<sampleCnt; ++i) {
		frontCompute(i);
		iClass = getExtremumIndex(networkOutput, OUTPUT_CNT, 1);
		
		if (iClass != realNumIndex[i])
		{
			errCnt++;
			printf("error:%d 输出：%lf 实际类别：%d\n", i, networkOutput[iClass], realNumIndex[i]);
		}
	}
	printf("测试%d样本，错误样本个数：%d， 正确率：%lf \n", sampleCnt, errCnt, 1-(errCnt)/ (sampleCnt*1.0));
	free(realNumIndex);
	free(sampleInput);
	free(desireOutput);
	return 0;
}

// 求jizhi
int		getExtremumIndex(const double nums[], int numsSize, int mode) {
	int i, maxIndex, minIndex;

	maxIndex = minIndex = 0;
	for (i = 0; i<numsSize; ++i) {
		maxIndex = (nums[maxIndex]>nums[i]) ? maxIndex : i;
		minIndex = (nums[minIndex]<nums[i]) ? minIndex : i;
	}

	return (mode == 0) ? minIndex : maxIndex;
}

void	loadData(const char* src, const int sampleCnt) {
	FILE *fpFeatures;
	int i, j;
	double*		temp = NULL;

	realNumIndex = (int*)calloc(sampleCnt, sizeof(int));
	sampleInput = (double*)calloc(sampleCnt*FEATURES_CNT, sizeof(double));
	desireOutput = (int*)calloc(sampleCnt*OUTPUT_CNT, sizeof(int));
	
	temp = sampleInput;
	
	fpFeatures = openTextFile(src, "r");
	//printf("dd");
	for (i = 0;i < sampleCnt;i++) {
		for (j = 0; j < FEATURES_CNT; j++) {
			fscanf(fpFeatures, "%lf", temp++);
		}
		fscanf(fpFeatures, "%d", &realNumIndex[i]);
		
		if (realNumIndex[i] == -1)
		{
			realNumIndex[i] = 0;
		}
		
		*(desireOutput + i*OUTPUT_CNT + realNumIndex[i]) = 1;
		
	}
	
		
	
	fclose(fpFeatures);
}

//void loadData(const char* src, const int sampleCnt) {
//	FILE *fpFeatures;
//	int i, j;
//	double*		temp = NULL;
//
//	realNumIndex = (int*)calloc(sampleCnt, sizeof(int));
//	sampleInput = (double*)calloc(sampleCnt*FEATURES_CNT, sizeof(double));
//	desireOutput = (int*)calloc(sampleCnt*OUTPUT_CNT, sizeof(int));
//
//	temp = sampleInput;
//
//	fpFeatures = openTextFile(src, "r");
//
//	for (i = 0;i < sampleCnt;i++) {
//		for (j = 0; j < FEATURES_CNT; j++) {
//			fscanf(fpFeatures, "%lf", temp++);
//		}
//		fscanf(fpFeatures, "%d", &realNumIndex[i]);
//
//		if (realNumIndex[i] == -1)
//		{
//			realNumIndex[i] = 0;
//		}
//
//		*(desireOutput + i*OUTPUT_CNT + realNumIndex[i]) = 1;
//
//	}
//
//
//
//	fclose(fpFeatures);
//}

//初始化神经网络，包括输入层特征值的归一化和权重的随机初始化
void	initNetwork(const int sampleCnte) {
	int i, j;
	
	// 归一化
	int curIndex;

	for ( i = 0; i < FEATURES_CNT; i++)
	{
		minIn[i] = maxIn[i] = sampleInput[i];
		for ( j = 0; j < sampleCnte; j++)
		{
			curIndex = j*FEATURES_CNT + i;
			maxIn[i] = maxIn[i]>sampleInput[curIndex] ? maxIn[i] : sampleInput[curIndex];
			minIn[i] = minIn[i]<sampleInput[curIndex] ? minIn[i] : sampleInput[curIndex];
		}
	}
	// 归一化处理
	for ( i = 0; i < FEATURES_CNT; i++)
	{
		for ( j = 0; j < sampleCnte; j++)
		{
			curIndex = j*FEATURES_CNT + i;
			sampleInput[curIndex] = (sampleInput[curIndex] - minIn[i] + 1) / (maxIn[i] - minIn[i] + 1);
		}
	}

	//权重随机初始化
	for (i = 0; i < HIDE_NEURON_CNT; ++i) {
		for (j = 0; j < FEATURES_CNT; ++j) {
			inputLayerWeight[i][j] = (rand()*2.0 / RAND_MAX - 1) / 2;
			inputLayerWeightDiff[i][j] = 0;
		}
	}

	for (i = 0; i < HIDE_NEURON_CNT; ++i) {
		for (j = 0; j < OUTPUT_CNT; ++j) {
			outputLayerWeight[j][i] = (rand()*2.0 / RAND_MAX - 1) / 2;
			outputLayerWeightDiff[j][i] = 0;
		}
	}
}

//test 初始化神经网络，包括输入层特征值的归一化和权重的随机初始化
void loadWeight(const char* src) {
	FILE *fpWeight;
	int i, j;
	double*		temp = NULL;
	
	//权重
	fpWeight = openTextFile(src, "r");
	temp = inputLayerWeight;
	for (i = 0; i < HIDE_NEURON_CNT; ++i) {
		for (j = 0; j < FEATURES_CNT; ++j) {
			fscanf(fpWeight, "%lf", temp++);
		}
	}
	
	temp = outputLayerWeight;
	for (i = 0; i < HIDE_NEURON_CNT; ++i) {
		for (j = 0; j < OUTPUT_CNT; ++j) {
			fscanf(fpWeight, "%lf", temp +j*HIDE_NEURON_CNT +i);
		}
	}
	fclose(fpWeight);
}

// 各层的正向传播
void frontCompute(int var) {
	int i, j;
	double sum;
	//printf("%d \n", var);
	//输入层到隐含层的正向传播   
	for (i = 0; i < HIDE_NEURON_CNT; ++i) {
		sum = 0;
		for (j = 0; j < FEATURES_CNT; ++j) {
			sum += inputLayerWeight[i][j] * sampleInput[var*FEATURES_CNT + j];
			
		}
		
		hideOutput[i] = 1 / (1 + exp(-1 * sum));
		//printf("%lf %lf\n", sum, hideOutput[i]);
		//printf("%lf \n", hideOutput[i]);
	}
	/*  隐藏层到输出层正向传播   */
	for (i = 0; i < OUTPUT_CNT; ++i) {
		sum = 0;
		for (j = 0; j < HIDE_NEURON_CNT; ++j)
			sum += outputLayerWeight[i][j] * hideOutput[j];

		//networkOutput[i] = sum;
		networkOutput[i] = 1 / (1 + exp(-1 * sum));
		
		//printf("==%lf== \n", networkOutput[i]);
	}
	
}

//void backUpdate(int var)
//{
//	int i, j;
//	int	curIndex;
//	double t;
//	for (i = 0; i < HIDE_NEURON_CNT; ++i)
//	{
//		t = 0;
//		for (j = 0; j < OUTPUT_CNT; ++j) {
//			curIndex = var*OUTPUT_CNT + j;
//			t += (networkOutput[j] - desireOutput[curIndex])*outputLayerWeight[j][i];
//
//			outputLayerWeightDiff[j][i] = A*outputLayerWeightDiff[j][i] + B*(networkOutput[j] - desireOutput[curIndex])*hideOutput[i];
//			outputLayerWeight[j][i] -= outputLayerWeightDiff[j][i];
//		}
//
//		for (j = 0; j < FEATURES_CNT; ++j) {
//			curIndex = var*FEATURES_CNT + j;
//			inputLayerWeightDiff[i][j] = a*inputLayerWeightDiff[i][j] + b*t*hideOutput[i] * (1 - hideOutput[i])*sampleInput[curIndex];
//			inputLayerWeight[i][j] -= inputLayerWeightDiff[i][j];
//		}
//	}
//}

void backUpdate(int var)
{
	int i, j;
	int	curIndex;
	double t;

	double	*theta2;		// 输出层上每个节点的残差，表明了该节点对最终输出值的残差产生了多少影响
	double	*theta1;		// 隐含层层上每个节点的残差

	theta2 = (double*)calloc(OUTPUT_CNT, sizeof(double));
	theta1 = (double*)calloc(HIDE_NEURON_CNT, sizeof(double));
	
	// 计算隐含层->输出层的权值系数增量
	for (j = 0; j < OUTPUT_CNT; j++)
	{
		curIndex = var*OUTPUT_CNT + j;
		// 当前节点的残差
		theta2[j] = (desireOutput[curIndex] - networkOutput[j])*networkOutput[j] * (1 - networkOutput[j]);
		//printf("%lf %lf \n", theta2[j], networkOutput[j]);
	}

	for ( i = 0; i < HIDE_NEURON_CNT; i++)
	{
		for ( j = 0; j < OUTPUT_CNT; j++)
		{
			outputLayerWeightDiff[j][i] = A * hideOutput[i] * theta2[j];
			
		}
	}

	// 计算输入层->隐含层的权值系数增量
	for ( i = 0; i < HIDE_NEURON_CNT; i++)
	{
		for ( j = 0; j < OUTPUT_CNT; j++)
		{
			theta1[i] += outputLayerWeight[j][i] * theta2[j];
		}
		theta1[i] *= hideOutput[i] * (1 - hideOutput[i]);
	}

	for ( i = 0; i < FEATURES_CNT; i++)
	{
		curIndex = var*FEATURES_CNT + i;
		for ( j = 0; j < HIDE_NEURON_CNT; j++)
		{
			inputLayerWeightDiff[j][i] = A*sampleInput[curIndex] * theta1[j];
		}
	}

	// 更新网络权值
	for ( i = 0; i < FEATURES_CNT; i++)
	{
		for ( j = 0; j < HIDE_NEURON_CNT; j++)
		{
			inputLayerWeight[j][i] += inputLayerWeightDiff[j][i];
		}
	}

	for (i = 0; i < HIDE_NEURON_CNT; i++)
	{
		for (j = 0; j < OUTPUT_CNT; j++)
		{
			outputLayerWeight[j][i] += outputLayerWeightDiff[j][i];
		}
	}

	free(theta1);
	free(theta2);

	/*for ( i = 0; i < OUTPUT_CNT; i++)
	{
		theta2[i] = 0.0;
	}

	for (i = 0; i < HIDE_NEURON_CNT; i++)
	{
		theta1[i] = 0.0;
	}*/

	/*for (i = 0; i < HIDE_NEURON_CNT; ++i)
	{
		t = 0;

		
		for (j = 0; j < OUTPUT_CNT; ++j) {
			curIndex = var*OUTPUT_CNT + j;
			t += (networkOutput[j] - desireOutput[curIndex])*outputLayerWeight[j][i];

			outputLayerWeightDiff[j][i] = A*outputLayerWeightDiff[j][i] + B*(networkOutput[j] - desireOutput[curIndex])*hideOutput[i];
			outputLayerWeight[j][i] -= outputLayerWeightDiff[j][i];
		}

		for (j = 0; j < FEATURES_CNT; ++j) {
			curIndex = var*FEATURES_CNT + j;
			inputLayerWeightDiff[i][j] = a*inputLayerWeightDiff[i][j] + b*t*hideOutput[i] * (1 - hideOutput[i])*sampleInput[curIndex];
			inputLayerWeight[i][j] -= inputLayerWeightDiff[i][j];
		}
	}*/
}

void  trainNetwork(int sampleCnt) {
	int i, j , c = 0;

	do {
		e = 0;
		for (i = 0; i < sampleCnt; ++i) {
			frontCompute(i);
			for ( j = 0; j < OUTPUT_CNT; j++)
			{
				e += (networkOutput[j] - desireOutput[i*OUTPUT_CNT + j]) * (networkOutput[j] - desireOutput[i*OUTPUT_CNT + j]);

			}
			//e += fabs(networkOutput[realNumIndex[i]] - desireOutput[i*OUTPUT_CNT + realNumIndex[i]]);

			//printf("%lf \n", desireOutput[i*OUTPUT_CNT + realNumIndex[i]]);
			backUpdate(i);
		}
		c++;
		//printf("迭代次数：%d  误差：%lf 隐含层神经元个数：%d \n", c, e / sampleCnt, HIDE_NEURON_CNT);

	} while (c<TRAIN_CNT && e / sampleCnt>ACCURACY);
	printf("迭代次数：%d  误差：%lf 隐含层神经元个数：%d \n", c, e / sampleCnt, HIDE_NEURON_CNT);
}

void writeWeight(const char* weightSrc)
{
	FILE *fpNeuron;
	int i, j;

	fpNeuron = openTextFile(weightSrc, "w");
	for (i = 0; i < HIDE_NEURON_CNT; ++i)
		for (j = 0; j < FEATURES_CNT; ++j)
			fprintf(fpNeuron, "%lf ", inputLayerWeight[i][j]);

	fprintf(fpNeuron, "\n\n\n\n");

	for (i = 0; i < HIDE_NEURON_CNT; ++i)
		for (j = 0; j < OUTPUT_CNT; ++j)
			fprintf(fpNeuron, "%lf ", outputLayerWeight[j][i]);

	fclose(fpNeuron);
}

FILE*	openTextFile(const char* filename, char* mode) {
	FILE*	fp;
	if ((fp = fopen(filename, mode)) == NULL)
	{
		printf("打开文件%s失败！\n", filename);
		exit(0);
	}
	return fp;
}

double	sigmoid(double x) {
	return 1 / (1 + exp(-x));
}