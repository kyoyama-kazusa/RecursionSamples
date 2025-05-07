#pragma once


/// <summary>
/// 表示二叉树节点类型。
/// </summary>
typedef struct BinaryTree {
	/// <summary>
	/// 表示左子树。
	/// </summary>
	struct BinaryTree *left_child;

	/// <summary>
	/// 表示右子树。
	/// </summary>
	struct BinaryTree *right_child;

	/// <summary>
	/// 表示数值。
	/// </summary>
	int value;
} BinaryTree;

/// <summary>
/// 指定一种二叉树遍历模式。
/// </summary>
typedef enum {
	/// <summary>
	/// 表示前序遍历。
	/// </summary>
	Preordered,

	/// <summary>
	/// 表示中序遍历。
	/// </summary>
	Inordered,

	/// <summary>
	/// 表示后序遍历。
	/// </summary>
	Postordered
} BinaryTreeOrder;

/// <summary>
/// 表示二叉树遍历时候执行的操作。
/// </summary>
typedef void (*BinaryTreeTraverseAction)(const BinaryTree *const);

void binary_tree_traverse(const BinaryTree *const, BinaryTreeOrder, BinaryTreeTraverseAction);
