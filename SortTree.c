#include<stdio.h>
#include<stdlib.h>
/*二叉排序树代码实现*/
/*数据结构*/
typedef struct SortTree {
	struct SortTree* left, * right;
	int key;//存放数据
}Node;
/*全局变量*/
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

/*初始化一个根节点*/
void Init(int key)
{
	root = (Node*)malloc(sizeof(Node));
	root->key = key;
	root->left = NULL;
	root->right = NULL;
}

/*
二叉排序树的插入 永远是插入在叶子
要先找到应该在哪个结点的孩子进行插入
然后判断是这个结点的左孩子还是右孩子
*/
void insert(int key)
{
	Node* temp = root;//定义一个临时指针 方便移动
	Node* prev = NULL;//指向temp的前一个结点
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
			//当找到待删除结点的时候  要先找到他的前一个结点是谁
			Node* tempNode = prev_node(root, node, key);
			Node* temp;
			/*如果右子树为空 只需要重新连接结点
			如果是叶子结点 直接删除
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
				}//接下来要判断待删除结点是父亲结点的左孩子还是右孩子
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
				node = node->right;//要么指向右子树 要么指向NULL
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
			else//左右子树都不为空
			{
				temp = node;
				Node* s = node;//移动 找替换结点
				//找左子树的最大值
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
找到待删除结点的前一个结点
Node* root 根节点开始 起点
Node* node 待删除的结点 终点
int key 具体的值
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