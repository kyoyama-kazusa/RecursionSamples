#pragma once

#include "../DataStructures/Utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// ͳ��ָ�����ֵ�λ����
/// </summary>
/// <param name="n">���֡�</param>
/// <returns>������ж���λ��</returns>
int num_digits(long long n) {
	if (n == 0) return 1;
	int count = 0;
	while (n != 0) {
		n /= 10;
		count++;
	}
	return count;
}

/// <summary>
/// �������Ǹ�����ʹ�� Karatsuba �����㷨��ˡ�
/// </summary>
/// <param name="x">����������</param>
/// <param name="y">�ұ��������</param>
/// <returns>�����</returns>
long long karatsuba(long long x, long long y) {
	// �������������һλ����ֱ�ӷ��ؽ�����ݹ���ڣ���
	if (x < 10 || y < 10) {
		return x * y;
	}

	// ������������λ����С��
	int n = MAX(num_digits(x), num_digits(y));
	int half = n / 2;

	// �� x �� y ��֡�
	long long pow10 = (long long)pow(10, half);
	long long high1 = x / pow10;
	long long low1 = x % pow10;
	long long high2 = y / pow10;
	long long low2 = y % pow10;

	// ���εݹ���á�
	long long z0 = karatsuba(low1, low2);
	long long z1 = karatsuba(low1 + high1, low2 + high2);
	long long z2 = karatsuba(high1, high2);

	// ���Ͻ����
	return z2 * (long long)pow(10, 2 * half) + (z1 - z2 - z0) * pow10 + z0;
}

void entry(void) {
	long long a, b;
	printf("��������������������ˣ�");
	if (scanf("%lld %lld", &a, &b) != 2) {
		printf("���������� - ��������������������㣬�м��ÿո�ָ���\n");
		return;
	}

	if (a < 0 || b < 0) {
		printf("����������������ֶ��ǷǸ�������\n");
		return;
	}

	long long result = karatsuba(a, b);
	printf("�����%lld\n", result);
}
