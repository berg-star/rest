#include<stdio.h>
#include<stdlib.h>
//孩子表示法 当前结点对应的孩子是谁
//一对多
typedef struct Child
{
	int data;//存放数据域
	struct Child* next;//指向下一个结点 指向孩子
}Node;


Node* node_array[20];
int size;//当前元素个数
void Init(int key);
void Great_Tree(int parent, int key);

int find_parent(int parent);

int main()
{
	Init(1);
	Great_Tree(1, 2);
	Great_Tree(1, 3);
	Great_Tree(1, 4);
	Great_Tree(2, 5);
	Great_Tree(2, 6);
	Great_Tree(3, 7);
	for (int i = 0; i < size; i++)
	{
		printf("父节点为");
		printf("%d ", node_array[i]->data);
		Node* temp = node_array[i]->next;
		while (temp != NULL)
		{
			printf("孩子结点点为");
			printf("%d ", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}


/*
初始化 给我根节点
int key 根节点的值
*/
void Init(int key)
{
	size = 0;
	node_array[size] = (Node*)malloc(sizeof(Node));
	node_array[size]->data = key;
	node_array[size]->next = NULL;
	size++;
}

/*
int parent
	父节点 

int key 
	当前结点对应的孩子
*/
void Great_Tree(int parent, int key)
{
	//找下标
	int index = find_parent(parent);
	if (index == -1)
	{

	}
	else
	{
		//把孩子作为新的结点加入到数组当中
		node_array[size] = (Node*)malloc(sizeof(Node));
		node_array[size]->data = key;
		node_array[size]->next = NULL;
		size++;

		Node* new_node = (Node*)malloc(sizeof(Node));
		new_node->data = key;
		new_node->next = node_array[index]->next;
		node_array[index]->next = new_node;
	}
	
	

}

int find_parent(int parent)
{
	for (int i = 0; i < size; i++)
	{
		if (node_array[i]->data == parent)
		{
			return i;
		}

	}
	return -1;
}

