/*************************************************************************
	> File Name: list_tree.c
	> Author: likang
	> Created Time: 2014年08月13日 星期三 12时44分31秒
 ************************************************************************/

#include<stdio.h>
#include "tree.h"
#include<stdlib.h>
#include<malloc.h>
#include<assert.h>

typedef struct TREE_NODE
{
	TREE_TYPE value;
	struct TREE_NODE *left;
	struct TREE_NODE *right;
}TreeNode;

static TreeNode *tree;
static int flag = 0;

void
insert(TREE_TYPE value)
{
	TreeNode *current;
	TreeNode **link;
	link = &tree;
	while((current = *link) != NULL){
		if(value < current->value)
			link = &current->left;
		else{
			assert(value != current->value);
			link = &current->right;
		}
	}
	current = (TreeNode *)malloc(sizeof(TreeNode));
	assert(current != NULL);
	current->value = value;
	current->left = NULL;
	current->right = NULL;
	*link = current;
}
/*方法1
void
precreate_tree(TreeNode **T)
{
    int value;
    scanf("%d",&value);
    if (value == 0)
        return;

    *T = (TreeNode *)malloc(sizeof(TreeNode));
    TreeNode *cu = *T;
    cu->value = value;
    precreate_tree(&cu->left);
    precreate_tree(&cu->right);
}
*/

/***************方法2*******/
TreeNode*  precreate_tree()
{
    int value;
    TreeNode *T;
    scanf("%d",&value);
    if (value == 0)
        return NULL;
    T = (TreeNode *)malloc(sizeof(TreeNode));
    T->value = value;
    T->left = precreate_tree();
    T->right = precreate_tree();

    return T;
}

int
find(TREE_TYPE value)
{
	TreeNode *current = tree;
	while(current != NULL && current->value != value)
	{
		if(value > current->value)
			current = current->right;
		else
			current = current->left;
	}
	if(current != NULL)
		return 1;
	return 0;
}

void
callback(TREE_TYPE value)
{
	printf("%d ",value);
}

static void
do_pre_order_traverse(TreeNode *current, void (*callback)(TREE_TYPE value))
{
	if(current != NULL)
	{
		callback(current->value);
		do_pre_order_traverse(current->left, callback);
		do_pre_order_traverse(current->right,callback);
	}
}

static void
judgeAVL(TreeNode *tr,int (*callback)(TreeNode *T))
{
    if (tr != NULL)
    {
        int left_depth = callback(tr->left);
        int right_depth = callback(tr->right);
        printf("l = %d r = %d \n",left_depth,right_depth);
        if (abs(left_depth-right_depth) > 1)
            flag = 1;
        else
        {
            judgeAVL(tr->left,callback);
            judgeAVL(tr->right,callback);
        }
    }
}

void
pre_order_traverse(void (*callback)(TREE_TYPE value))
{
	do_pre_order_traverse(tree, callback);
}

int
tree_depth(TreeNode *current)
{
	if(current == NULL)	
		return 0;
	int left = tree_depth(current->left);
	int right = tree_depth(current->right);
	return left > right ? left + 1 : right + 1;
}

int
main(void)
{
	int i;
	int value;
	for(i = 0; i < 10; i++)
	{
		printf("input the %d value:",i+1);
		scanf("%d",&value);
		getchar();
		insert(value);
	}
    judgeAVL(tree,tree_depth);
    if (flag == 0)
    {
        printf("this is a AVL tree!\n");
    }
    else
    {
        printf("this is not a AVL tree\n");
    }
	return 0;
}

