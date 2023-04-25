#include<stdio.h>
#include<stdlib.h>
#define RED 0
#define BLACK 1
/*���ݼ��� */
typedef struct RBTreeNode {
	char color;//��ɫ���ߺ�ɫ
	struct RBTreeNode* left;
	struct RBTreeNode* right;
	int key;
	struct RBTreeNode* parent;//���ڵ�
	int count;//��¼�ظ����ݵĸ���
}Node, *RBTree;

//����һ�����ڵ�
typedef struct tb_root {
	Node* root;
}RBRoot;
/*��������*/
RBRoot* creat_rbtree();
int insert_rbtree(int key,RBRoot* root);
Node* search(int key, Node* root);
int rbtree_insert(RBRoot* root, Node* node);
void rbtree_insert_fixup(RBRoot* root,Node*node);
void rbtree_left_rotate(RBRoot* root, Node* x);
void rbtree_right_rotate(RBRoot* root, Node* y);
void rbtree_delete_fixup(RBRoot* root, Node* child, Node* parent);


void rbtree_right_rotate(RBRoot* root, Node* y)
{
	//���ҵ���ǰ������
	Node* x = y->left;
	//��x���Һ��ӱ��y������
	y->left = x->right;
	if (x->right != NULL)
	{
		x->right->parent = y;
	}

	x->parent = y->parent;
	if (y->parent == NULL)
	{
		root->root = x;
	}
	else
	{
		if (y == y->parent->right)
		{
			y->parent->right = x;
		}
		else
		{
			y->parent->left = x;
		}
	}

	x->right = y;
	y->parent = x;


}


//�Ժ������x����������
void rbtree_left_rotate(RBRoot* root, Node* x)
{
	Node* y = x->right;

	//��y����������Ϊx���Һ���
	//���y�����ӷǿ� 
	x->right = y->left;
	if (y->left!= NULL)
	{
		y->left->parent = x;
	}

	y->parent = x->parent;
	if (x->parent == NULL)
	{
		root->root = y;
	}
	else
	{
		if (x->parent->left == x)
		{
			x->parent->left = y;
		}
		else
		{
			x->parent->right = y;
		}
	}

	y->left = x;
	x->parent = y;

}


Node* creat_node(char color, struct RBTreeNode* left, struct RBTreeNode* right, struct RBTreeNode* parent,int key)
{
	Node* node = (Node*)malloc(sizeof(Node));
	node->color = color;
	node->key = key;
	node->left = left;
	node->right = right;
	node->parent = parent;
	return node;
}

Node* search(int key, RBTree root)
{
	if (root == NULL || root->key == key )
	{
		return root;
	}

	if (key < root->key)
	{
		return search(key, root->left);
	}
	else
	{
		return search(key, root->right);
	}
}




/*����һ�ſ��� ���غ�����ĸ�*/
RBRoot* creat_rbtree()
{
	RBRoot* node = (RBRoot*)malloc(sizeof(RBRoot));
	node->root = NULL;
	return node;
	
}
/*
����ֵ�����жϲ���ɹ�����ʧ�� �����������жϣ�
int key
	������Ĺؼ�

RBRoot* root
	��������ǿ���

�������ظ�����/���Խ����ظ����ݵ���д
*/
int insert_rbtree(int key, RBRoot* root)
{
	//���� 
	if (search(key,root->root) != NULL)
	{
		//�������Ѿ�����
		//root->root->count++;
	}
	else
	{
		//���� �����µĽ��
		Node* node = creat_node(RED, NULL, NULL, NULL, key);

		//������� ִ�в���
		rbtree_insert(root, node);
	}
}

/*
���������������
*/
void rbtree_insert_fixup(RBRoot* root, Node* node)
{
	Node* parent = NULL, * gparent;
	//������ڵ���� ������ɫ�Ǻ�ɫ
	while ( (parent = node->parent) && parent->color == RED)
	{
		gparent = parent->parent;
		//������ڵ����游��������
		if (parent == gparent->left)
		{
			//case 1:��������һ����ɫ��
			Node* uncle = gparent->right;
			if (uncle && uncle == RED)
			{
				uncle->color = BLACK;
				parent->color = BLACK;
				gparent->color = RED;
				node = gparent;
				continue;
			}
			//case 2: ��������Ǻ�ɫ �ҵ�ǰ������Һ���
			if (parent->right == node)
			{
				Node* temp;
				//����
				rbtree_left_rotate(root,parent);
				temp = parent;
				parent = node;
				node = temp;
			}

			//��������Ǻ�ɫ �ҵ�ǰ���������
			//����
			parent->color = BLACK;
			gparent->color = RED;
			rbtree_right_rotate(root, gparent);
		}
		else//���ڵ����游�����Һ��ӵ����
		{
			//case 1:��������һ����ɫ��
			Node* uncle = gparent->left;
			if (uncle && uncle == RED)
			{
				uncle->color = BLACK;
				parent->color = BLACK;
				gparent->color = RED;
				
				node = gparent;
				continue;
			}

			//case 2: ��������Ǻ�ɫ �ҵ�ǰ���������
			if (parent->left == node)
			{
				Node* temp;
				//����
				rbtree_right_rotate(root, parent);
				temp = parent;
				parent = node;
				node = temp;
			}

			//��������Ǻ�ɫ �ҵ�ǰ���������
			//����
			parent->color = BLACK;
			gparent->color = RED;
			rbtree_left_rotate(root, gparent);

		}
	}

	root->root->color = BLACK;
}


int rbtree_insert(RBRoot* root, Node* node)
{

	Node* x = root->root;
	Node* y = NULL;//������ ��λ��������λ��
	
	while (x != NULL)
	{
		y = x;
		if (x->key < node->key )
		{
			x = x->right;
		}
		else
		{
			x = x->left;
		}
	}

	node->parent = y;

	if (y != NULL)
	{
		if (node->key < y->key)
		{
			y->left = node;
		}
		else
		{
			y->right = node;
		}
	}
	else
	{
		root->root = node;
	}

	node->color = RED;

	//��ʼ��������
	rbtree_insert_fixup(root,node);
}

//ɾ������������
/*
Node* node �������Ľ��
*/
void rbtree_delete_fixup(RBRoot* root, Node* node, Node* parent)
{
	Node* other;

	while ((!node || node->color == BLACK) && node != root->root)
	{
		if (parent->left == node)
		{
			other = parent->right;

			if (other->color == RED)
			{
				//case1 : x���ֵ��Ǻ�ɫ��
				other->color == BLACK;
				parent->color == RED;
				rbtree_left_rotate(root, parent);
				other = parent->right;
			}
			//�ֵ��Ǻ�ɫ �������Ƕ��Ǻ�ɫ
			if ( (!other->left || other->left->color == BLACK)
				&& (!other->right || other->right->color == BLACK))
			{
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				//�ֵ��Ǻ�ɫ �����Ǻ�ɫ �Һ����Ǻ�ɫ
				if (!other->right || other->right->color == BLACK)
				{
					other->left->color = BLACK;
					other->color = RED;
					rbtree_right_rotate(root, other);
					other = parent->right;
				}

				//�ֵ��Ǻ�ɫ �Һ����Ǻ�ɫ ����
				other->color = parent->color;
				parent->color = BLACK;
				other->right->color = BLACK;
				rbtree_left_rotate(root, parent);
				node = root->root;
				break;
			}




		}
		else
		{
			other = parent->left;

			if (other->color == RED)
			{
				//case1 : x���ֵ��Ǻ�ɫ��
				other->color == BLACK;
				parent->color == RED;
				rbtree_right_rotate(root, parent);
				other = parent->left;
			}
			if ((!other->left || other->left->color == BLACK)
				&& (!other->right || other->right->color == BLACK)
				)
			{
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				if (!other->left || other->left->color == BLACK)
				{
					other->right->color = BLACK;
					other->color = RED;
					rbtree_left_rotate(root, other);
					other = parent->left;
				}

				//�ֵ��Ǻ�ɫ �Һ����Ǻ�ɫ ���Ӻ�ɫ
				other->color = parent->color;
				parent->color = BLACK;
				other->left->color = BLACK;
				rbtree_right_rotate(root, parent);
				node = root->root;
				break;
			}
		}

	}

	if (node)
	{
		node->color = BLACK;
	}

}



void rbtree_delete(RBRoot* root, Node* node)
{
	Node* child,* parent;
	int color;
	//��׼����������ɾ��
	if ((node->left != NULL) && (node->right != NULL))
	{
		//�ҵ���ɾ�����ĺ��/ǰ��
		Node* replace = node;//������

		replace = node->right;
		while (replace->left != NULL)
		{
			replace = node->left;
		}

		if (node->parent != NULL)
		{
			if (node->parent->left == node)
			{
				node->parent->left = replace;
			}
			else
			{
				node->parent->right = replace;
			}

		}
		else
		{
			//���¸��ڵ�
			root->root = replace;
		}
		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		//��ɾ����������ĺ�̽��ĸ��ڵ�
		if (parent == node)
		{
			parent = replace;
		}
		else
		{
			if (child)
			{
				child->parent = parent;
			}
			parent->left = child;
			replace->right = node->right;
			node->right->parent = replace;
		}

		replace->parent = node->parent;
		replace->color = node->color;
		replace->left = node->left;
		node->left->parent = replace;

		if (color == BLACK)//
		{
			//����
			rbtree_delete_fixup(root,child,parent);
		}
		free(node);
		return;
	}

	if (node->left != NULL)
	{
		child = node->left;
	}
	else 
	{
		child = node->right;
	}

	parent = node->parent;

	color = node->color;

	if (child)
	{
		child->parent = parent;
	}

	//���node���Ǹ��ڵ�
	if (parent)
	{
		if (parent->left == node)
		{
			parent->left = child;
		}
		else
		{
			parent->right = child;
		}

	}
	else
	{
		root->root = child;
	}


	if (color == BLACK)
	{
		rbtree_delete_fixup(root, child, parent);

	}
	free(node);

}

void delete_rbtree(RBRoot* root, int key)
{

	Node* z;
	if ((z = search(key,root->root) )!= NULL)
	{
		//ִ��ɾ��
		rbtree_delete(root,z);
	}
	else 
	{
		//û�����ֵ �޷�ɾ��
	}
}


void inorder(RBTree tree)
{
	if (tree != NULL)
	{
		inorder(tree->left);
		printf("%d ", tree->key);
		inorder(tree->right);
	}
}

void inorder_rbtree(RBRoot* root)
{
	if (root)
	{
		inorder(root->root);
		printf("\n ");
	}
}


void main()
{
	int a[] = { 10,40,30,60,90,70,20,50,80 };
	RBRoot* root = NULL;
	root = creat_rbtree();
	for (int i = 0; i < 9; i++)
	{
		insert_rbtree(a[i], root);

	}

	
	inorder_rbtree(root);
	delete_rbtree(root, 80);
	delete_rbtree(root, 60);
	delete_rbtree(root, 50);
	delete_rbtree(root, 10);
	delete_rbtree(root, 70);
	delete_rbtree(root, 90);
	delete_rbtree(root, 20);
	delete_rbtree(root, 30);
	inorder_rbtree(root);
	

}

