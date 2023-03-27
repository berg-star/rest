#include<stdio.h>
#include<stdlib.h>
/*˳��� ����*/
typedef struct ArrayList {
	int* list;//����
	int count;//��¼��ǰԪ�ظ���
	int maxSize;//������
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

//��ʼ��
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
˳�Ų���
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
		//��ʾ���� ����ֱ������
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
��ĳ��Ԫ��֮ǰ����
1������ʲôԪ��
2�����ĸ�˳������
3�����ĸ�Ԫ��֮ǰ����
*/
void insert_index(int key, List* list, int data)
{
	if (list->count < list->maxSize)
	{
		int index = find(list, data);
		if (index==-1)
		{
			//û�����Ԫ�� ��ʾ �˳�
			return;
		}
		else
		{
			//���ƶ�λ��
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
		//��ʾ���� ���� ����
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