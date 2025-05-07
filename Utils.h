#pragma once

#include <stdio.h>

#ifndef MAX
// 定义求得两个参数哪一个大。
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif // !MAX
#ifndef MIN
// 定义求得两个参数哪一个小。
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif // !MIN

/// <summary>
/// 打印一个一维数组。
/// </summary>
/// <param name="array">数组。</param>
/// <param name="length">数组的元素数量。</param>
void print_array(int *array, int length) {
	printf("[");
	for (int i = 0; i < length; i++) {
		printf("%d, ", array[i]);
	}
	printf("\b\b]\n");
}
