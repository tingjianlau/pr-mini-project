#define _CRT_SECURE_NO_WARNINGS
#include	<stdio.h>
#include	"trainNetwork.c"

int	main() {
	/*trainNetworkMain("train.data", "weight.txt", 8285);
	testNetworkMain("test.data", "weight.txt", 2702);*/
	trainNetworkMain("iris_train.txt", "weight.txt", 80);
	testNetworkMain("iris_test.txt", "weight.txt", 20);
	printf("\n");

	return 0;
}