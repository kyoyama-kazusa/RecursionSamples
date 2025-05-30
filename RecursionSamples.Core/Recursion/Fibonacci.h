/*
* 斐波那契数列
*
* 斐波那契数列就是从 0 和 1 开始的、每后一个数都等于它前面的两个数的和，这么个数列。
* 这个数列非常不方便写成一个函数表达式（因为特别复杂，带黄金分割比的那个式子，各位可以查一下）；但是它的递推函数非常好找：f(n) = f(n - 1) + f(n - 2)。
* 只要我们能够确保递归的开始能立即返回结果的那个位置有一个确切的数值（如 0 和 1 是初始数），那么我们就把他强制直接返回，这么个递归就构造好了。
*/

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