#include "LinkedList.h"
#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>

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
		list->head = node; // 如果链表头节点都不存在，则让头节点指向它，它作为第一个节点。
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
	if (!node->next) {
		printf("指定节点 "nameof(node)" 尚不存在后继节点。");
		exit(-2);
	}

	LinkedListNode *target = node->next->next;
	LinkedListNode *created = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	if (!created) {
		printf("内存分配失败。");
		exit(-1);
	}

	node->next = created; // 让 node 作为前驱节点，使得它 next 指向创建的节点。
	created->next = target; // 让创建的节点连接到原本 node 的后继节点。
	created->value = value;
}

/// <summary>
/// 从链表里删除第一个遍历遇到的指定数值的节点。如果节点找不到，则会返回 NULL。
/// </summary>
/// <param name="list">链表。</param>
/// <param name="value">数值。</param>
/// <returns>节点。节点拿到后如果不使用请释放它。</returns>
const LinkedListNode *const linked_list_remove(LinkedList *const list, int value) {
	LinkedListNode *temp = list->head;
	if (!temp) {
		// 链表为空。
		return NULL;
	}

	LinkedListNode *current = temp->next;
	for (LinkedListNode *previous = list->head; current; previous = previous->next, current = current->next) {
		if (current->value == value) {
			// 找到节点，删除它。
			const LinkedListNode *const node = current;
			previous->next = current->next; // 直接让前驱节点指向 current 的后继节点，跳过 current。
			current->next = NULL; // 然后断开 current 指向 current->next。
			return node;
		}
	}

	// 找不到这个删除的节点。
	return NULL;
}

/// <summary>
/// 找到索引为 i 的指定节点，返回该节点的地址；如果索引值过大，则会返回 NULL。
/// </summary>
/// <param name="list">链表。</param>
/// <param name="i">索引。</param>
/// <returns>节点。</returns>
const LinkedListNode *linked_list_element_at(const LinkedList *const list, int i) {
	if (i < 0) {
		printf("索引值参数 "nameof(i)" 不可为负数。");
		exit(-2);
	}

	int index = 0;
	for (const LinkedListNode *current = list->head; current; current = current->next) {
		if (index++ == i) {
			return current;
		}
	}
	return NULL;
}

/// <summary>
/// 释放链表的内存。
/// </summary>
/// <param name="list">链表。</param>
void linked_list_dispose(LinkedList *const list) {
	// 循环进行销毁。
	for (LinkedListNode *current = list->head; current;) {
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
void linked_list_traverse(const LinkedList *const list, LinkedListTraverseAction traverse_node) {
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

/// <summary>
/// 获取指定链表的尾节点。如果链表没有元素，则返回 NULL。
/// </summary>
/// <param name="list">链表。</param>
/// <returns>该链表的尾节点。</returns>
LinkedListNode *linked_list_tail(const LinkedList *const list) {
	LinkedListNode *result = list->head;
	for (LinkedListNode *current = list->head->next; current; current = current->next, result = result->next);
	return result;
}

/// <summary>
/// 获取指定链表的长度。
/// </summary>
/// <param name="list">链表。</param>
/// <returns>该链表的长度（多少个元素）。</returns>
int linked_list_count(const LinkedList *const list) {
	int result = 0;
	for (LinkedListNode *current = list->head; current; current = current->next, result++);
	return result;
}
