#include "Utils.h"

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
