#include<stdio.h>
#include<stdlib.h>


typedef struct Queue {
	int* queue;//队列数组
	int rear;//队尾指针
	int front;//队头指针
	int maxSize;//最大长度
}queue;

queue* initQueue()
{
	queue* list = (queue*)malloc(sizeof(queue));
	list->queue = (int*)malloc(sizeof(int) * 5);
	list->rear = list->front = 0;
	list->maxSize = 5;
	return list;
}

/*

插入队列
int key 待插入的元素

queue* list 需要插入哪个队列
*/
void insert_queue(int key,queue* list)
{
	if ((list->rear + 1 )%list->maxSize != list->front)
	{
		list->queue[list->rear] = key;
		list->rear = ((list->rear) + 1) % list->maxSize;
	}
	else
	{
		//满了
	}
}

void delete_queue(queue* list)
{
	if (list->front != list->rear)
	{
		list->front = ((list->front) + 1) % list->maxSize;
	}
	else {
		//队空 不能删
	}
}

//进行输出
void printf_queue(queue* list)
{
	//先拿到队头和队尾指针
	int temp_front = list->front;
	int temp_rear = list->rear;

	for (int i = temp_front; i != temp_rear ; i = (i + 1) % list->maxSize)
	{
		printf("%d ", list->queue[i]);
	}
	
}





