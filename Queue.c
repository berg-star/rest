#include<stdio.h>
#include<stdlib.h>


typedef struct Queue {
	int* queue;//��������
	int rear;//��βָ��
	int front;//��ͷָ��
	int maxSize;//��󳤶�
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

�������
int key �������Ԫ��

queue* list ��Ҫ�����ĸ�����
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
		//����
	}
}

void delete_queue(queue* list)
{
	if (list->front != list->rear)
	{
		list->front = ((list->front) + 1) % list->maxSize;
	}
	else {
		//�ӿ� ����ɾ
	}
}

//�������
void printf_queue(queue* list)
{
	//���õ���ͷ�Ͷ�βָ��
	int temp_front = list->front;
	int temp_rear = list->rear;

	for (int i = temp_front; i != temp_rear ; i = (i + 1) % list->maxSize)
	{
		printf("%d ", list->queue[i]);
	}
	
}





