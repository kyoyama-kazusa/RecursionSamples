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
/// ִ�й鲢����
/// </summary>
/// <param name="arr">���顣</param>
/// <param name="left">����������½磩��</param>
/// <param name="right">�ұ��������Ͻ磩��</param>
void merge_sort(int *arr, int left, int right) {
	if (left < right) {
		int middle = (left + right) >> 1;
		merge_sort(arr, left, middle);
		merge_sort(arr, middle + 1, right);
		merge(arr, left, middle, right);
	}
}

/// <summary>
/// �ϲ����������Ԫ�ء�
/// </summary>
/// <param name="arr">���顣</param>
/// <param name="left">���������</param>
/// <param name="middle">�м�ָ���������</param>
/// <param name="right">�ұ�������</param>
void merge(int *arr, int left, int middle, int right) {
	int n1 = middle - left + 1;
	int n2 = right - middle;

	// ������ʱ���顣
	int *left_part = (int *)malloc(n1 * sizeof(int));
	int *right_part = (int *)malloc(n2 * sizeof(int));
	if (!left_part || !right_part) {
		printf("�ڴ����ʧ�ܡ�\n");
		exit(-1);
	}

	// ��Ԫ�ؿ�������������ʱ��������������ߣ���
	int i, j, k;
	for (i = 0; i < n1; i++) {
		left_part[i] = arr[left + i];
	}
	for (j = 0; j < n2; j++) {
		right_part[j] = arr[middle + 1 + j];
	}

	// ����ʱ���飬�ϲ��� arr[left..right] ��һ�����
	i = 0; // ��һ��������ĵ�һ��Ԫ�ص�������
	j = 0; // �ڶ���������ĵ�һ��Ԫ�ص�������
	k = left; // �ϲ�������ĵ�һ��Ԫ�ص�������

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

	// �����鿽���� arr��left_part ���֣���
	while (i < n1) {
		arr[k] = left_part[i];
		i++;
		k++;
	}

	// �����鿽���� arr��right_part ���֣���
	while (j < n2) {
		arr[k] = right_part[j];
		j++;
		k++;
	}

	// �ͷ���ʱ������ڴ档
	free(left_part);
	free(right_part);
}
