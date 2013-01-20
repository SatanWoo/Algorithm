//@Author:Ziqi Wu 
//        Tongji University 
//        2013-01-20

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu

//有点像归并排序，但是还是有点区别的。

#include<iostream>
using namespace std;

void quicksort(int *array, int start, int end);
int partition(int *array, int start, int end);
void swap(int *array, int a, int b);

int main()
{
	int test[] = {3,5,1,4,6,8,2};
	int size = sizeof(test) / sizeof(int);
	quicksort(test, 0 ,size - 1);
	for (int i = 0; i < size; ++i)
	{
		cout << test[i] << endl;
	}
	return 0;
}

void quicksort(int *array, int start, int end)
{
	if (start >= end) return;

	int q = partition(array, start, end);
	quicksort(array, start, q - 1);
	quicksort(array, q + 1, end);
}

int partition(int *array, int start, int end)
{
	int x = array[end]; //这里其实可以优化，不一定要以最后的为支点。
	int firstPart = start;
	for (int j = start; j < end; ++j)
	{
		if (array[j] <= x)
		{
			swap(array, firstPart++, j);
		}
	}
	swap(array, firstPart, end);
	return firstPart;
}

void swap(int *array, int a, int b)
{
	int temp = array[b];
	array[b] = array[a];
	array[a] = temp;
}