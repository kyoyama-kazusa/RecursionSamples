#pragma once

#include <stdio.h>

unsigned long long fibonacci(int);

void entry(void) {
	printf("fib(%d) = %lld��\n", 3, fibonacci(3));
	printf("fib(%d) = %lld��\n", 6, fibonacci(6));
	printf("fib(%d) = %lld��\n", 10, fibonacci(10));
	printf("fib(%d) = %lld��\n", 25, fibonacci(25));
}

/// <summary>
/// ���쳲��������еĵ� n ���ֵ��
/// </summary>
/// <param name="n">��� 0 ��ʼ��ţ��ֱ��� 0��1��1��2��3��5��8��������</param>
/// <returns>�����</returns>
static unsigned long long fibonacci(int n) {
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}