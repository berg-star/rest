#include<stdio.h>
#include<stdlib.h>
//���ӱ�ʾ�� ��ǰ����Ӧ�ĺ�����˭
//һ�Զ�
typedef struct Child
{
	int data;//���������
	struct Child* next;//ָ����һ����� ָ����
}Node;


Node* node_array[20];
int size;//��ǰԪ�ظ���
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
		printf("���ڵ�Ϊ");
		printf("%d ", node_array[i]->data);
		Node* temp = node_array[i]->next;
		while (temp != NULL)
		{
			printf("���ӽ���Ϊ");
			printf("%d ", temp->data);
			temp = temp->next;
		}
		printf("\n");
	}
}


/*
��ʼ�� ���Ҹ��ڵ�
int key ���ڵ��ֵ
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
	���ڵ� 

int key 
	��ǰ����Ӧ�ĺ���
*/
void Great_Tree(int parent, int key)
{
	//���±�
	int index = find_parent(parent);
	if (index == -1)
	{

	}
	else
	{
		//�Ѻ�����Ϊ�µĽ����뵽���鵱��
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

