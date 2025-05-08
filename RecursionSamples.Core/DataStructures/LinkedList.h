#pragma once

/// <summary>
/// 定义一个链表的节点。
/// </summary>
typedef struct LinkedListNode {
	/// <summary>
	/// 表示链表存储的数值。
	/// </summary>
	int value;

	/// <summary>
	/// 表示链表指向的下一个元素。
	/// </summary>
	struct LinkedListNode *next;
} LinkedListNode;

/// <summary>
/// 定义一个链表。
/// </summary>
typedef struct LinkedList {
	/// <summary>
	/// 表示链表的头节点。
	/// </summary>
	LinkedListNode *head;
} LinkedList;

LinkedList *create_linked_list(void);
void linked_list_add(LinkedList *const, int);
void linked_list_insert(LinkedListNode *, int);
void linked_list_dispose(LinkedList *const);
void linked_list_traverse(const LinkedList *const, void (*)(const LinkedListNode *const));
const LinkedListNode *const linked_list_index_of(const LinkedList *const, int);
