#pragma once

/// <summary>
/// ����һ������Ľڵ㡣
/// </summary>
typedef struct LinkedListNode {
	/// <summary>
	/// ��ʾ����洢����ֵ��
	/// </summary>
	int value;

	/// <summary>
	/// ��ʾ����ָ�����һ��Ԫ�ء�
	/// </summary>
	struct LinkedListNode *next;
} LinkedListNode;

/// <summary>
/// ����һ������
/// </summary>
typedef struct LinkedList {
	/// <summary>
	/// ��ʾ�����ͷ�ڵ㡣
	/// </summary>
	LinkedListNode *head;
} LinkedList;

LinkedList *create_linked_list(void);
void linked_list_add(LinkedList *const, int);
void linked_list_insert(LinkedListNode *, int);
void linked_list_dispose(LinkedList *const);
void linked_list_traverse(const LinkedList *const, void (*)(const LinkedListNode *const));
const LinkedListNode *const linked_list_index_of(const LinkedList *const, int);
