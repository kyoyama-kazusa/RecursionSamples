#pragma once


/// <summary>
/// ��ʾ�������ڵ����͡�
/// </summary>
typedef struct BinaryTree {
	/// <summary>
	/// ��ʾ��������
	/// </summary>
	struct BinaryTree *left_child;

	/// <summary>
	/// ��ʾ��������
	/// </summary>
	struct BinaryTree *right_child;

	/// <summary>
	/// ��ʾ��ֵ��
	/// </summary>
	int value;
} BinaryTree;

/// <summary>
/// ָ��һ�ֶ���������ģʽ��
/// </summary>
typedef enum {
	/// <summary>
	/// ��ʾǰ�������
	/// </summary>
	Preordered,

	/// <summary>
	/// ��ʾ���������
	/// </summary>
	Inordered,

	/// <summary>
	/// ��ʾ���������
	/// </summary>
	Postordered
} BinaryTreeOrder;

/// <summary>
/// ��ʾ����������ʱ��ִ�еĲ�����
/// </summary>
typedef void (*BinaryTreeTraverseAction)(const BinaryTree *const);

void binary_tree_traverse(const BinaryTree *const, BinaryTreeOrder, BinaryTreeTraverseAction);
