#include<stdio.h>
#include<stdlib.h>
typedef struct ChildBro {
	struct ChildBro* child;//����ָ��
	struct ChildBro* sibling;//�ֵ�ָ��
	int key;//����
}Node;
Node* root;


//��ʼ�����ڵ�
void Init(int Key)
{
	root = (Node*)malloc(sizeof(Node));
	root->key = Key;
	root->child = NULL;
	root->sibling = NULL;
}

/*
int key
	��ǰ���

int parent
	��ǰ���ĸ���
*/
void insert(int key, int parent)
{
	Node* tempNode = NULL;//�ȶ�λ���ڵ���˭
	//���Ҹ��ڵ��λ��
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