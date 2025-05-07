#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

/// <summary>
/// ����һ��������
/// </summary>
/// <returns>�������ָ�룬��Ҫ free �ͷ��ڴ档</returns>
LinkedList *create_linked_list(void) {
	LinkedList *result = (LinkedList *const)malloc(sizeof(LinkedList));
	if (!result) {
		printf("�ڴ����ʧ�ܡ�");
		exit(-1);
	}

	result->head = NULL;
	return result;
}

/// <summary>
/// �����������һ��Ԫ�ء�
/// </summary>
/// <param name="list">����</param>
/// <param name="value">Ԫ�ء�</param>
void linked_list_add(LinkedList *const list, int value) {
	LinkedListNode *const node = (LinkedListNode *const)malloc(sizeof(LinkedListNode));
	if (!node) {
		printf("�ڴ����ʧ�ܡ�");
		exit(-1);
	}

	node->value = value;
	node->next = NULL;
	if (!list->head) {
		list->head = node;
		return;
	}

	// ��ͷ�ڵ㿪ʼ��������� next Ϊ NULL �Ľڵ㣬Ȼ��� next ָ�� node��
	for (LinkedListNode *current = list->head; current; current = current->next) {
		if (!current->next) {
			// ������һ���ڵ�Ϊ NULL��
			current->next = node;
			break;
		}
	}
}

/// <summary>
/// ��ָ��������ڵ��ϲ���һ���µĽڵ㡣
/// </summary>
/// <param name="node">����ڵ㡣</param>
/// <param name="value">��ֵ��</param>
void linked_list_insert(LinkedListNode *node, int value) {
	LinkedListNode *target = node->next->next;
	LinkedListNode *created = (LinkedListNode *)malloc(sizeof(LinkedListNode));
	if (!created) {
		printf("�ڴ����ʧ�ܡ�");
		exit(-1);
	}

	node->next = created;
	created->next = target;
	created->value = value;
}

/// <summary>
/// �ͷ�������ڴ档
/// </summary>
/// <param name="list">����</param>
void linked_list_dispose(LinkedList *const list) {
	// ѭ���������١�
	for (LinkedListNode *current = list->head; current; ) {
		LinkedListNode *next = current->next;
		free(current);
		current = next;
	}

	// ���ٺ���ⴹ��ָ�룬�� list ��ͷ�ڵ�ָ�� NULL��
	list->head = NULL;
}

/// <summary>
/// ������������
/// </summary>
/// <param name="list">����</param>
/// <param name="traverse_node">�����ڵ������õĺ���ָ�롣</param>
void linked_list_traverse(const LinkedList *const list, void (*traverse_node)(const LinkedListNode *const)) {
	for (LinkedListNode *current = list->head; current; current = current->next) {
		traverse_node(current);
	}
}

/// <summary>
/// �ж��������Ƿ��нڵ����ֵ�� value������з�������ڵ��ָ�롣
/// </summary>
/// <param name="list">����</param>
/// <param name="value">��ֵ��</param>
/// <returns>ָ������ڵ��ָ�롣</returns>
const LinkedListNode *const linked_list_index_of(const LinkedList *const list, int value) {
	for (LinkedListNode *current = list->head; current; current = current->next) {
		if (current->value == value) {
			return current;
		}
	}
	return NULL;
}
