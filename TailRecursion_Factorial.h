#pragma once

#include <stdio.h>

unsigned long long factorial(int, unsigned long long);

void entry(void) {
	printf("0 的阶乘是 %lld。\n", factorial(0, 1));
	printf("1 的阶乘是 %lld。\n", factorial(1, 1));
	printf("3 的阶乘是 %lld。\n", factorial(3, 1));
	printf("10 的阶乘是 %lld。\n", factorial(10, 1));
	printf("15 的阶乘是 %lld。\n", factorial(15, 1));
}

/// <summary>
/// 尾递归函数。尾递归的递归逻辑必须在所有运算的最后一步，比如这个地方。
/// </summary>
/// <param name="value">数值。</param>
/// <param name="accumulator">积累结果。</param>
/// <returns>结果。</returns>
static unsigned long long factorial(int value, unsigned long long accumulator) {
	if (value == 0) {
		// 递归出口 - 直接返回传入的参数。
		return accumulator;
	}

	// 进行尾递归操作 - 这里要让参数接收结果以让递归逻辑一定在 return 语句执行的时候作为最后一步执行。
	// 即使你这里写 return factorial(value - 1) * value 也不行，
	// 因为这样会多一步 * value 操作然后才返回。
	return factorial(value - 1, value * accumulator);
}
