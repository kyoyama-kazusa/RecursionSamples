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
/// ִ�п�������
/// </summary>
/// <param name="array">���顣</param>
/// <param name="left">���������</param>
/// <param name="right">�ұ�������</param>
void quick_sort(int *array, int left, int right) {
	if (left < right) {
		// �������ҳ�ê�㣬��ߵ�����С��ê�㣬�ұߵ���������ê�㡣
		int pivot = partition(array, left, right);

		// �Ի�׼���������������ݹ�ִ������������
		quick_sort(array, left, pivot - 1);
		quick_sort(array, pivot + 1, right);
	}
}

/// <summary>
/// �������ȷֳ�������������ߵ�С��ָ����ֵ���ұߵĴ���ָ����ֵ��
/// </summary>
/// <param name="array">���顣</param>
/// <param name="left">���������</param>
/// <param name="right">�ұ�������</param>
/// <returns>�м������λ�á�</returns>
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
/// ���������������ڴ���洢����ֵ��
/// </summary>
/// <param name="a">��ߵı�����</param>
/// <param name="b">�ұߵı�����</param>
void swap(int *__restrict a, int *__restrict b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
