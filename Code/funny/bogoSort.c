#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int a = 0;
int bogoSort(int *arr, int n);
bool isOrder(int *arr, int n);
void shuffle(int *arr, int n);

int main (void)
{
	int arr[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
	srand((unsigned)time(NULL));
	printf("Times : %d\n", bogoSort(arr, 9));
	for (int i = 0; i < 9; i++)
		printf("%d ", arr[i]);
	printf("\n");
	return 0;
}

// bogo排序算法实现
// 接受一个无序数组，将其排序并返回排序次数
int bogoSort(int *arr, int n)
{
	int count = 0;
	while (!isOrder(arr, n))
	{
		shuffle(arr, n);
		count++;
	}
	return count;
}

// 判断数组是否已经有序
bool isOrder(int *arr, int n)
{
	for (int i = 1; i < n; i++)
		if (arr[i - 1] > arr[i])
			return false;
	return true;
}

// 随机对输入的数组进行排序
void shuffle(int *arr, int n)
{
	int temp;

	// 将这行加到这儿很难运行出来
	// 如果加到main函数的话，运行个几十万次还是可以算出来的
	// srand((unsigned)time(NULL));

	for (int i = 0; i < n; i++)
	{
		int j = (int)(rand() % n);
		temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
}
