#include "Utils.h"

/// <summary>
/// ��ӡһ��һά���顣
/// </summary>
/// <param name="array">���顣</param>
/// <param name="length">�����Ԫ��������</param>
void print_array(int *array, int length) {
	printf("[");
	for (int i = 0; i < length; i++) {
		printf("%d, ", array[i]);
	}
	printf("\b\b]\n");
}
