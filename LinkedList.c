#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/// <summary>
/// 创建一个空链表。
/// </summary>
/// <returns>空链表的指针，需要 free 释放内存。</returns>
LinkedList *create_linked_list(void) {
	LinkedList *result = (LinkedList *const)malloc(sizeof(LinkedList));
	if (!result) {
		printf("内存分配失败。");
		exit(-1);
	}

	result->head = NULL;
	return result;
}

/// <summary>
/// 往链表里添加一个元素。
/// </summary>
/// <param name="list">链表。</param>
/// <param name="value">元素。</param>
void linked_list_add(LinkedList *const list, int value) {
	LinkedListNode *const node = (LinkedListNode *const)malloc(sizeof(LinkedListNode));
	if (!node) {
		printf("内存分配失败。");
		exit(-1);
	}

	node->value = value;
	node->next = NULL;
	if (!list->head) {
		list->head = node;
		return;
	}

	// 从头节点开始遍历到最后 next 为 NULL 的节点，然后把 next 指向 node。
	for (LinkedListNode *current = list->head; current; current = current->next) {
		if (!current->next) {
			// 它的下一个节点为 NULL。
			current->next = node;
			break;
		}
	}
}

/// <summary>
/// 往指定的链表节点上插入一个新的节点。
/// </summary>
/// <param name="node">链表节点。</param>
/// <param name="value">数值。</param>
void linked_list_insert(LinkedListNode *node, int value) {
	LinkedListNode *target = node->next->next;
	LinkedListNode *created = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	if (!created) {
		printf("内存分配失败。");
		exit(-1);
	}

	node->next = created;
	created->next = target;
	created->value = value;
}

/// <summary>
/// 释放链表的内存。
/// </summary>
/// <param name="list">链表。</param>
void linked_list_dispose(LinkedList *const list) {
	// 循环进行销毁。
	for (LinkedListNode *current = list->head; current; ) {
		LinkedListNode *next = current->next;
		free(current);
		current = next;
	}

	// 销毁后避免垂悬指针，让 list 的头节点指向 NULL。
	list->head = NULL;
}

/// <summary>
/// 遍历整个链表。
/// </summary>
/// <param name="list">链表。</param>
/// <param name="traverse_node">遍历节点所调用的函数指针。</param>
void linked_list_traverse(const LinkedList *const list, void (*traverse_node)(const LinkedListNode *const)) {
	for (LinkedListNode *current = list->head; current; current = current->next) {
		traverse_node(current);
	}
}

/// <summary>
/// 判断链表里是否有节点的数值是 value。如果有返回这个节点的指针。
/// </summary>
/// <param name="list">链表。</param>
/// <param name="value">数值。</param>
/// <returns>指向这个节点的指针。</returns>
const LinkedListNode *const linked_list_index_of(const LinkedList *const list, int value) {
	for (LinkedListNode *current = list->head; current; current = current->next) {
		if (current->value == value) {
			return current;
		}
	}
	return NULL;
}
