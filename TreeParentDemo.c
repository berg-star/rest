#include<stdio.h>
#include<stdlib.h>
//当前结点对应的父亲是谁
//数据关系 1V1

typedef struct TreeNode {
	int data;//树中存放的数据
	int parent;//当前数据对应的父节点是谁 根节点的父节点-1

}Node;

Node* node[5];
int size;//当前元素个数

void Init(int key);
void insert_child(int key, int parent_node);
int find_parent(int parent);

int main()
{
	Init(5);
	insert_child(4, 5);
	insert_child(3, 4);
	printf("%d-------%d", node[2]->data, node[2]->parent);
}

void Init(int key)
{
	size = 0;
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->data = key;
	new_node->parent = -1;
	node[size] = new_node;
	size++;
}

/*
int key
	当前结点是谁 
int parent_node
	父节点是谁
*/
void insert_child(int key, int parent_node)
{
	if (size == 5)
	{

	}
	else
	{
		int parent_index = find_parent(parent_node);
		if (parent_index == -1)
		{
			return;
		}
		else 
		{
			Node* new_node = (Node*)malloc(sizeof(Node));
			new_node->data = key;
			new_node->parent = parent_index;
			node[size] = new_node; 
			size++;
		}

	}
}

int find_parent(int parent)
{
	for (int i = 0; i < size; i++)
	{
		if (node[i]->data == parent)
		{
			return i;
		}

	}
	return -1;
}



