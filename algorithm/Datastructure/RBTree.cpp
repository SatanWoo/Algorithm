//@Author:Ziqi Wu 
//        Tongji University 
//        2013-02-08

//@www.weibo.com/billgawu
//@www.facebook.com/billgawu

// 如果有很多不懂，可以参阅: http://blog.csdn.net/v_JULY_v/article/details/6105630

// 红黑树的最重要的5条条性质
// 1.根节点必须为黑色的
// 2.红节点不能和红节点相邻
// 3.从任何一个节点到分支的每一个节点上的黑点个数是一样的。
// 4.只存在红色或者黑色的节点
// 每个空节点都视为黑色节点

#include<iostream>
using namespace std;

enum nodeColor
 { 
 	black = 0,
 	red = 1,
 	undefined = 2
 };

//////////////////////////////////////////////////////////////////
struct Node
{
	int key;
	int color;

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
	color = undefined;
}

Node::Node(int data)
{
	key = data;
	left = NULL, right = NULL, parent = NULL; 
	color = undefined;
}

Node::~Node()
{
	key = 0;
	left = NULL, right = NULL, parent = NULL;
	color = undefined;
}

//////////////////////////////////////////////////////////////////
class RBTree
{
public:
	RBTree();
	RBTree(Node *r);
	~RBTree();

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

	void rotateLeft(Node *pivotNode);
	void rotateRight(Node *pivotNode);

	void insertFixUp(Node *node);
	void deleteFixUp(Node *node);

	void insertStepByStep(Node *node);
	void deleteStepByStep(Node *node);

	int searchMiniumData(Node *node);
	int searchMaxiumData(Node *node);

	void recursivePrintInPre(Node *node);
	void recursivePrintInMid(Node *node);
	void recursivePrintInPost(Node *node);

	void recursiveDeleteNode(Node *node);

	bool isNodeEmpty(Node *node) const{return node == NULL;}
	int nodeColor(Node *node) const{if (node == NULL) return undefined; return node->color;}
	Node *root;
};

RBTree::RBTree()
{
	root = NULL;
}

RBTree::RBTree(Node *r)
{
	root = r;
}

RBTree::~RBTree()
{
	recursiveDeleteNode(root);
}

void RBTree::printTreeInPre()
{
	recursivePrintInPre(root);
}

void RBTree::printTreeInMid()
{
	recursivePrintInMid(root);
}

void RBTree::printTreeInPost()
{
	recursivePrintInPost(root);
}

Node *RBTree::Search(int data)
{
	return searchTree(root, data);
}

void RBTree::insertData(int data)
{
	if (root == NULL)
	{
		root = new Node(data);

		// Case 1:遇到插入跟节点，直接涂成黑色就完事了。
		root->color = black;
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

	// 让新加入的节点变成红色
	newNode->color = red;
	insertFixUp(newNode);
}

void RBTree::deleteData(int data)
{
	Node *deleteNode = Search(data);

	if (deleteNode == NULL) return;

	bool isRoot = deleteNode == root;

	Node *parentNode = deleteNode->parent;
	Node *toFixNode = NULL;
	// 1.这种情况下，直接删除就可以了。因为不需要涉及到子节点的更改
	if (deleteNode->left == NULL && deleteNode->right == NULL)
	{
		if (parentNode != NULL)
		{
			if (deleteNode == parentNode->left) parentNode->left = NULL;
			else parentNode->right = NULL;
		} 
	
		if (isRoot) 
		{
			// Delete Case 2: 删除的节点直接是黑色的根，所以没关系，直接删除就可以了
			root = NULL;
			return ;
		}
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
	}

	toFixNode = deleteNode->left == NULL ? deleteNode->right : deleteNode->left;
	deleteFixUp(toFixNode);

	delete deleteNode, deleteNode = NULL; 
}

// Private Method
void RBTree::recursivePrintInPre(Node *node)
{
	if (node == NULL) return ;
	cout << node->key << endl;
	recursivePrintInPre(node->left);
	recursivePrintInPre(node->right);
}

void RBTree::recursivePrintInMid(Node *node)
{
	if (node == NULL) return ;
	recursivePrintInMid(node->left);
	cout << node->key << endl;
	recursivePrintInMid(node->right);
}

void RBTree::recursiveDeleteNode(Node *node)
{
	if (node == NULL) return ;
	recursiveDeleteNode(node->left);
	recursiveDeleteNode(node->right);
	delete node, node = NULL;
}

void RBTree::recursivePrintInPost(Node *node)
{
	if (node == NULL) return ;
	recursivePrintInPost(node->left);
	recursivePrintInPost(node->right);
	cout << node->key << endl;
}

Node *RBTree::searchTree(Node *node, int data)
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

int RBTree::searchMiniumData(Node *node)
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

int RBTree::searchMaxiumData(Node *node)
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

Node *RBTree::successorNode(Node *node)
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

void RBTree::rotateLeft(Node *pivotNode)
{
	Node *rightChild = pivotNode->right;
	if (rightChild == NULL) return;

	Node *parentNode = pivotNode->parent;
	if (parentNode != NULL)
	{
		if (pivotNode == parentNode->left)
			parentNode->left = rightChild;
		else 
			parentNode->right = rightChild;

		rightChild->parent = parentNode;
	}
	else
	{
		root = rightChild;
	}
	
	pivotNode->right = rightChild->left;
	rightChild->left->parent = pivotNode;

	pivotNode->parent = rightChild;
	rightChild->left = pivotNode;
}

void RBTree::rotateRight(Node *pivotNode)
{
	Node *leftChild = pivotNode->left;
	if (leftChild == NULL) return ;

	Node *parentNode = pivotNode->parent;
	if (parentNode != NULL)
	{
		if (pivotNode == parentNode->left)
			parentNode->left = leftChild;
		else 
			parentNode->right = leftChild;

		leftChild->parent = parentNode;
	}
	else
	{
		root = leftChild;
	}

	pivotNode->left = leftChild->right;
	leftChild->right->parent = pivotNode;

	pivotNode->parent = leftChild;
	leftChild->right = pivotNode;
}

void RBTree::insertFixUp(Node *node)
{
	if (node == NULL) return ;

	// Case 2:根据性质，没不允许黑色节点和黑色节点在一起，过关
	if (node->parent != NULL && node->parent->color == black) return ;

	// 下面是着重的三种情况
	while(!isNodeEmpty(node->parent) && node->parent->color == red)
	{
		if (!isNodeEmpty(node->parent) && !isNodeEmpty(node->parent->parent))
		{
			Node *parentNode = node->parent;
			Node *grandParentNode = node->parent->parent;
			Node *uncleNode = parentNode == grandParentNode->left ? grandParentNode->right : grandParentNode->left;

			// Case 3: 当前节点的父节点是红色并且叔叔节点（祖父的另一个节点）是红色并且是左子树的情况
			if (uncleNode->color == red && parentNode->color == red)
			{
				parentNode->color = black;
				uncleNode->color = black;
				grandParentNode->color = red;
				node = grandParentNode;
			}

			// Case 4:当前节点的父节点是红色，叔叔是黑色，并且当前节点是父节点的右子树或者左子树情况
			if (uncleNode->color == black && parentNode->color == red && node == parentNode->right)
			{
				rotateLeft(parentNode);
				node = parentNode;
			}

			// Case 5:当前节点的父节点是红色，叔叔是黑色，并且当前节点是父节点的左子树
			if (uncleNode->color == black && parentNode->color == red && node == parentNode->left)
			{
				parentNode->color = black;
				grandParentNode->color = red;
				rotateRight(grandParentNode);
			}
		}
	}
}

void RBTree::deleteFixUp(Node *node)
{	
	// 一定要理解额外一种黑色的含义
	
	while(node != root && node->color == black)
	{
		// Delete Case 3:如果当前节点的兄弟节点为红色，则改变父节点颜色和兄弟节点颜色，并旋转
		Node *parentNode = node->parent;
		Node *siblingNode = node == parentNode->left ? parentNode->right : parentNode->left;

		if (siblingNode->color == red)
		{
			parentNode->color = red;
			siblingNode->color = black;
			if (siblingNode == parentNode->left)
				rotateRight(parentNode);
			else
				rotateLeft(parentNode);

			node = siblingNode;
		}

		// Delete Case 4:如果当前节点的兄弟节点为黑色，且兄弟节点的两个子节点都是黑色
		else if (nodeColor(siblingNode) == black && nodeColor(siblingNode->left) == black && nodeColor(siblingNode->right) == black)
		{
			siblingNode->color = red;
			parentNode->color = black;
			node = parentNode;
		}

		// Delete Case 5:如果当前节点的兄弟节点为黑色，且兄弟节点的两个子节点左节点是红色，有节点是黑色
		else if (nodeColor(siblingNode) == black && nodeColor(siblingNode->left) == red && nodeColor(siblingNode->right) == black)
		{
			siblingNode->color = red;
			siblingNode->left->color = black;

			rotateRight(siblingNode);
		}

		// Delete Case 6:如果当前节点的兄弟节点为黑色，兄弟的右节点是红色
		else if (nodeColor(siblingNode) == black && nodeColor(siblingNode->right) == red)
		{
			siblingNode->color = nodeColor(parentNode);
			parentNode->color = black;
			rotateLeft(parentNode);
			node == root;
		}
	}

	// Delete Case 1: 如果这个节点是红色的，直接诶染成黑色就行了
	node->color = black;
}

//////////////////////////////////////////////////////////////////

int main()
{
	return 0;
}