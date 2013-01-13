//@Author:Ziqi Wu 
//        Tongji University 
//        2013-01-13 

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu
#include<iostream>
using namespace std;

// 这个表示这个部分已经归并结束了
#define maxium 100000

// middle这个参数要特别注意，有的实现要补1，有的不用，自己当心
// 归并前无论你用什么方法，确保已经排好序
void merge(int *array,  int start,  int middle,  int end); 

int main()
{
	int test[] = {0,2,4,7,3,9,20};
	int size = sizeof(test) / sizeof(int);
	int middle = size / 2;
	merge(test, 0, middle, size - 1);

	for (int i = 0; i < size; ++i)
	{
		cout << test[i] << endl;
	}
	return 0;
}

void merge(int *array,  int start,  int middle,  int end)
{
	// 前半
	int size1 = middle - start + 1;
	int size2 = end - middle;

	int *first = new int [size1 + 1];
	int *second = new int [size2 + 1];

	for (int i = start; i < size1; ++i)
	{
		first[i] = array[i];
	}
	first[size1] = maxium;

	for (int i = size1; i < size1 + size2; i++)
	{
		second[i - size1] = array[i];
	}
	second[size2] = maxium;

	int firstIndex = 0, secondIndex = 0;

	for (int k = start; k <= end; k++)
	{
		if (first[firstIndex] < second[secondIndex])
		{
			array[k] = first[firstIndex];
			firstIndex ++;
		} else {
			array[k] = second[secondIndex];
			secondIndex ++;
		}
	}
}