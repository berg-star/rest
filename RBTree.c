#include<stdio.h>
#include<stdlib.h>
#define RED 0
#define BLACK 1
/*数据集合 */
typedef struct RBTreeNode {
	char color;//红色或者黑色
	struct RBTreeNode* left;
	struct RBTreeNode* right;
	int key;
	struct RBTreeNode* parent;//父节点
	int count;//记录重复数据的个数
}Node, *RBTree;

//设置一个根节点
typedef struct tb_root {
	Node* root;
}RBRoot;
/*操作集合*/
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
	//先找到当前的左孩子
	Node* x = y->left;
	//将x的右孩子变成y的左孩子
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


//对红黑树的x结点进行左旋
void rbtree_left_rotate(RBRoot* root, Node* x)
{
	Node* y = x->right;

	//将y的左孩子设置为x的右孩子
	//如果y的左孩子非空 
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




/*建立一颗空树 返回红黑树的根*/
RBRoot* creat_rbtree()
{
	RBRoot* node = (RBRoot*)malloc(sizeof(RBRoot));
	node->root = NULL;
	return node;
	
}
/*
返回值用来判断插入成功或者失败 （方法里面判断）
int key
	待插入的关键

RBRoot* root
	待插入的那颗树

不允许重复数据/可以进行重复数据的书写
*/
int insert_rbtree(int key, RBRoot* root)
{
	//查找 
	if (search(key,root->root) != NULL)
	{
		//该数据已经有了
		//root->root->count++;
	}
	else
	{
		//首先 创建新的结点
		Node* node = creat_node(RED, NULL, NULL, NULL, key);

		//创建完成 执行插入
		rbtree_insert(root, node);
	}
}

/*
红黑树的修正函数
*/
void rbtree_insert_fixup(RBRoot* root, Node* node)
{
	Node* parent = NULL, * gparent;
	//如果父节点存在 并且颜色是红色
	while ( (parent = node->parent) && parent->color == RED)
	{
		gparent = parent->parent;
		//如果父节点是祖父结点的左孩子
		if (parent == gparent->left)
		{
			//case 1:叔叔结点是一个红色的
			Node* uncle = gparent->right;
			if (uncle && uncle == RED)
			{
				uncle->color = BLACK;
				parent->color = BLACK;
				gparent->color = RED;
				node = gparent;
				continue;
			}
			//case 2: 如果叔叔是黑色 且当前结点是右孩子
			if (parent->right == node)
			{
				Node* temp;
				//左旋
				rbtree_left_rotate(root,parent);
				temp = parent;
				parent = node;
				node = temp;
			}

			//如果叔叔是黑色 且当前结点是左孩子
			//右旋
			parent->color = BLACK;
			gparent->color = RED;
			rbtree_right_rotate(root, gparent);
		}
		else//父节点是祖父结点的右孩子的情况
		{
			//case 1:叔叔结点是一个红色的
			Node* uncle = gparent->left;
			if (uncle && uncle == RED)
			{
				uncle->color = BLACK;
				parent->color = BLACK;
				gparent->color = RED;
				
				node = gparent;
				continue;
			}

			//case 2: 如果叔叔是黑色 且当前结点是左孩子
			if (parent->left == node)
			{
				Node* temp;
				//左旋
				rbtree_right_rotate(root, parent);
				temp = parent;
				parent = node;
				node = temp;
			}

			//如果叔叔是黑色 且当前结点是左孩子
			//右旋
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
	Node* y = NULL;//跟着跑 定位到待插入位置
	
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

	//开始进行修正
	rbtree_insert_fixup(root,node);
}

//删除的修正函数
/*
Node* node 待修正的结点
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
				//case1 : x的兄弟是红色的
				other->color == BLACK;
				parent->color == RED;
				rbtree_left_rotate(root, parent);
				other = parent->right;
			}
			//兄弟是黑色 且俩还是都是黑色
			if ( (!other->left || other->left->color == BLACK)
				&& (!other->right || other->right->color == BLACK))
			{
				other->color = RED;
				node = parent;
				parent = node->parent;
			}
			else
			{
				//兄弟是黑色 左孩子是红色 右孩子是黑色
				if (!other->right || other->right->color == BLACK)
				{
					other->left->color = BLACK;
					other->color = RED;
					rbtree_right_rotate(root, other);
					other = parent->right;
				}

				//兄弟是黑色 右孩子是红色 左孩子
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
				//case1 : x的兄弟是红色的
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

				//兄弟是黑色 右孩子是黑色 左孩子红色
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
	//标准的排序树的删除
	if ((node->left != NULL) && (node->right != NULL))
	{
		//找到被删除结点的后继/前驱
		Node* replace = node;//替代结点

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
			//更新根节点
			root->root = replace;
		}
		child = replace->right;
		parent = replace->parent;
		color = replace->color;

		//被删除结点是它的后继结点的父节点
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
			//调整
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

	//如果node不是根节点
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
		//执行删除
		rbtree_delete(root,z);
	}
	else 
	{
		//没有这个值 无法删除
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

