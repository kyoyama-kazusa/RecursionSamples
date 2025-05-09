#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool resize(List *, int);

/// <summary>
/// ��ʼ��һ��˳���
/// </summary>
/// <param name="list">˳���</param>
/// <param name="initial_capacity">��ʼ����������</param>
/// <returns>˳����Ƿ��ڴ������ɲ��ɹ�������</returns>
List *create_list(int initial_capacity) {
	if (initial_capacity <= 0) {
		return false;
	}

	List *list = (List *)malloc(sizeof(List));
	if (!list) {
		printf("�ڴ����ʧ�ܡ�");
		exit(-1);
	}

	list->data = (int *)malloc(initial_capacity * sizeof(int));
	if (!list->data) {
		printf("�ڴ����ʧ�ܡ�");
		exit(-1);
	}

	list->size = 0;
	list->capacity = initial_capacity;
	return list;
}

/// <summary>
/// �� list ���ڴ�����ͷš�
/// </summary>
/// <param name="list">˳���</param>
void dispose_list(List *const list) {
	free(list->data);
	list->data = NULL;
	list->size = list->capacity = 0;
}

/// <summary>
/// ׷��һ��ָ��Ԫ�ص�ĩβ��
/// </summary>
/// <param name="list">˳���</param>
/// <param name="element">��ֵ��</param>
/// <returns>�Ƿ���ӳɹ���</returns>
bool list_add(List *const list, int element) {
	if (list->size == list->capacity) {
		// �ο� C# �ڴ汶�����������ݣ���
		if (!resize(list, list->capacity << 1)) {
			return false;
		}
	}

	list->data[list->size++] = element;
	return true;
}

/// <summary>
/// ��Ԫ�ز��뵽ָ��������λ�õĺ��档
/// </summary>
/// <param name="list">˳���</param>
/// <param name="index">������</param>
/// <param name="element">��ֵ��</param>
/// <returns>�Ƿ����ɹ���</returns>
bool list_insert(List *const list, int index, int element) {
	if (index < 0 || index > list->size
		|| list->size == list->capacity && !resize(list, list->capacity * 2)) {
		return false;
	}

	// ����Ԫ���ڳ�λ�á�
	for (int i = list->size; i > index; i--) {
		list->data[i] = list->data[i - 1];
	}

	list->data[index] = element;
	list->size++;
	return true;
}

/// <summary>
/// ɾ��ָ��λ�õ�Ԫ�ء�
/// </summary>
/// <param name="list">˳���</param>
/// <param name="index">������</param>
/// <returns>�Ƿ�ɾ���ɹ���</returns>
bool list_remove_at(List *const list, int index) {
	if (index < 0 || index >= list->size) {
		return false;
	}

	// ǰ�ƺ���Ԫ�ء�
	for (int i = index; i < list->size - 1; i++) {
		list->data[i] = list->data[i + 1];
	}

	list->size--;
	return true;
}

/// <summary>
/// ɾ����һ��ƥ���Ԫ�ء�
/// </summary>
/// <param name="list">˳���</param>
/// <param name="element">��ֵ��</param>
/// <returns>�Ƿ�ɾ���ɹ���</returns>
bool list_remove(List *const list, int element) {
	for (int i = 0; i < list->size; i++) {
		if (list->data[i] == element) {
			return list_remove_at(list, i);
		}
	}
	return false;
}

/// <summary>
/// ����������
/// </summary>
/// <param name="list">˳���</param>
/// <param name="new_capacity">�µ�������С��</param>
/// <returns>�Ƿ�����ɹ���</returns>
static bool resize(List *list, int new_capacity) {
	int *new_data = (int *)realloc(list->data, new_capacity * sizeof(int));
	if (!new_data) {
		return false;
	}

	list->data = new_data;
	list->capacity = new_capacity;
	return true;
}
