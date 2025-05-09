#pragma once

#include "Utils.h"

/// <summary>
/// 定义一个单向链表的节点。
/// </summary>
typedef struct SinglyLinkedListNode {
	/// <summary>
	/// 表示链表存储的数值。
	/// </summary>
	int value;

	/// <summary>
	/// 表示链表指向的下一个元素。
	/// </summary>
	struct SinglyLinkedListNode *next;
} SinglyLinkedListNode;

/// <summary>
/// 定义一个单向链表。
/// </summary>
typedef struct SinglyLinkedList {
	/// <summary>
	/// 表示链表的头节点。
	/// </summary>
	SinglyLinkedListNode *head;
} SinglyLinkedList;

/// <summary>
/// 表示遍历链表节点的函数指针。
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
