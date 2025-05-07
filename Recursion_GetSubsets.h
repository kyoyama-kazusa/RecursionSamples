#pragma once

#include "Utils.h"
#include <stdio.h>

#define N 6
#define M 3
#define BUFFER_SIZE 20

void get_subsets(int, int, int *const, const int[N], int (*)[M], int *const);
int combination_of(int, int);
int factorial(int);

void entry(void) {
	const int values[N] = { 1, 2, 3, 4, 5, 6 };

	// Visual Studio ��֧�� VLA���䳤���飩���ԣ���Ϊ����Ҫ�ö�ά�������
	// �������Ǹ����б�ÿһ��Ԫ������ M ��Ԫ�ص����飩��
	// �� malloc �� free д�����е�Ѿ���������Ͳ�Ū�ˣ�ֱ����ԭʼ�� #define ���峣������ɡ�
	int buffer[BUFFER_SIZE][M] = { { 0 } };
	int temp_array[M] = { 0 };
	int z = 0;
	get_subsets(N, M, temp_array, values, buffer, &z);

	printf("[\n");
	for (int i = 0; i < BUFFER_SIZE; i++) {
		printf("  ");
		print_array(buffer[i], M);
	}
	printf("\b\b]\n");
}

/// <summary>
/// �ݹ����ָ�������������ȫ���Ӽ������ֲ����Ⱥ�˳�򣩡�
/// </summary>
/// <param name="last">���һ��Ԫ�ص�������ê�㣩����ʼΪ�б��ܳ��ȡ�</param>
/// <param name="index">��ǰ������</param>
/// <param name="temp_array">��ʱ�洢һ��Ԫ�أ���ʱ����������</param>
/// <param name="values">�����������С�</param>
/// <param name="result">��¼��������С���ҪԤ�ȷ����ڴ档</param>
/// <param name="z">��ʾ��ǰ��¼�˶��ٸ�Ԫ�ء�</param>
static void get_subsets(int last, int index, int *const temp_array, const int values[N], int (*result)[M], int *const z) {
	for (int i = last; i >= index; i--) {
		temp_array[index - 1] = values[i - 1];
		if (index > 1) {
			// index != 0��˵��ǰ���й̶��������������������ֶ��̶������Ծ͵ݹ������䶯���е����֡�
			get_subsets(i - 1, index - 1, temp_array, values, result, z);
		}
		else {
			// index == 0 ���ߵ����Ҳ����˵���������Ѿ�ȫ���ݹ���ɣ�������ѽ��������
			for (int j = 0; j < M; j++) {
				result[*z][j] = temp_array[j];
			}
			(*z)++;
		}
	}
}

/// <summary>
/// ��� C(n, m) ����ֵ��
/// </summary>
/// <param name="n">��ֵ n�����ٸ�Ԫ�أ���</param>
/// <param name="m">��ֵ m��ȡ���ж��ٸ�Ԫ�أ���</param>
/// <returns>ȡ�������������</returns>
static int combination_of(int n, int m) {
	return factorial(n) / (factorial(m) * factorial(n - m));
}

/// <summary>
/// ��ȡһ�����Ľ׳ˡ�
/// </summary>
/// <param name="n">���֡�</param>
/// <returns>�׳ˡ�</returns>
static int factorial(int n) {
	if (n == 1) {
		return 1;
	}
	return n * factorial(n - 1);
}