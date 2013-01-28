//@Author:Ziqi Wu 
//        Tongji University 
//        2013-01-28

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu

#include <iostream>
using namespace std;

class Deque
{
public:
	Deque();
	~Deque();
	void queue(int x);
	int dequeue();
	int cou()const {return count;}
private:
	int count;
	int head;
	int rear;
	int element[5];
	int size;
};

Deque::Deque()
{

	head = 0;
	rear = 0;
	size = 5;
	count = 0; 
}

Deque::~Deque()
{
	head = rear = count = 0;
	size = 0;
}

void Deque::queue(int x)
{
	if (rear + head >= size) return ; // Overflow
	count ++;
	element[rear] = x;
	rear = rear + 1 >= size ? 0 : ++rear;
	//cout << "rear is " << rear << endl;
}

int Deque::dequeue()
{
	if (head == -1) return -1; // underflow
	count --;
	int result = element[head];
	head = head + 1 >= size ? 0 : ++head;
	//cout << "Head is " << head << endl;
	return result;
}

int main()
{
	Deque de;
	de.queue(2);
	de.queue(3);
	de.queue(4);
	de.queue(5);
	de.queue(6);
	de.dequeue();de.dequeue();de.dequeue();de.dequeue();de.dequeue();
	 cout << "Deque Finished" << endl;
	de.queue(7);
	de.queue(8);
	de.queue(9);
	de.queue(0);
	de.queue(-5);
	cout << de.dequeue() << endl;
	cout << de.dequeue() << endl;
	 cout << de.dequeue() << endl;
	 cout << de.dequeue() << endl;
	 de.queue(-7);
	 cout << de.dequeue() << endl;
	 cout << de.dequeue() << endl;
	return 0;
}
