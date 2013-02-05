//@Author:Ziqi Wu 
//        Tongji University 
//        2013-02-05

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu

//二叉查找树最麻烦的事情是删除节点。
//需要判断三种情况，如果没有子孩子。直接删除就好啦。
//如果有一个孩子，不管事左还是右孩子，
//如果是两个孩子，则

#include<iostream>
using namespace std;

//////////////////////////////////////////////////////////////////
struct Node
{
	int key;
	Node *left;
	Node *right;
	Node *parent;

	Node();
	Node(int data);
	~Node();
};

Node::Node()
{
	key = 0;
	left = NULL, right = NULL, parent = NULL;
}

Node::Node(int data)
{
	key = data;
	left = NULL, right = NULL, parent = NULL; 
}

Node::~Node()
{
	key = 0;
	left = NULL, right = NULL, parent = NULL;
}

//////////////////////////////////////////////////////////////////
class BinaryTree
{
public:
	BinaryTree();
	BinaryTree(Node *r);
	~BinaryTree();

	void insertData(int data);
	void deleteData(int data);

	Node *Search(int data);

	void printTreeInPre();
	void printTreeInMid();
	void printTreeInPost();

	int miniumData(){return searchMiniumData(root);}
	int maxiumData(){return searchMaxiumData(root);}
private:
	Node *searchTree(Node *node, int data);
	Node *successorNode(Node *node);

	int searchMiniumData(Node *node);
	int searchMaxiumData(Node *node);

	void recursivePrintInPre(Node *node);
	void recursivePrintInMid(Node *node);
	void recursivePrintInPost(Node *node);

	void recursiveDeleteNode(Node *node);

	Node *root;
};

BinaryTree::BinaryTree()
{
	root = NULL;
}

BinaryTree::BinaryTree(Node *r)
{
	root = r;
}

BinaryTree::~BinaryTree()
{
	recursiveDeleteNode(root);
}

void BinaryTree::printTreeInPre()
{
	recursivePrintInPre(root);
}

void BinaryTree::printTreeInMid()
{
	recursivePrintInMid(root);
}

void BinaryTree::printTreeInPost()
{
	recursivePrintInPost(root);
}

Node *BinaryTree::Search(int data)
{
	return searchTree(root, data);
}

void BinaryTree::insertData(int data)
{
	if (root == NULL)
	{
		root = new Node(data);
		return ;
	}

	Node *temp = root;
	Node *parentNode = NULL;
	while(temp != NULL)
	{
		parentNode = temp;
		if (temp->key > data) temp = temp->left;
		else temp = temp->right;
	}

	Node *newNode = new Node(data);
	newNode->parent = parentNode;
	if (data > parentNode->key) parentNode->right = newNode;
	else parentNode->left = newNode;
}

void BinaryTree::deleteData(int data)
{
	Node *deleteNode = Search(data);

	if (deleteNode == NULL) return;

	bool isRoot = deleteNode == root;

	Node *parentNode = deleteNode->parent;
	// 1.这种情况下，直接删除就可以了。因为不需要涉及到子节点的更改
	if (deleteNode->left == NULL && deleteNode->right == NULL)
	{

		if (parentNode != NULL)
		{
			if (deleteNode == parentNode->left) parentNode->left = NULL;
			else parentNode->right = NULL;
		} 
		delete deleteNode, deleteNode = NULL; 

		if (isRoot) root = NULL;
	}
	// 2.这种情况最复杂，要上移指针。慢慢讨论
	else if (deleteNode->left != NULL && deleteNode->right != NULL)
	{
		Node *successor = successorNode(deleteNode);
		int key = successor->key;
		deleteData(key);
		deleteNode->key = key;
	}
	// 3.这种情况是有一个子节点需要考虑的
	else
	{
		if (isRoot)
		{
			if (deleteNode->left != NULL) deleteNode = deleteNode->left;
			else deleteNode = deleteNode->right;

			int key = deleteNode->key;
			deleteData(key);
			root->key = key;
			return ;
		}

		if (deleteNode->left != NULL)
		{
			deleteNode->left->parent = parentNode;
			if (deleteNode == parentNode->left) parentNode->left = deleteNode->left;
			else parentNode->right = deleteNode->left;
		}
		else 
		{
			deleteNode->right->parent = parentNode;
			if (deleteNode == parentNode->left) parentNode->left = deleteNode->right;
			else parentNode->right = deleteNode->right;	
		}

		delete deleteNode, deleteNode = NULL;
		
	}
}

// Private Method
void BinaryTree::recursivePrintInPre(Node *node)
{
	if (node == NULL) return ;
	cout << node->key << endl;
	recursivePrintInPre(node->left);
	recursivePrintInPre(node->right);
}

void BinaryTree::recursivePrintInMid(Node *node)
{
	if (node == NULL) return ;
	recursivePrintInMid(node->left);
	cout << node->key << endl;
	recursivePrintInMid(node->right);
}

void BinaryTree::recursiveDeleteNode(Node *node)
{
	if (node == NULL) return ;
	recursiveDeleteNode(node->left);
	recursiveDeleteNode(node->right);
	delete node, node = NULL;
}

void BinaryTree::recursivePrintInPost(Node *node)
{
	if (node == NULL) return ;
	recursivePrintInPost(node->left);
	recursivePrintInPost(node->right);
	cout << node->key << endl;
}

Node *BinaryTree::searchTree(Node *node, int data)
{
	Node *temp = node;
	bool found = false;
	while(temp != NULL && found == false) 
	{
		if (temp->key < data) temp = temp->right;
		else if (temp->key > data) temp = temp->left;
		else found = true; 
	}

	if (found == false)
	{
		cout << "Not Found Data" << endl;
		return NULL;
	} 
	else 
		return temp; 
}

int BinaryTree::searchMiniumData(Node *node)
{
	Node *temp = node;
	while(temp->left != NULL)
	{
		temp = temp->left;
	}

	if (temp == NULL)
	{
		cout << "No Minuium Data" <<endl;
		return -1;
	}
	return temp->key;
}

int BinaryTree::searchMaxiumData(Node *node)
{
	Node *temp = node;
	while(temp->right != NULL)
	{
		temp = temp->right;
	}

	if (temp == NULL)
	{
		cout << "No Maxium Data" <<endl;
		return -1;
	}
	return temp->key;
}

Node *BinaryTree::successorNode(Node *node)
{
	if (node == NULL)
	{
		cout << "Null Node Error" << endl;
		return NULL;
	}

	Node *temp = node;
	if (temp->right != NULL) return searchTree(temp, searchMiniumData(temp));

	Node *parentNode = temp->parent;
	while(parentNode != NULL && temp == parentNode->right)
	{
		temp = parentNode;
		parentNode = parentNode->parent;
	}

	return parentNode;
}

//////////////////////////////////////////////////////////////////
int main()
{
	/* Demo Usage*/

	BinaryTree tree;	
	tree.insertData(5);
	// tree.insertData(19);
	// tree.insertData(3);
	// //tree.printTreeInMid();
	// //tree.printTreeInPost();

	// //tree.printTreeInMid();

	// //tree.Search(3);
	// //cout << tree.Search(3)->key;

	// //cout << tree.maxiumData();
	// tree.deleteData(3);
	// tree.insertData(6);
	// tree.printTreeInMid();
	tree.deleteData(5);
	tree.insertData(6);
	tree.insertData(3);
	tree.insertData(19);
	tree.deleteData(6);
	tree.insertData(50);

	tree.printTreeInPost();

	return 0;
}