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