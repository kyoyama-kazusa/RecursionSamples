#pragma once

#include "Utils.h"

/// <summary>
/// ����һ����������Ľڵ㡣
/// </summary>
typedef struct SinglyLinkedListNode {
	/// <summary>
	/// ��ʾ����洢����ֵ��
	/// </summary>
	int value;

	/// <summary>
	/// ��ʾ����ָ�����һ��Ԫ�ء�
	/// </summary>
	struct SinglyLinkedListNode *next;
} SinglyLinkedListNode;

/// <summary>
/// ����һ����������
/// </summary>
typedef struct SinglyLinkedList {
	/// <summary>
	/// ��ʾ�����ͷ�ڵ㡣
	/// </summary>
	SinglyLinkedListNode *head;
} SinglyLinkedList;

/// <summary>
/// ��ʾ��������ڵ�ĺ���ָ�롣
/// </summary>
typedef void (*SinglyLinkedListTraverseAction)(const SinglyLinkedListNode *const);

void linked_list_add(SinglyLinkedList *const, int);
void linked_list_insert(SinglyLinkedListNode *, int);
void linked_list_dispose(SinglyLinkedList *const);
void linked_list_traverse(const SinglyLinkedList *const, SinglyLinkedListTraverseAction);
int linked_list_count(const SinglyLinkedList *const);
SinglyLinkedList *create_linked_list(void);
SinglyLinkedListNode *linked_list_tail(const SinglyLinkedList *const);
const SinglyLinkedListNode *linked_list_element_at(const SinglyLinkedList *const, int);
const SinglyLinkedListNode *const linked_list_index_of(const SinglyLinkedList *const, int);
const SinglyLinkedListNode *const linked_list_remove(SinglyLinkedList *const, int);
