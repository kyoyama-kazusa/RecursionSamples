/*
* 阶乘运算
* 
* 给定一个数，求这个数的阶乘。
* 一个数的阶乘等于从 1 开始，到求的这个数字本身的所有数的乘积。如 5 的阶乘等于 1 * 2 * 3 * 4 * 5，即 120。
* 
* 阶乘运算非常适合用于初学递归，递归的本质是找一个迭代函数，能让它的前一个状态通过运算达到后一个状态，并且前后两个状态的计算逻辑是一致的。
* 显然，f(n - 1) * n 就等于 f(n)，而 f(n - 1) 的得来又可以等于 f(n - 2) * (n - 1)，所以这么个递推式子就找到了。
* 递归的本质是用相同的函数（此处是这个 f）来完成重复操作，只不过每一次的数据规模都跟原来不同，直到这个 f 可以直接返回结果时结束。
*/

#pragma once

#include <stdio.h>

unsigned long long factorial(int value);

void entry(void) {
	printf("0 的阶乘是 %lld。\n", factorial(0));
	printf("1 的阶乘是 %lld。\n", factorial(1));
	printf("3 的阶乘是 %lld。\n", factorial(3));
	printf("10 的阶乘是 %lld。\n", factorial(10));
	printf("15 的阶乘是 %lld。\n", factorial(15));
}

/// <summary>
/// 求得指定数字的阶乘。
/// </summary>
/// <param name="value">数值。</param>
/// <returns>阶乘结果。</returns>
static unsigned long long factorial(int value) {
	if (value == 0) {
		return 1;
	}
	return value * factorial(value - 1);
}