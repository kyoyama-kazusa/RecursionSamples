/*
* ���������ֱ���ģʽ
* 
* ������ѶȲ�С����ΪҪ�ö�����������ݽṹ������ѧ���Ļ������㲻֪��Ҳ����������й���������ˣ�����ѹ����������ôȥ�����д��
* ������������ǵݹ�ģ����Էǳ����룬���Ծ��Լ����ˡ�
*/

#pragma once

#include "../DataStructures/BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

void print_tree_node(const BinaryTree *const);

void entry(void) {
	// ���������
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

	printf("��ָ��һ�ֱ���ģʽ��0 - ǰ�������1 - ���������2 - ���������\n");
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
		"��������%s",
		node->left_child ? _itoa(node->left_child->value, buffer, 10) : "null"
	);
	sprintf(
		child_result + 100,
		"��������%s",
		node->right_child ? _itoa(node->right_child->value, buffer + 12, 10) : "null"
	);
	printf("��ǰ�ڵ���ֵ��%d��%s��%s\n", node->value, child_result, child_result + 100);
}
