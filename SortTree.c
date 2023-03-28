#include<stdio.h>
#include<stdlib.h>
/*��������������ʵ��*/
/*���ݽṹ*/
typedef struct SortTree {
	struct SortTree* left, * right;
	int key;//�������
}Node;
/*ȫ�ֱ���*/
Node* root;
void show(Node* root);
void Init(int key);
void insert(int key);
int delete_node(Node* node, int key);
Node* prev_node(Node* root, Node* node, int key);

int main()
{
	Init(3);
	insert(1);
	insert(2);
	show(root);
	delete_node(root, 3);
	show(root);
}

/*��ʼ��һ�����ڵ�*/
void Init(int key)
{
	root = (Node*)malloc(sizeof(Node));
	root->key = key;
	root->left = NULL;
	root->right = NULL;
}

/*
�����������Ĳ��� ��Զ�ǲ�����Ҷ��
Ҫ���ҵ�Ӧ�����ĸ����ĺ��ӽ��в���
Ȼ���ж�������������ӻ����Һ���
*/
void insert(int key)
{
	Node* temp = root;//����һ����ʱָ�� �����ƶ�
	Node* prev = NULL;//ָ��temp��ǰһ�����
	while (temp != NULL)
	{
		prev = temp;
		if (key < temp->key) {
			temp = temp->left;
		}else if (key > temp->key) {
			temp = temp->right;
		}
		else
		{
			return;
		}
	}

	if (key < prev->key)
	{
		prev->left = (Node*)malloc(sizeof(Node));
		prev->left->key = key;
		prev->left->left = NULL;
		prev->left->right = NULL;
	}
	else
	{
		prev->right = (Node*)malloc(sizeof(Node));
		prev->right->key = key;
		prev->right->left = NULL;
		prev->right->right = NULL;
	}

}


int delete_node(Node* node,int key)
{
	if (node == NULL)
	{
		return -1;
	}
	else
	{
		if (node->key == key)
		{
			//���ҵ���ɾ������ʱ��  Ҫ���ҵ�����ǰһ�������˭
			Node* tempNode = prev_node(root, node, key);
			Node* temp;
			/*���������Ϊ�� ֻ��Ҫ�������ӽ��
			�����Ҷ�ӽ�� ֱ��ɾ��
			*/
			if (node->right == NULL)
			{
				temp = node;
				node = node->left;
				if (temp == root)
				{
					temp->left = NULL;
					free(temp);
					root = node;
				}//������Ҫ�жϴ�ɾ������Ǹ��׽������ӻ����Һ���
				else if (tempNode->left != NULL && (tempNode->left->key == temp->key))
				{
					Node* free_node = temp;
					tempNode->left = node;
					free(free_node);
					free_node = NULL;
				}
				else
				{
					Node* free_node = temp;
					tempNode->right = node;
					free(free_node);
					free_node = NULL;
				}
			}
			else if (node->left == NULL)
			{
				temp = node;
				node = node->right;//Ҫôָ�������� Ҫôָ��NULL
				if (temp == root)
				{
					temp->right = NULL;
					free(temp);
					root = node;
				}if (tempNode->left != NULL && (tempNode->left->key == temp->key))
				{
					Node* free_node = temp;
					tempNode->right = node;
					free(free_node);
					free_node = NULL;
				}
				else
				{
					Node* free_node = temp;
					tempNode->left = node;
					free(free_node);
					free_node = NULL;
				}
			}
			else//������������Ϊ��
			{
				temp = node;
				Node* s = node;//�ƶ� ���滻���
				//�������������ֵ
				s = s->left;
				while (s->right != NULL)
				{
					temp = s;
					s = s->right;
				}
				node->key = s->key;
				if (temp != node)
				{
					temp->right = s->left;
					free(s);
				}
				else
				{
					temp->left = s->left;
					free(s);
				}
				

			}

		}
		else if (key < node->key)
		{
			delete_node(node->left, key);
		}
		else 
		{
			delete_node(node->right, key);
		}
	}
}

/*
�ҵ���ɾ������ǰһ�����
Node* root ���ڵ㿪ʼ ���
Node* node ��ɾ���Ľ�� �յ�
int key �����ֵ
*/
Node* prev_node(Node* root, Node* node, int key)
{
	if (root == NULL || root == node)
	{
		return node;
	}
	else 
	{
		if (root->right != NULL && root->right->key == key)
		{
			return root;
		}
		else if(root->left != NULL && root->left->key == key)
		{
			return root;
		}
		else if (key < root->key)
		{
			return prev_node(root->left, node, key);
		}
		else
		{
			return prev_node(root->right, node, key);
		}

	}
}

void show(Node* root)
{
	if (root == NULL)
	{
		return;
	}
	if (root->left != NULL)
	{
		show(root->left);
	}
	printf("%d", root->key);
	if (root->right != NULL)
	{
		show(root->right);
	}

}