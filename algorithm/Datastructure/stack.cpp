//@Author:Ziqi Wu 
//        Tongji University 
//        2013-01-28

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu

#include<iostream>
using namespace std;

class Stack
{
public:
	Stack();
	~Stack();
	void push(int x);
	int pop();
	int size()const {return top + 1;}
	bool empty()const {return top < 0;}

private:
	void copyElementToNewArray();
	int *array;
	int count;
	int top;
};

Stack::Stack()
{
	count = 5;
	top = -1;
	array = new int [count]; 
}

Stack::~Stack()
{
	count = 0;
	top = -1;
	delete [] array;
}

void Stack::push(int x)
{
	if (top >= count) copyElementToNewArray();
	array[++top] = x;
}

int Stack::pop()
{
	if (top < 0) return -1;
	return array[top--];
}

void Stack::copyElementToNewArray()
{
	//这个是模仿STL的实现理念，每次不够用，扩大两倍
	count *= 2;
	int *newArray = new int [count];
	for (int i = 0; i < top; ++i) newArray[i] = array[i];
	delete [] array, array = NULL;
	array = newArray;
}

int main()
{
	Stack test;
	test.push(5);
	test.push(2);
	test.push(1);
	test.push(4);
	test.push(7);
	test.push(6);
	cout << test.size() << endl;
	cout << test.pop() << endl;
	cout << test.pop() << endl;
	cout << test.pop() << endl;
	test.push(6);
	cout << test.size() << endl;
}