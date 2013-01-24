//@Author:Ziqi Wu 
//        Tongji University 
//        2013-01-24

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu
#include<iostream>
using namespace std;

void countSort(int *array, int *resultArray, int size, int maxNumber);

int main()
{
	int test[] = {2,5,3,0,2,3,0,3};
	int size = sizeof(test) / sizeof(int);
	int result[8] = {0};
	countSort(test, result,size, 5);
	for (int i = 0; i < size; ++i)
	{
		cout << result[i] << endl;;
	}
	return 0;
}

void countSort(int *array, int *resultArray, int size, int maxNumber)
{
	int *tempArray = new int [maxNumber + 1];
	for (int i = 0; i <= maxNumber; ++i)
	{
		tempArray[i] = 0;
	}

	for (int i = 0; i < size ; ++i)
	{
		tempArray[array[i]] ++;
	}

	int k = 0, j = 0;//k代表temparray当前，j代表resultarray当前
	while(k <= maxNumber)
	{
		int count = tempArray[k];
		while(count --) {
 			resultArray[j++] = k;
		}
		k++;
	}	
	delete [] tempArray;
}