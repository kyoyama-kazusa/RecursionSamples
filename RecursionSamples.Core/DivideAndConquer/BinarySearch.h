#pragma once

#include <stdio.h>
#include <stdlib.h>

#define N 5

int cmp(const void *__restrict, const void *__restrict);
int binary_search(const int *const, int, int, int, int);

void entry(void) {
	// 定义一个数组。数组必须从小到大排列。
	int arr[N] = { 1, 3, 5, 7, 9 };

	// 如果不是有序的，就需要排序。
	// qsort 函数执行的是快速排序，但元素可以任意指定，所以需要带有额外的参数信息参与比较过程，如数组长度、元素大小和比较规则等。
	qsort(arr, N, sizeof(int), cmp);

	// 打印结果。
	printf("5 位于索引 [%d]。\n", binary_search(arr, N, 5, 0, N - 1));
	printf("2 位于索引 [%d]。\n", binary_search(arr, N, 2, 0, N - 1));
}

/// <summary>
/// 比较器函数。
/// </summary>
/// <param name="left">左边的元素，一定是 int。</param>
/// <param name="right">右边的元素，一定是 int。</param>
/// <returns>比较结果。</returns>
static int cmp(const void *__restrict left, const void *__restrict right) {
	// 将两个指针强制转换为 int * 后取出指向的数值。
	return *(int *)left - *(int *)right;
}

/// <summary>
/// 二分查找算法。二分查找算法依赖于数组必须已经有序，否则无法利用左边小右边大的原则来对元素进行查找。
/// </summary>
/// <param name="arr">数组。</param>
/// <param name="n">数组的元素个数。</param>
/// <param name="target">需要查找的数值。</param>
/// <param name="low_index">最小索引。</param>
/// <param name="high_index">最大索引。</param>
/// <returns>所在的索引。如果找不着数值，则返回 -1。</returns>
static int binary_search(const int *const arr, int length, int target, int low_index, int high_index) {
	while (low_index <= high_index) {
		// 这里使用 left + (right - left) / 2 是为了避免索引溢出。
		// 使用 (left + right) / 2 的时候，如果 left + right 超出 int 大小，就会出现溢出。
		// 然后 mid 取值就不对，因为索引已经超出了 arr 的范围。
		int mid = low_index + (high_index - low_index) / 2;
		if (arr[mid] == target) {
			return mid; // 找到目标，返回索引。
		}

		if (arr[mid] < target) {
			// 目标在右半部分。
			return binary_search(arr, length, target, mid + 1, high_index);
		}

		// 目标在左半部分。
		return binary_search(arr, length, target, low_index, mid - 1);
	}

	// 没找着，返回 -1。
	return -1;
}
