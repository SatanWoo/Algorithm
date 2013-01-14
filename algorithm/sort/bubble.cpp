//@Author:Ziqi Wu 
//        Tongji University 
//        2013-01-13 

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu

#include<iostream>
using namespace std;
// 这是一个非常简单的排序方法。两两交换就可以
void bubbleSwap(int *array, int index, int nextIndex);

int main()
{
	int test[] = {1,2,6,7,8,0};
	int size = sizeof(test) / sizeof(int);
	for (int i = 0; i < size; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			bubbleSwap(test,i,j);
		}
	}


	for (int i = 0; i < size; ++i)
	{
		cout << test[i] << endl;
	}
	return 0;
}

void bubbleSwap(int *array, int index, int nextIndex)
{
	if (array[index] > array[nextIndex])
	{
		int temp = array[index];
		array[index] = array[nextIndex];
		array[nextIndex] = temp;
	}
} 