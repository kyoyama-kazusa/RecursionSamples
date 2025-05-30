/*
* 二叉树三种遍历模式
* 
* 这个题难度不小，因为要用二叉树这个数据结构。不过学过的话就算你不知道也早已熟读背诵过这个代码了，所以压根都不用怎么去边想边写。
* 二叉树自身就是递归的，所以非常好想，所以就自己看了。
*/

#pragma once

#include "../DataStructures/BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

void print_tree_node(const BinaryTree *const);

void entry(void) {
	// 比如这个：
	//     0
	//    / \
	//   1   2
	//  / \
	// 3   4
	BinaryTree d = { .left_child = NULL, .right_child = NULL, .value = 3 };
	BinaryTree e = { .left_child = NULL, .right_child = NULL, .value = 4 };
	BinaryTree b = { .left_child = &d, .right_child = &e, .value = 1 };
	BinaryTree c = { .left_child = NULL, .right_child = NULL, .value = 2 };
	BinaryTree root = { .left_child = &b, .right_child = &c, .value = 0 };

	printf("请指定一种遍历模式：0 - 前序遍历，1 - 中序遍历，2 - 后序遍历：\n");
	int mode;
	int ignored = scanf("%d", &mode);
	BinaryTreeOrder order = mode == 0 ? Preordered : mode == 1 ? Inordered : Postordered;
	binary_tree_traverse(&root, order, print_tree_node);
}

static void print_tree_node(const BinaryTree *const node) {
	char buffer[24] = { '\0' };
	char child_result[200] = { '\0' };
	sprintf(
		child_result,
		"左子树：%s",
		node->left_child ? _itoa(node->left_child->value, buffer, 10) : "null"
	);
	sprintf(
		child_result + 100,
		"右子树：%s",
		node->right_child ? _itoa(node->right_child->value, buffer + 12, 10) : "null"
	);
	printf("当前节点数值：%d，%s，%s\n", node->value, child_result, child_result + 100);
}
