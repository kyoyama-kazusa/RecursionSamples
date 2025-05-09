#pragma once

#include <stdbool.h>

typedef struct {
	/// <summary>
	/// ��ʾ����ָ�롣
	/// </summary>
	int *data;

	/// <summary>
	/// ��ʾ�ж��ٸ�Ԫ�ء�
	/// </summary>
	int size;

	/// <summary>
	/// ��ʾ��ǰ�б��������
	/// </summary>
	int capacity;
} List;

void dispose_list(List *const);
bool list_add(List *const, int);
bool list_insert(List *const, int, int);
bool list_remove(List *const, int);
bool list_remove_at(List *const, int);
List *create_list(int);
