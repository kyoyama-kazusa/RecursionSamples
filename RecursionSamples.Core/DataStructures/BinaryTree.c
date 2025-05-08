#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// 遍历一个二叉树。
/// </summary>
/// <param name="base">二叉树。</param>
/// <param name="order">表示二叉树的遍历模式。</param>
/// <param name="traverse_action">二叉树遍历到每一个节点所执行的方法。</param>
void binary_tree_traverse(const BinaryTree *const base, BinaryTreeOrder order, BinaryTreeTraverseAction traverse_action) {
	switch (order) {
	case Preordered:
		// 前序遍历：中间，左子树，右子树。
		traverse_action(base);
		if (base->left_child) {
			binary_tree_traverse(base->left_child, order, traverse_action);
		}
		if (base->right_child) {
			binary_tree_traverse(base->right_child, order, traverse_action);
		}
		break;
	case Inordered:
		// 中序遍历：左子树，中间，右子树。
		if (base->left_child) {
			binary_tree_traverse(base->left_child, order, traverse_action);
		}
		traverse_action(base);
		if (base->right_child) {
			binary_tree_traverse(base->right_child, order, traverse_action);
		}
		break;
	case Postordered:
		// 后序遍历：左子树，右子树，中间。
		if (base->left_child) {
			binary_tree_traverse(base->left_child, order, traverse_action);
		}
		if (base->right_child) {
			binary_tree_traverse(base->right_child, order, traverse_action);
		}
		traverse_action(base);
		break;
	}
}
