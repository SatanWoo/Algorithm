//@Author:Ziqi Wu 
//        Tongji University 
//        2013-02-08

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu

#include<iostream>
#include<cstring>
using namespace std;

#define maxVal 10000000

float nodeP[] = {0, 0.15, 0.1, 0.05, 0.1, 0.2};
float leaveP[] = {0.05, 0.1, 0.05, 0.05, 0.05, 0.1};

const int size = 6;

float w[size + 1][size + 1] = {0};
float wc[size + 1][size + 1] = {0};
float expectation[size + 1][size + 1]= {0};
float root[size][size] = {0};

//个人感觉，这两个是没冲突的，好像功能一样
float recursiveWeight(int i, int j)
{
	if (j <= i - 1) return leaveP[j];
	return recursiveWeight(i, j - 1) + nodeP[j] + leaveP[j];
}

float calculaeWeight(int i, int j)
{
	float sum = 0.0;
	for (int start = i; start <= j; ++start)
		sum += nodeP[start];

	for (int start = i - 1; start <= j; ++start)
		sum += leaveP[start];

	return sum;
}
/////////////////////////////////////////

void initWC()
{
	//memset(wc,0, sizeof(wc));
	for (int i = 1; i < size + 1; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			wc[i][j] = calculaeWeight(i,j);
		}
	}
}

void print()
{
	for (int i = 1; i < size + 1; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << wc[i][j] << " ";
		} 
		cout << endl;
	}
}

void printNew()
{
	for (int i = 1; i < size + 1; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			cout << w[i][j] << " ";
		} 
		cout << endl;
	}
}


void optimalBinaryTreeByPrecalculation()
{
	// Implicit Len 0
	for (int i = 1; i < size + 1; ++i)
	{
		int j = i - 1;
		expectation[i][j] = leaveP[j];
	}

	//计算跨度 i ~ j
	for (int len = 1; len < size ; ++len)
	{
		// 由于e[n+1 , n]在之前已经算过了，这里不用了
		for (int i = 1; i < size - len + 1; ++i)
		{
			int j = i + len - 1;// 从一个跨度开始~len跨度
			expectation[i][j] = maxVal;
			for (int rt = i; rt <= j; ++rt)
			{
				float temp = expectation[i][rt - 1] + wc[i][j] + expectation[rt + 1][j];
				if (temp < expectation[i][j])
				{
					expectation[i][j] = temp;
					root[i][j] = rt;
				}
			}
		}
	}
}

void optimalBinaryTreeByRecursive()
{
	for (int i = 1; i < size + 1; ++i)
	{
		int j = i - 1;
		expectation[i][j] = leaveP[j];
		w[i][j] = leaveP[j];
	}

	for (int len = 1; len < size ; ++len)
	{
		for (int i = 1 ; i < size + 1 - len ; i++)
		{
			int j = i - 1 + len;
			expectation[i][j] = maxVal;
			w[i][j] = w[i][j - 1] + leaveP[j] + nodeP[j];

			for (int rt = i; rt <= j; ++rt)
			{
				float temp = expectation[i][rt - 1] + w[i][j] + expectation[rt + 1][j];
				if (temp < expectation[i][j])
				{
					expectation[i][j] = temp;
					root[i][j] = rt;					
				}
			}
		}
	}
}

int main()
{
	// 一次性算完所有的算法。不用一次次从下级算到上次的算法。
	initWC();
	optimalBinaryTreeByPrecalculation();

	//递归算法
	//optimalBinaryTreeByRecursive();


	for (int i = 1; i < size; ++i)
	{
		for (int j = 1; j < size; j++)
		{
			cout << root[i][j] << " "; 
		}
		cout << endl;
	}


	return 0;
}