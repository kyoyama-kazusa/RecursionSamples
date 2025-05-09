#include "LinkedList.h"
#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>

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
		list->head = node; // �������ͷ�ڵ㶼�����ڣ�����ͷ�ڵ�ָ����������Ϊ��һ���ڵ㡣
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
	if (!node->next) {
		printf("ָ���ڵ� "nameof(node)" �в����ں�̽ڵ㡣");
		exit(-2);
	}

	LinkedListNode *target = node->next->next;
	LinkedListNode *created = (LinkedListNode *)malloc(sizeof(LinkedListNode));
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
const LinkedListNode *const linked_list_remove(LinkedList *const list, int value) {
	LinkedListNode *temp = list->head;
	if (!temp) {
		// ����Ϊ�ա�
		return NULL;
	}

	LinkedListNode *current = temp->next;
	for (LinkedListNode *previous = list->head; current; previous = previous->next, current = current->next) {
		if (current->value == value) {
			// �ҵ��ڵ㣬ɾ������
			const LinkedListNode *const node = current;
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
const LinkedListNode *linked_list_element_at(const LinkedList *const list, int i) {
	if (i < 0) {
		printf("����ֵ���� "nameof(i)" ����Ϊ������");
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
/// �ͷ�������ڴ档
/// </summary>
/// <param name="list">����</param>
void linked_list_dispose(LinkedList *const list) {
	// ѭ���������١�
	for (LinkedListNode *current = list->head; current;) {
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
void linked_list_traverse(const LinkedList *const list, LinkedListTraverseAction traverse_node) {
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

/// <summary>
/// ��ȡָ�������β�ڵ㡣�������û��Ԫ�أ��򷵻� NULL��
/// </summary>
/// <param name="list">����</param>
/// <returns>�������β�ڵ㡣</returns>
LinkedListNode *linked_list_tail(const LinkedList *const list) {
	LinkedListNode *result = list->head;
	for (LinkedListNode *current = list->head->next; current; current = current->next, result = result->next);
	return result;
}

/// <summary>
/// ��ȡָ������ĳ��ȡ�
/// </summary>
/// <param name="list">����</param>
/// <returns>������ĳ��ȣ����ٸ�Ԫ�أ���</returns>
int linked_list_count(const LinkedList *const list) {
	int result = 0;
	for (LinkedListNode *current = list->head; current; current = current->next, result++);
	return result;
}
