//@Author:Ziqi Wu 
//        Tongji University 
//        2013-01-24

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu

#include<iostream>
using namespace std;
struct Node 
{
	int data;
	Node *next;
	Node(int d);
	Node();
} ;

Node::Node()
{
	data = 0;
	next = NULL;
}

Node::Node(int d)
{
	data = d;
	next = NULL;
}

void print(Node **ar, int sectionIndex, int *result);
void bucketSort(Node **ar, int *data, int size, int index);
void insertBucketSort(Node **ar, int data, int section);

int main()
{
	int test[] = {78,17,39,26,72,94,21,12,23,68};
	int size = sizeof(test) / sizeof(int);

	Node **array = new Node *[size];
	for (int i = 0; i < size; ++i)
	{
		array[i] = NULL;
	}

	for (int i = 0; i < size; ++i)
	{
		bucketSort(array, test, size, i);
	}

	for (int i = 0; i < size; ++i)
	{
		print(array, i, test);
	}

	for (int i = 0; i < size; ++i)
	{
		cout << test[i] << endl;
	}
	

	delete [] array;
	return 0;
}

void print(Node **ar, int sectionIndex, int* result)
{
	static int inputIndex = 0;
	Node *temp = ar[sectionIndex];
	while(temp)
	{
		result[inputIndex++] = temp->data;
		temp = temp -> next;
	}
}

void bucketSort(Node **ar, int *data, int size, int index)
{
	if (index >= size || index < 0) return;

	int section = data[index] / size;
	section = section < 0 ? 0 : section;
	section = section < size ? section : (size - 1);
	insertBucketSort(ar, data[index], section);
}

void insertBucketSort(Node **ar, int data, int section)
{
	Node *headNode = ar[section];

	if (ar[section] == NULL) 
	{
		ar[section] = new Node(data);
	}	
	else if (headNode->data > data)
	{
		Node *node = new Node(headNode->data);
		headNode->data = data;
		headNode->next = node;
	}
	else 
	{
		Node *preNode = ar[section];
		Node *currentNode = ar[section] -> next;
		bool isInserted = false;

		while(currentNode) {
			if (currentNode->data > data)
			{
				Node *newNode = new Node(data);
				newNode->next = currentNode;
				preNode->next = newNode;

				isInserted = true;
				break;
			}
			currentNode = currentNode->next;
			preNode = preNode -> next;
		}

		if (!isInserted) currentNode->next = new Node(data);
	}
}