#pragma once

#include <stdio.h>

unsigned long long fibonacci(int);

void entry(void) {
	printf("fib(%d) = %lld。\n", 3, fibonacci(3));
	printf("fib(%d) = %lld。\n", 6, fibonacci(6));
	printf("fib(%d) = %lld。\n", 10, fibonacci(10));
	printf("fib(%d) = %lld。\n", 25, fibonacci(25));
}

/// <summary>
/// 求得斐波那契数列的第 n 项的值。
/// </summary>
/// <param name="n">项。从 0 开始编号，分别是 0、1、1、2、3、5、8，……。</param>
/// <returns>结果。</returns>
static unsigned long long fibonacci(int n) {
	if (n == 0) {
		return 0;
	}
	if (n == 1) {
		return 1;
	}
	return fibonacci(n - 1) + fibonacci(n - 2);
}