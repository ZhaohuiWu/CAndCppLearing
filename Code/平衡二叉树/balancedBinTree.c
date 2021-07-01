/********************************************************************++
 *   Copyright (c) 2021     All rights reserved.
 * -------------------------------------------------------------------
 * Author   :   Mark Wu
 * Summary  :   数据结构课设————平衡二叉树
--********************************************************************/

#if 1	// 预处理操作
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define MAX_DIR 1024
#define max(a, b) ((a)>(b)?(a):(b))
#define inputElem(elem) scanf("%d", &(elem))
#define finputElem(fp, elem) fscanf(fp, "%d", &(elem))

#endif

#if 1	// 类型定义
typedef int elemType;
typedef struct binTreeNode
{
	struct binTreeNode * left;
	struct binTreeNode * right;
	int height;
	elemType data;
}binTreeNode, *binaryTree;

#endif

#if 1	// 函数的声明
void putMenu(void);
void destoryTree(binaryTree root);
void inOrderTraverse(binaryTree root);
int getTreeHeight(binTreeNode *root);
int getBalanceFactor(binTreeNode * node);
binTreeNode *findMinNode(binaryTree root);
binTreeNode *createNode(elemType x);
binaryTree fileInput(binaryTree root);
binaryTree insertNode(binaryTree root, elemType x);
binaryTree deleteNode(binaryTree root, elemType x);

// 平衡旋转操作
binaryTree llRotate(binTreeNode *node);
binaryTree lrRotate(binTreeNode *node);
binaryTree rlRotate(binTreeNode *node);
binaryTree rrRotate(binTreeNode *node);

#endif

int main(void)
{
	system("chcp 65001");	// 改变控制台的编码为UTF-8编码格式
	system("cls");

	binaryTree root = NULL;
	int choice, n;
	choice = n = 0;
	elemType x;
	while (1)
	{
		putMenu();
		scanf("%d", &choice);
		switch (choice)
		{
			case 1:
				printf("请输入需要插入的元素个数 ： ");
				scanf("%d", &n);
				printf("请输入需要插入的元素 ：");
				for (int i = 0; i < n; i++)
				{
					inputElem(x);
					root = insertNode(root, x);
				}
				break;
			case 2:
				root = fileInput(root);
				break;
			case 3:
				printf("请输入需要插入的元素 ：");
				inputElem(x);
				root = insertNode(root, x);
				break;
			case 4:
				printf("请输入需要删除的元素 ：");
				inputElem(x);
				root = deleteNode(root, x);
				printf("操作完成！\n");
				break;
			case 5:
				printf("中序遍历输出为 : \n");
				inOrderTraverse(root);
				printf("\n");
				break;
			case 6:
				destoryTree(root);
				root = NULL;
				printf("已清空！\n");
				break;
			default:
				destoryTree(root);
				return 0;
		}
	}
}

// 树节点的创建和初始化
binTreeNode *createNode(elemType x)
{
	binTreeNode * p = (binTreeNode *)malloc(sizeof(binTreeNode));
	p->left = p->right = NULL;
	p->data = x;
	p->height = 1;
	return p;
}

// 输出菜单
void putMenu(void)
{
	const char STAR_30[35] = "******************************";
	const char DASH_30[35] = "------------------------------";
	printf("**%s%s**\n", STAR_30, STAR_30);
	printf("*                   欢迎来到平衡二叉树小程序                   *\n");
	printf("*%s%s--*\n", DASH_30, DASH_30);
	printf("* 1. 键盘输入创建平衡二叉树                                    *\n");
	printf("* 2. 文件输入创建平衡二叉树                                    *\n");
	printf("* 3. 向平衡二叉树中插入单个元素                                *\n");
	printf("* 4. 删除平衡二叉树的某个元素                                  *\n");
	printf("* 5. 中序遍历该平衡二叉树                                      *\n");
	printf("* 6. 清空该平衡二叉树                                          *\n");
	printf("* 7. 退出该程序                                                *\n");
	printf("**%s%s**\n", STAR_30, STAR_30);
	printf("请输入您的选择(选项前序号) :  ");
}

// 清空该二叉树
void destoryTree(binaryTree root)
{
	if (!root)
		return;
	destoryTree(root->left);
	destoryTree(root->right);
	free(root);
	root = NULL;
	return;
}

binaryTree insertNode(binaryTree root, elemType x)
{
	// 树中一个节点也没有
	if (root == NULL)
		return createNode(x);

	if (x < root->data)
		root->left = insertNode(root->left, x);
	else if (x > root->data)
		root->right = insertNode(root->right, x);
	else
		return root;

	// 更新插入节点的祖先节点的高度信息
	root->height = 1 + max(getTreeHeight(root->left), getTreeHeight(root->right));

	// 当前节点的平衡因子
	int balanceFactor = getBalanceFactor(root);

	if (balanceFactor > 1)
	{
		if (x < root->left->data)
			return llRotate(root);
		else
			return lrRotate(root);
	}
	else if (balanceFactor < -1)
	{
		if (x > root->right->data)
			return rrRotate(root);
		else
			return rlRotate(root);
	}

	return root;
}

// 确定某个节点的平衡因子
int getBalanceFactor(binTreeNode * node)
{
	int leftheight = 0;
	int rightheight = 0;
	if (node->left)
		leftheight = node->left->height;
	if (node->right)
		rightheight = node->right->height;
	return leftheight - rightheight;
}

// ll型的旋转策略
binaryTree llRotate(binTreeNode *node)
{
	binTreeNode *t = node->left;
	node->left = t->right;
	t->right = node;

	node->height = max(getTreeHeight(node->left), getTreeHeight(node->right)) + 1;
	t->height = max(getTreeHeight(t->left), getTreeHeight(t->right)) + 1;

	return t;
}

// lr型的旋转策略
binaryTree lrRotate(binTreeNode *node)
{
	node->left = rrRotate(node->left);
	return llRotate(node);
}

// rl型的旋转策略
binaryTree rlRotate(binTreeNode *node)
{
	node->right = llRotate(node->right);
	return rrRotate(node);
}

// rr型的旋转策略
binaryTree rrRotate(binTreeNode *node)
{
	binTreeNode *t = node->right;
	node->right = t->left;
	t->left = node;

	node->height = max(getTreeHeight(node->left), getTreeHeight(node->right)) + 1;
	t->height = max(getTreeHeight(t->left), getTreeHeight(t->right)) + 1;

	return t;
}

binaryTree fileInput(binaryTree root)
{
	FILE *fp = NULL;
	int n, choice;
	char dir[MAX_DIR];
	elemType x;
	printf("请输入要打开文件的绝对路径(不同级别目录之间使用'\\\\'连接) : \n");
	while (1)
	{
		scanf("%s", dir);
		fp = fopen(dir, "r");
		if (fp)
			break;
		printf("[ERROR] : 输入错误！\n是否重新输入？\t1.是  0.否\n");
		scanf("%d", &choice);
		if (!choice)
			break;
		else
			printf("注意：目录之间不能有空格\n");
	}
	if (fp == NULL)
	{
		printf("创建失败！\n");
		return NULL;
	}

	finputElem(fp, n);
	for (int i = 0; i < n; i++)
	{
		finputElem(fp, x);
		root = insertNode(root, x);
	}
	printf("创建成功！\n");
	fclose(fp);
	return root;
}

// 中序遍历输出平衡二叉树
void inOrderTraverse(binaryTree root)
{
	if (root == NULL)
		return;
	inOrderTraverse(root->left);
	printf("%d  ", root->data);
	inOrderTraverse(root->right);
}

// 找到该二叉搜索树的最左边的节点
binTreeNode *findMinNode(binaryTree root)
{
	binTreeNode *temp = root;
	while (temp->left != NULL)
		temp = temp->left;
	return temp;
}

// 删除平衡二叉树的某个节点
binaryTree deleteNode(binaryTree root, elemType x)
{
	if (root == NULL)
		return root;

	if (x < root->data)
		root->left = deleteNode(root->left, x);
	else if (x > root->data)
		root->right = deleteNode(root->right, x);
	else
	{
		if ((root->left == NULL) || (root->right == NULL))
		{
			binTreeNode *temp = root->left ? root->left : root->right;

			if (temp == NULL)
			{
				temp = root;
				root = NULL;
			}
			else
				*root = *temp;
			free(temp);
		}
		else
		{
			binTreeNode *temp = findMinNode(root->right);
			root->data = temp->data;
			root->right = deleteNode(root->right, temp->data);
		}
	}

	if (root == NULL)
		return root;

	// 更新插入节点的祖先节点的高度信息
	root->height = 1 + max(getTreeHeight(root->left), getTreeHeight(root->right));

	// 当前节点的平衡因子
	int balanceFactor = getBalanceFactor(root);

	if (balanceFactor > 1)
	{
		if (x < root->left->data)
			return llRotate(root);
		else
			return lrRotate(root);
	}
	else if (balanceFactor < -1)
	{
		if (x > root->right->data)
			return rrRotate(root);
		else
			return rlRotate(root);
	}

	return root;
}

// 取得节点高度
int getTreeHeight(binTreeNode *root)
{
	if (root)
		return root->height;
	else
		return 0;
}
