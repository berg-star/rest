#include<stdio.h>
#include<stdlib.h>
#define Size 5
/*ȫ�ֱ���*/
int* queue;//���е�˳���
int left;
int right;
int maxSize;//��ǰ���Ԫ�ظ���
int size;//��ǰԪ�ظ���



void InitQueue()
{
	queue = (int*)malloc(Size * sizeof(int));
	maxSize = Size;
	size = 0;
}

int isEmpty()
{
	if (size == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//
int isFull()
{
	if (size == maxSize)
	{
		return 1;//����
	}
	else
	{
		return 0;
	}
}

void insert_left(int key)
{
	i = 0;
	if (isFull())
	{
		//���� ����ʧ��
	}
	else 
	{
		if (isEmpty())
		{
			left = right = 0;
			queue[left] = key;
		}
		else
		{
			if (left == 0)
			{
				left = maxSize;
			}
			left--;
			queue[left] = key;
		}
		size++;
	}
}

void delete_left()
{
	if (isEmpty())
	{

	}
	else 
	{
		if (left == maxSize-1)
		{
			printf("��ɾ����Ԫ��Ϊ%d\n", queue[left]);
			left = 0;
			size--;

		}
		else
		{
			printf("��ɾ����Ԫ��Ϊ%d\n", queue[left]);
			left++;
			size--;
		}
	}
}

void insert_right(int key)
{
	if (isFull())
	{

	}
	else
	{
		if (isEmpty())
		{
			left = right = 0;
			queue[right] = key;
		}
		else
		{
			if (right == maxSize- 1)
			{
				right = -1;
			}
			right++;
			queue[right] = key;
		}
		size++;
	}
}

void delete_right()
{
	if (isEmpty())
	{

	}
	else
	{
		if (right == 0)
		{
			printf("��ɾ����Ԫ��Ϊ%d\n", queue[right]);
			right = maxSize-1;
			size--;
		}
		else {
			printf("��ɾ����Ԫ��Ϊ%d\n", queue[right]);
			right--;
			size--;
		}
	}
}

void printf_queue()
{
	//ͨ���Ǹ�������ָ�� �����б���
	//ͨ���ж���廹���Ҳ����ж�
	int temp_front = right;
	int temp_rear = left;

	int count = 0;
	while (count < size)
	{
		if (temp_front < 0)
		{
			temp_front = maxSize - 1;
		}
		printf("%d", queue[temp_front]);
		temp_front--;
		count++;
	}
}