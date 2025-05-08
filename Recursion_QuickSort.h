#pragma once

#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>

void quick_sort(int *, int, int);
int partition(int *, int, int);
void swap(int *__restrict, int *__restrict);

void entry(void) {
	int array[9] = { 3, 8, 1, 6, 5, 4, 7, 2, 9 };
	print_array(array, 9);

	quick_sort(array, 0, 8);
	print_array(array, 9);
}

/// <summary>
/// 执行快速排序。
/// </summary>
/// <param name="array">数组。</param>
/// <param name="left">左边索引。</param>
/// <param name="right">右边索引。</param>
void quick_sort(int *array, int left, int right) {
	if (left < right) {
		// 分区，找出锚点，左边的数都小于锚点，右边的数都大于锚点。
		int pivot = partition(array, left, right);

		// 对基准左右两侧的子数组递归执行上述操作。
		quick_sort(array, left, pivot - 1);
		quick_sort(array, pivot + 1, right);
	}
}

/// <summary>
/// 将数组先分成两个区，让左边的小于指定数值，右边的大于指定数值。
/// </summary>
/// <param name="array">数组。</param>
/// <param name="left">左边索引。</param>
/// <param name="right">右边索引。</param>
/// <returns>中间的索引位置。</returns>
int partition(int *array, int left, int right) {
	int pivot = array[right];
	int i = left - 1;
	for (int j = left; j < right; j++) {
		if (array[j] < pivot) {
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[right]);
	return i + 1;
}

/// <summary>
/// 交换两个变量的内存里存储的数值。
/// </summary>
/// <param name="a">左边的变量。</param>
/// <param name="b">右边的变量。</param>
void swap(int *__restrict a, int *__restrict b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
