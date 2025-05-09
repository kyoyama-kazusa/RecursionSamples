#include "SinglyLinkedList.h"
#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// ����һ��������
/// </summary>
/// <returns>�������ָ�룬��Ҫ free �ͷ��ڴ档</returns>
SinglyLinkedList *create_linked_list(void) {
	SinglyLinkedList *result = (SinglyLinkedList *const)malloc(sizeof(SinglyLinkedList));
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
void linked_list_add(SinglyLinkedList *const list, int value) {
	SinglyLinkedListNode *const node = (SinglyLinkedListNode *const)malloc(sizeof(SinglyLinkedListNode));
	if (!node) {
		printf("�ڴ����ʧ�ܡ�");
		exit(-1);
	}

	node->value = value;
	node->next = NULL;
	if (!list->head) {
		list->head = node; // �������ͷ�ڵ㶼�����ڣ�����ͷ�ڵ�ָ����������Ϊ��һ���ڵ㡣
		return;
	}

	// ��ͷ�ڵ㿪ʼ��������� next Ϊ NULL �Ľڵ㣬Ȼ��� next ָ�� node��
	for (SinglyLinkedListNode *current = list->head; current; current = current->next) {
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
void linked_list_insert(SinglyLinkedListNode *node, int value) {
	if (!node->next) {
		printf("ָ���ڵ� "nameof(node)" �в����ں�̽ڵ㡣");
		exit(-2);
	}

	SinglyLinkedListNode *target = node->next->next;
	SinglyLinkedListNode *created = (SinglyLinkedListNode *)malloc(sizeof(SinglyLinkedListNode));
	if (!created) {
		printf("�ڴ����ʧ�ܡ�");
		exit(-1);
	}

	node->next = created; // �� node ��Ϊǰ���ڵ㣬ʹ���� next ָ�򴴽��Ľڵ㡣
	created->next = target; // �ô����Ľڵ����ӵ�ԭ�� node �ĺ�̽ڵ㡣
	created->value = value;
}

/// <summary>
/// ��������ɾ����һ������������ָ����ֵ�Ľڵ㡣����ڵ��Ҳ�������᷵�� NULL��
/// </summary>
/// <param name="list">����</param>
/// <param name="value">��ֵ��</param>
/// <returns>�ڵ㡣�ڵ��õ��������ʹ�����ͷ�����</returns>
const SinglyLinkedListNode *const linked_list_remove(SinglyLinkedList *const list, int value) {
	SinglyLinkedListNode *temp = list->head;
	if (!temp) {
		// ����Ϊ�ա�
		return NULL;
	}

	SinglyLinkedListNode *current = temp->next;
	for (SinglyLinkedListNode *previous = list->head; current; previous = previous->next, current = current->next) {
		if (current->value == value) {
			// �ҵ��ڵ㣬ɾ������
			const SinglyLinkedListNode *const node = current;
			previous->next = current->next; // ֱ����ǰ���ڵ�ָ�� current �ĺ�̽ڵ㣬���� current��
			current->next = NULL; // Ȼ��Ͽ� current ָ�� current->next��
			return node;
		}
	}

	// �Ҳ������ɾ���Ľڵ㡣
	return NULL;
}

/// <summary>
/// �ҵ�����Ϊ i ��ָ���ڵ㣬���ظýڵ�ĵ�ַ���������ֵ������᷵�� NULL��
/// </summary>
/// <param name="list">����</param>
/// <param name="i">������</param>
/// <returns>�ڵ㡣</returns>
const SinglyLinkedListNode *linked_list_element_at(const SinglyLinkedList *const list, int i) {
	if (i < 0) {
		printf("����ֵ���� "nameof(i)" ����Ϊ������");
		exit(-2);
	}

	int index = 0;
	for (const SinglyLinkedListNode *current = list->head; current; current = current->next) {
		if (index++ == i) {
			return current;
		}
	}
	return NULL;
}

/// <summary>
/// �ͷ�������ڴ档
/// </summary>
/// <param name="list">����</param>
void linked_list_dispose(SinglyLinkedList *const list) {
	// ѭ���������١�
	for (SinglyLinkedListNode *current = list->head; current;) {
		SinglyLinkedListNode *next = current->next;
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
void linked_list_traverse(const SinglyLinkedList *const list, SinglyLinkedListTraverseAction traverse_node) {
	for (SinglyLinkedListNode *current = list->head; current; current = current->next) {
		traverse_node(current);
	}
}

/// <summary>
/// �ж��������Ƿ��нڵ����ֵ�� value������з�������ڵ��ָ�롣
/// </summary>
/// <param name="list">����</param>
/// <param name="value">��ֵ��</param>
/// <returns>ָ������ڵ��ָ�롣</returns>
const SinglyLinkedListNode *const linked_list_index_of(const SinglyLinkedList *const list, int value) {
	for (SinglyLinkedListNode *current = list->head; current; current = current->next) {
		if (current->value == value) {
			return current;
		}
	}
	return NULL;
}

/// <summary>
/// ��ȡָ�������β�ڵ㡣�������û��Ԫ�أ��򷵻� NULL��
/// </summary>
/// <param name="list">����</param>
/// <returns>�������β�ڵ㡣</returns>
SinglyLinkedListNode *linked_list_tail(const SinglyLinkedList *const list) {
	SinglyLinkedListNode *result = list->head;
	for (SinglyLinkedListNode *current = list->head->next; current; current = current->next, result = result->next);
	return result;
}

/// <summary>
/// ��ȡָ������ĳ��ȡ�
/// </summary>
/// <param name="list">����</param>
/// <returns>������ĳ��ȣ����ٸ�Ԫ�أ���</returns>
int linked_list_count(const SinglyLinkedList *const list) {
	int result = 0;
	for (SinglyLinkedListNode *current = list->head; current; current = current->next, result++);
	return result;
}
