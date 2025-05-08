#pragma once

#include "Utils.h"
#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *, int, int);
void merge(int *, int, int, int);

void entry(void) {
	int arr[9] = { 3, 8, 1, 6, 5, 4, 7, 2, 9 };
	print_array(arr, 9);

	merge_sort(arr, 0, 8);
	print_array(arr, 9);
}

/// <summary>
/// 执行归并排序。
/// </summary>
/// <param name="arr">数组。</param>
/// <param name="left">左边索引（下界）。</param>
/// <param name="right">右边索引（上界）。</param>
void merge_sort(int *arr, int left, int right) {
	if (left < right) {
		int middle = (left + right) >> 1;
		merge_sort(arr, left, middle);
		merge_sort(arr, middle + 1, right);
		merge(arr, left, middle, right);
	}
}

/// <summary>
/// 合并两个数组的元素。
/// </summary>
/// <param name="arr">数组。</param>
/// <param name="left">左边索引。</param>
/// <param name="middle">中间分隔的索引。</param>
/// <param name="right">右边索引。</param>
void merge(int *arr, int left, int middle, int right) {
	int n1 = middle - left + 1;
	int n2 = right - middle;

	// 创建临时数组。
	int *left_part = (int *)malloc(n1 * sizeof(int));
	int *right_part = (int *)malloc(n2 * sizeof(int));
	if (!left_part || !right_part) {
		printf("内存分配失败。\n");
		exit(-1);
	}

	// 将元素拷贝到这两个临时数组里（分左右两边）。
	int i, j, k;
	for (i = 0; i < n1; i++) {
		left_part[i] = arr[left + i];
	}
	for (j = 0; j < n2; j++) {
		right_part[j] = arr[middle + 1 + j];
	}

	// 将临时数组，合并回 arr[left..right] 这一部分里。
	i = 0; // 第一个子数组的第一个元素的索引。
	j = 0; // 第二个子数组的第一个元素的索引。
	k = left; // 合并子数组的第一个元素的索引。

	while (i < n1 && j < n2) {
		if (left_part[i] <= right_part[j]) {
			arr[k] = left_part[i];
			i++;
		}
		else {
			arr[k] = right_part[j];
			j++;
		}
		k++;
	}

	// 将数组拷贝回 arr（left_part 部分）。
	while (i < n1) {
		arr[k] = left_part[i];
		i++;
		k++;
	}

	// 将数组拷贝回 arr（right_part 部分）。
	while (j < n2) {
		arr[k] = right_part[j];
		j++;
		k++;
	}

	// 释放临时数组的内存。
	free(left_part);
	free(right_part);
}
