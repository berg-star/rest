#include<stdio.h>
#include<stdlib.h>
/*顺序表 数组*/
typedef struct ArrayList {
	int* list;//数组
	int count;//记录当前元素个数
	int maxSize;//总容量
}List;
List* initList();
void insert(int key, List* list);
int find(List* list, int key);
void insert_index(int key, List* list, int data);
void printfList(List* list);
void delete_list(int key, List* list);

int main()
{
	List* list = initList();
	insert(1, list);
	insert(2, list);
	insert(3, list);
	insert(4, list);
	insert(5, list);
	insert(6, list);
	printfList(list);
	
}

//初始化
List* initList()
{
	List* list = (List*)malloc(sizeof(List));
	list->count = 0;
	list->maxSize = 5;
	list->list = (int*)malloc(sizeof(int) * 5);
	return list;
}


void enlargement(List* list)
{
	int* temp = (int*)malloc(sizeof(int) * (list->maxSize + 5));
	for (int i = 0; i < list->maxSize; i++)
	{
		temp[i] = list->list[i];
	}
	int* arrytemp = list->list;
	list->list = temp;
	list->maxSize = list->maxSize + 5;
	free(arrytemp);
}


/*
顺着插入
*/
void insert(int key, List* list)
{
	if (list->count < list->maxSize)
	{
		list->list[list->count] = key;
		list->count++;
	}
	else
	{
		//提示满了 或者直接扩容
		enlargement(list);
		list->list[list->count] = key;
		list->count++;
	}
}


int find(List* list, int key)
{
	for (int i = 0; i < list->count; i++)
	{
		if (list->list[i] == key)
		{
			return i;
		}
	}

	return -1;
}

/*
在某个元素之前插入
1、插入什么元素
2、在哪个顺序表插入
3、在哪个元素之前插入
*/
void insert_index(int key, List* list, int data)
{
	if (list->count < list->maxSize)
	{
		int index = find(list, data);
		if (index==-1)
		{
			//没有这个元素 提示 退出
			return;
		}
		else
		{
			//先移动位置
			for (int i = list->count; i > index; i--)
			{
				list->list[i] = list->list[i - 1];
			}
			list->list[index] = key;
			list->count++;
		}
	}
	else 
	{
		//提示满了 或者 扩容
	}
}


void printfList(List* list)
{
	for (int i = 0; i < list->count; i++)
	{
		printf("%d ", list->list[i]);
	}

	printf("\n");
}

void delete_list(int key, List* list)
{
	if (list->count == 0)
	{
		return;
	}
	else 
	{
		int index = find(list, key);
		if (index == -1)
		{
			return;
		}
		else
		{
			for (int i = index; i < list->count; i++)
			{
				list->list[i] = list->list[i + 1];
			}
			list->count--;
		}
	}
}