#include "List.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool resize(List *, int);

/// <summary>
/// 初始化一个顺序表。
/// </summary>
/// <param name="list">顺序表。</param>
/// <param name="initial_capacity">初始化的容量。</param>
/// <returns>顺序表是否内存分配完成并成功创建。</returns>
List *create_list(int initial_capacity) {
	if (initial_capacity <= 0) {
		return false;
	}

	List *list = (List *)malloc(sizeof(List));
	if (!list) {
		printf("内存分配失败。");
		exit(-1);
	}

	list->data = (int *)malloc(initial_capacity * sizeof(int));
	if (!list->data) {
		printf("内存分配失败。");
		exit(-1);
	}

	list->size = 0;
	list->capacity = initial_capacity;
	return list;
}

/// <summary>
/// 将 list 的内存进行释放。
/// </summary>
/// <param name="list">顺序表。</param>
void dispose_list(List *const list) {
	free(list->data);
	list->data = NULL;
	list->size = list->capacity = 0;
}

/// <summary>
/// 追加一个指定元素到末尾。
/// </summary>
/// <param name="list">顺序表。</param>
/// <param name="element">数值。</param>
/// <returns>是否添加成功。</returns>
bool list_add(List *const list, int element) {
	if (list->size == list->capacity) {
		// 参考 C# 内存倍扩（翻倍扩容）。
		if (!resize(list, list->capacity << 1)) {
			return false;
		}
	}

	list->data[list->size++] = element;
	return true;
}

/// <summary>
/// 将元素插入到指定索引的位置的后面。
/// </summary>
/// <param name="list">顺序表。</param>
/// <param name="index">索引。</param>
/// <param name="element">数值。</param>
/// <returns>是否插入成功。</returns>
bool list_insert(List *const list, int index, int element) {
	if (index < 0 || index > list->size
		|| list->size == list->capacity && !resize(list, list->capacity * 2)) {
		return false;
	}

	// 后移元素腾出位置。
	for (int i = list->size; i > index; i--) {
		list->data[i] = list->data[i - 1];
	}

	list->data[index] = element;
	list->size++;
	return true;
}

/// <summary>
/// 删除指定位置的元素。
/// </summary>
/// <param name="list">顺序表。</param>
/// <param name="index">索引。</param>
/// <returns>是否删除成功。</returns>
bool list_remove_at(List *const list, int index) {
	if (index < 0 || index >= list->size) {
		return false;
	}

	// 前移后续元素。
	for (int i = index; i < list->size - 1; i++) {
		list->data[i] = list->data[i + 1];
	}

	list->size--;
	return true;
}

/// <summary>
/// 删除第一个匹配的元素。
/// </summary>
/// <param name="list">顺序表。</param>
/// <param name="element">数值。</param>
/// <returns>是否删除成功。</returns>
bool list_remove(List *const list, int element) {
	for (int i = 0; i < list->size; i++) {
		if (list->data[i] == element) {
			return list_remove_at(list, i);
		}
	}
	return false;
}

/// <summary>
/// 调整容量。
/// </summary>
/// <param name="list">顺序表。</param>
/// <param name="new_capacity">新的容量大小。</param>
/// <returns>是否调整成功。</returns>
static bool resize(List *list, int new_capacity) {
	int *new_data = (int *)realloc(list->data, new_capacity * sizeof(int));
	if (!new_data) {
		return false;
	}

	list->data = new_data;
	list->capacity = new_capacity;
	return true;
}
