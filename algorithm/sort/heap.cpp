//@Author:Ziqi Wu 
//        Tongji University 
//        2013-01-17

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu

#include<iostream>
using namespace std;

int parent(int i);
int leftNode(int i);
int rightNode(int i);
void buildHeap(int *array, int size);
void heapSort(int *array, int size);
void buildMaxHeap(int *array, int index, int size);
void swap(int *array, int a, int b);

int main()
{
	int test[] = {4,1,3,2,16,9,10,14,8,7};
	int size = sizeof(test) / sizeof(int);
	heapSort(test,size);
	for (int i = 0; i < size; ++i)
	{
		cout << test[i] << endl;
	}
	return 0;
}

void heapSort(int *array, int size)
{
	// 最后的元素都属于排列过的，不用继续参与，heapsize代表仍然没有排列过的
	int heapSize = size;
	buildHeap(array, size);
	for (int i = size - 1; i >= 1; i--)
	{
		swap(array,0,heapSize - 1);
		heapSize -= 1;
		buildMaxHeap(array,0,heapSize);
		
	}
}

void buildHeap(int *array, int size)
{
	// 后面一半开始必然不会存在子节点。你不确定也可以改成Size
	for (int i = (size - 1 )/ 2; i >= 0; --i)
	{
		buildMaxHeap(array, i , size);
	}
}

void buildMaxHeap(int *array, int index, int size)
{
	if (index < 0 || index >= size)
		return ;

	int left = leftNode(index);
	int right = rightNode(index);
	int largest = index;

	if (left < size && array[left] > array[largest])
		largest = left;
	if (right < size && array[right] > array[largest])
		largest = right;

	if (largest != index)
	{
		swap(array, index, largest);
		buildMaxHeap(array, largest, size);
	}
}

void swap(int *array, int a, int b)
{
	int temp = array[b];
	array[b] = array[a];
	array[a] = temp;
}

int parent(int i)
{
	return (i - 1) >> 1;
}

int leftNode(int i)
{
	return (i << 1) + 1;
}

int rightNode(int i)
{
	return (i << 1) + 2;
}