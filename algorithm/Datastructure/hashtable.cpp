//@Author:Ziqi Wu 
//        Tongji University 
//        2013-02-04

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu

//hashtable 最重要的是利用散列函数进行均匀化散列
//这里实现一个完全散列
//关键在于是一个二次散列过程，并且要确保碰撞率小必须要严格控制数组大小。
//所以比较适合用来构造静态关键字的大小。

#include<iostream>
#include<string.h>
#include<math.h>
using namespace std;

#define pFactor 101
#define aFactor 3
#define bFactor 42

class SlotList
{
public:
	SlotList();
	SlotList(int facotorA, int factorB, int size);
	~SlotList();
	void insertNewElement(int key);
	void print();
private:
	int factorA;
	int factorB;
	int currentSize;
	int *elements;
	int getHashCode(int key);
};

SlotList::SlotList()
{
	factorA = 0;
	factorB = 0;
	currentSize = 0;
}

SlotList::SlotList(int facA, int facB, int size)
{
	factorA = facA;
	factorB = facB;
	currentSize = pow(size, 2);

	elements = new int[currentSize];
	memset(elements, 0, currentSize * sizeof(int));
}

SlotList::~SlotList()
{
	delete [] elements, elements = NULL;
}

void SlotList::print()
{
	for (int i = 0; i < currentSize; ++i)
	{
		if(elements[i] != 0) cout << elements[i] << " ";
	}
	cout << endl;
}

void SlotList::insertNewElement(int key)
{
	int hashCode = getHashCode(key);

	//cout << "Second Hash Code is " << hashCode << endl;

	if (hashCode >= 0 && hashCode < currentSize && elements[hashCode] == 0) {
		elements[hashCode] = key;
		return ;
	}

	cout << "Insert Error" << endl;
}

int SlotList::getHashCode(int key)
{
	int result = ((factorA * key + factorB) % pFactor) % currentSize;
	return result;
}

class HashTable
{
public:
	HashTable();
	~HashTable();
	void insertNewElement(int key);
	void print();
private:
	int getHashCode(int key);
	void configureSlot(int index, int key);
	void configure(int index);
	SlotList *section[9];
};

HashTable::HashTable()
{
	for (int i = 0; i < 9; ++i)
	{
		section[i] = NULL;
	}
}

HashTable::~HashTable()
{
	for (int i = 0; i < 9; ++i)
	{
		if (section[i] != NULL) 
		{
			delete section[i];
			section[i] = NULL;
		}	
	}
}

void HashTable::print()
{
	for (int i = 0; i < 9; ++i)
	{
		if (section[i] != NULL) section[i] -> print();
	}
}

void HashTable::insertNewElement(int key)
{
	int hashCode = getHashCode(key);

	//cout << hashCode << endl;

	if (hashCode < 0 || hashCode >= 9)
	{
		cout << "Hash Code Error" << endl;
		return ;
	}

	configureSlot(hashCode, key);
}

void HashTable::configure(int index)
{
	switch(index)
	{
		case 0:
			section[index] = new SlotList(0,0,1);
			break;
		case 2:
			section[index] = new SlotList(10,18,2);
			break;
		case 5:
			section[index] = new SlotList(0,0,1);
			break;
		case 7:
			section[index] = new SlotList(23,88,3);
			break;
	}
}

int HashTable::getHashCode(int key)
{
	int result = ((aFactor * key + bFactor) % pFactor) % 9;
	return result;
}

void HashTable::configureSlot(int index, int key)
{
	if (index < 0 || index >= 9) return;
	if (section[index] == NULL) configure(index);

	section[index]->insertNewElement(key);
}

int main()
{
	int test[] = {10,22,37,40,60,70,75};
	int size = sizeof(test) / sizeof(int);

	HashTable table;
	
	table.insertNewElement(10);
	table.insertNewElement(22);
	table.insertNewElement(37);
	table.insertNewElement(40);
	table.insertNewElement(60);
	table.insertNewElement(70);
	table.insertNewElement(75);

	table.print();

	return 0;
}

