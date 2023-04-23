#include<stdio.h>
#include<stdlib.h>
typedef struct ChildBro {
	struct ChildBro* child;//孩子指针
	struct ChildBro* sibling;//兄弟指针
	int key;//数据
}Node;
Node* root;


//初始化根节点
void Init(int Key)
{
	root = (Node*)malloc(sizeof(Node));
	root->key = Key;
	root->child = NULL;
	root->sibling = NULL;
}

/*
int key
	当前结点

int parent
	当前结点的父亲
*/
void insert(int key, int parent)
{
	Node* tempNode = NULL;//先定位父节点是谁
	//查找父节点的位置
	if (tempNode == NULL)
	{

	}
	else 
	{
		if (tempNode->child == NULL)
		{
			Node* node = (Node*)malloc(sizeof(Node));
			node->key = key;
			node->child = NULL;
			node->sibling = NULL;
			tempNode->child = node;
		}
		else
		{
			tempNode = tempNode->child;
			Node* node = (Node*)malloc(sizeof(Node));
			node->key = key;
			node->child = NULL;
			node->sibling = NULL;
			node->sibling = tempNode->sibling;
			tempNode->sibling = node;
		}
	}
}