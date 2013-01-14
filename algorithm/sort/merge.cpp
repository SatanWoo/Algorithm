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
void merge_sort(int *array, int start, int end);

int main()
{
	int test[] = {5,2,7,4,6};
	int size = sizeof(test) / sizeof(int);
	merge_sort(test,0,size - 1);

	for (int i = 0; i < size; ++i)
	{
		cout << test[i] << endl;
	}
	return 0;
}

void merge_sort(int *array, int start, int end)
{
	if (start >= end) return ;
	int middle = (start + end) / 2;
	merge_sort(array,start,middle);
	merge_sort(array,middle + 1,end);
	merge(array,start,middle,end);
}

void merge(int *array,  int start,  int middle,  int end)
{
	int size1 = middle - start + 1;
	int size2 = end - middle;

	int *first = new int [size1 + 1];
	int *second = new int [size2 + 1];

	for (int i = start; i < start + size1; ++i)
	{
		first[i - start] = array[i];
	}
	first[size1] = maxium;

	for (int i = start + size1; i < start + size1 + size2; i++)
	{
		second[i - start - size1] = array[i];
	}
	second[size2] = maxium;

	int firstIndex = 0, secondIndex = 0;

	for (int k = start; k <= end; k++)
	{
		if (first[firstIndex] < second[secondIndex])
		{
			array[k] = first[firstIndex] != maxium ? first[firstIndex] : array[k];
			firstIndex ++;
		} else {
			array[k] = second[secondIndex] != maxium ? second[secondIndex] :array[k];
			secondIndex ++;
		}
	}
}