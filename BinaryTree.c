#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// ����һ����������
/// </summary>
/// <param name="base">��������</param>
/// <param name="order">��ʾ�������ı���ģʽ��</param>
/// <param name="traverse_action">������������ÿһ���ڵ���ִ�еķ�����</param>
void binary_tree_traverse(const BinaryTree *const base, BinaryTreeOrder order, BinaryTreeTraverseAction traverse_action) {
	switch (order) {
	case Preordered:
		// ǰ��������м䣬����������������
		traverse_action(base);
		if (base->left_child) {
			binary_tree_traverse(base->left_child, order, traverse_action);
		}
		if (base->right_child) {
			binary_tree_traverse(base->right_child, order, traverse_action);
		}
		break;
	case Inordered:
		// ������������������м䣬��������
		if (base->left_child) {
			binary_tree_traverse(base->left_child, order, traverse_action);
		}
		traverse_action(base);
		if (base->right_child) {
			binary_tree_traverse(base->right_child, order, traverse_action);
		}
		break;
	case Postordered:
		// ��������������������������м䡣
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
