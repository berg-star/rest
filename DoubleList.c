#include<stdio.h>
#include<stdlib.h>

typedef struct DoubleList {
	struct DoubleList* front;
	int element;//Êý¾ÝÓò
	struct DoubleList* next;
}List;

List* head;

void InitList()
{
	head = (List*)malloc(sizeof(List));
	head->next = head;
	head->front = head;
}

void head_insert(int key)
{
	List* new_node = (List*)malloc(sizeof(List));
	new_node->element = key;
	new_node->next = head->next;
	new_node->front = head;
	head->next->front = new_node;
	head->next = new_node;
}

int find(int key)
{
	List* temp = head->next;
	int i = 0;
	while (temp != head)
	{
		if (temp->element == key)
		{
			return i;
		}
		i++;
		temp = temp->next;

	}

	return -1;
}


void delete_node(int key)
{
	
	if (head == NULL)
	{
		
	}
	else
	{
		int index = find(key);
		if (index == -1)
		{

		}
		else
		{
			List* temp = head;
			int i = 0;
			while (i < index)
			{
				temp = temp->next;
				i++;
			}
			List* free_node = temp->next;
			temp->next->next->front = temp;
			temp->next = temp->next->next;
			free(free_node);
		}
	}
}