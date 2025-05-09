#pragma once

#include "../DataStructures/Stack.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial_stack_based(int value);

void entry(void) {
	printf("0 的阶乘是 %lld。\n", factorial_stack_based(0));
	printf("1 的阶乘是 %lld。\n", factorial_stack_based(1));
	printf("3 的阶乘是 %lld。\n", factorial_stack_based(3));
	printf("10 的阶乘是 %lld。\n", factorial_stack_based(10));
	printf("15 的阶乘是 %lld。\n", factorial_stack_based(15));
}

/// <summary>
/// 计算数字 n 的阶乘，用栈 + 循环模拟递归。
/// </summary>
/// <param name="n">数字。</param>
/// <returns>结果。</returns>
unsigned long long factorial_stack_based(int n) {
	Stack *stack = create_stack(4);

	unsigned long long result = 1;

	// 压入初始任务（从 n 开始逐步减到 0）。
	while (n != 0) {
		push(stack, n);
		n--;
	}

	// 依次弹栈将元素录入计算结果。
	while (get_stack_size(stack) != 0) {
		result *= pop(stack);
	}

	// 释放临时创建的栈。
	free(stack);

	// 返回结果。
	return result;
}
