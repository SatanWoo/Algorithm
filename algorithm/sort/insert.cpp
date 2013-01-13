//@Author:Ziqi Wu 
//        Tongji University 
//        2013-01-13 

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu

#include<iostream>
using namespace std;

int main()
{
	int test[] = {5,2,4,6,1,3};
	int size = sizeof(test) / sizeof(int);

	// 从第二个数字开始判断
	for (int i = 1; i < size; i++)
	{
		int currentNumber = test[i];
		// 向左遍历
		int j = i - 1;
		while (j >= 0 && test[j] > currentNumber) {
			//把大的往后放
			test[j + 1] = test[j];
			j -= 1;
		}

		test[j + 1] = currentNumber;
	}

	for (int i = 0; i < size; ++i)
	{
		cout << test[i] << endl;
	}
	
	return 0;
}