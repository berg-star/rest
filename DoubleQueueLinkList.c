#include<stdio.h>
#include<stdlib.h>

typedef struct LinkQueue {
	int element;//数据
	struct LinkQueue* pre;
	struct LinkQueue* next;
}Node;

void InitQueue();
void left_push(int key);
void left_pop();
void right_push(int key);
void right_pop();

Node* middle;//中间节点
Node* left;
Node* right;

int main()
{
	InitQueue();
	right_push(1);
	right_push(2);
	right_push(3);
	Node* temp = middle->pre;
	while (temp != NULL)
	{ 
		printf("%d ", temp->element);
		temp = temp->pre;
	}
	printf("\n");
	left_pop();
	temp = middle->pre;
	while (temp != NULL)
	{
		printf("%d ", temp->element);
		temp = temp->pre; 
	}
}

void InitQueue()
{
	middle = (Node*)malloc(sizeof(Node));
	middle->next = NULL;
	middle->pre = NULL;
	left = middle;
	right = middle;
}

void left_push(int key)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->element = key;
	right->next = new_node;
	new_node->pre = right;
	new_node->next = NULL;
	right = right->next;
}

void left_pop()
{
	//如果右指针指向中间节点 代表右插左删形成队列
	//如果没有指向中间节点 代表左插左删形成栈
	if (right == middle)
	{
		Node* temp = right->pre;
		right->pre = right->pre->pre;
		right->pre->next = right;
		free(temp);
	}
	else 
	{
		Node* temp = right;
		right = right->pre;
		right->next = NULL;
		free(temp);
	}

}

void right_push(int key)
{
	Node* new_node = (Node*)malloc(sizeof(Node));
	new_node->element = key;
	left->pre = new_node;
	new_node->next = left;
	new_node->pre = NULL;
	left = left->pre;

}

void right_pop()
{
	//看左指针 如果左指针移动了 代表在进行右插右删
	//如果左指针没有动 在进行左插右删
	//先判断数据是否为空
	
	if (left == middle)
	{
		Node* temp = left->next;
		left->next = left->next->next;
		left->next->pre = left;
		free(temp);
	}
	else
	{
		Node* temp = left;
		left = left->next;
		left->pre = NULL;
		free(temp);
	}
}