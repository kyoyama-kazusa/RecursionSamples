#pragma once

#include <stdbool.h>

typedef struct {
	/// <summary>
	/// 表示数组指针。
	/// </summary>
	int *data;

	/// <summary>
	/// 表示有多少个元素。
	/// </summary>
	int size;

	/// <summary>
	/// 表示当前列表的容量。
	/// </summary>
	int capacity;
} List;

void dispose_list(List *const);
bool list_add(List *const, int);
bool list_insert(List *const, int, int);
bool list_remove(List *const, int);
bool list_remove_at(List *const, int);
List *create_list(int);
