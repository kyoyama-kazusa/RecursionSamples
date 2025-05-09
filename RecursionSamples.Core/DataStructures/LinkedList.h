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

/// <summary>
/// ��ʾ��������ڵ�ĺ���ָ�롣
/// </summary>
typedef void (*LinkedListTraverseAction)(const LinkedListNode *const);

void linked_list_add(LinkedList *const, int);
void linked_list_insert(LinkedListNode *, int);
void linked_list_dispose(LinkedList *const);
void linked_list_traverse(const LinkedList *const, LinkedListTraverseAction);
int linked_list_count(const LinkedList *const);
LinkedList *create_linked_list(void);
LinkedListNode *linked_list_tail(const LinkedList *const);
const LinkedListNode *linked_list_element_at(const LinkedList *const, int);
const LinkedListNode *const linked_list_index_of(const LinkedList *const, int);
const LinkedListNode *const linked_list_remove(LinkedList *const, int);
