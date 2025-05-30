#pragma once

#include <stdio.h>
#include <stdlib.h>

#define N 5

int cmp(const void *__restrict, const void *__restrict);
int binary_search(const int *const, int, int, int, int);

void entry(void) {
	// ����һ�����顣��������С�������С�
	int arr[N] = { 1, 3, 5, 7, 9 };

	// �����������ģ�����Ҫ����
	// qsort ����ִ�е��ǿ������򣬵�Ԫ�ؿ�������ָ����������Ҫ���ж���Ĳ�����Ϣ����ȽϹ��̣������鳤�ȡ�Ԫ�ش�С�ͱȽϹ���ȡ�
	qsort(arr, N, sizeof(int), cmp);

	// ��ӡ�����
	printf("5 λ������ [%d]��\n", binary_search(arr, N, 5, 0, N - 1));
	printf("2 λ������ [%d]��\n", binary_search(arr, N, 2, 0, N - 1));
}

/// <summary>
/// �Ƚ���������
/// </summary>
/// <param name="left">��ߵ�Ԫ�أ�һ���� int��</param>
/// <param name="right">�ұߵ�Ԫ�أ�һ���� int��</param>
/// <returns>�ȽϽ����</returns>
static int cmp(const void *__restrict left, const void *__restrict right) {
	// ������ָ��ǿ��ת��Ϊ int * ��ȡ��ָ�����ֵ��
	return *(int *)left - *(int *)right;
}

/// <summary>
/// ���ֲ����㷨�����ֲ����㷨��������������Ѿ����򣬷����޷��������С�ұߴ��ԭ������Ԫ�ؽ��в��ҡ�
/// </summary>
/// <param name="arr">���顣</param>
/// <param name="n">�����Ԫ�ظ�����</param>
/// <param name="target">��Ҫ���ҵ���ֵ��</param>
/// <param name="low_index">��С������</param>
/// <param name="high_index">���������</param>
/// <returns>���ڵ�����������Ҳ�����ֵ���򷵻� -1��</returns>
static int binary_search(const int *const arr, int length, int target, int low_index, int high_index) {
	while (low_index <= high_index) {
		// ����ʹ�� left + (right - left) / 2 ��Ϊ�˱������������
		// ʹ�� (left + right) / 2 ��ʱ����� left + right ���� int ��С���ͻ���������
		// Ȼ�� mid ȡֵ�Ͳ��ԣ���Ϊ�����Ѿ������� arr �ķ�Χ��
		int mid = low_index + (high_index - low_index) / 2;
		if (arr[mid] == target) {
			return mid; // �ҵ�Ŀ�꣬����������
		}

		if (arr[mid] < target) {
			// Ŀ�����Ұ벿�֡�
			return binary_search(arr, length, target, mid + 1, high_index);
		}

		// Ŀ������벿�֡�
		return binary_search(arr, length, target, low_index, mid - 1);
	}

	// û���ţ����� -1��
	return -1;
}
