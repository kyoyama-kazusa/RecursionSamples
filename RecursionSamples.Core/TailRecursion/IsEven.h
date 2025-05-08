#pragma once

#include <stdio.h>
#include <stdbool.h>

bool is_even(int);
bool is_even_cached_entry(int);
bool is_even_cached(int, bool);

void entry(void) {
	printf("请输入递归计算模式（0 - 普通尾递归；1 - 带参数尾递归），结果没啥区别：\n");

	int mode;
	int ignored = scanf("%d", &mode);
	bool (*function_pointer)(int) = mode == 0 ? is_even : is_even_cached_entry;
	printf("0 %s偶数。\n", function_pointer(0) ? "是" : "不是");
	printf("3 %s偶数。\n", function_pointer(3) ? "是" : "不是");
	printf("10 %s偶数。\n", function_pointer(10) ? "是" : "不是");
	printf("17 %s偶数。\n", function_pointer(17) ? "是" : "不是");
	printf("160 %s偶数。\n", function_pointer(160) ? "是" : "不是");
}

/// <summary>
/// 判断一个数是否是偶数。
/// </summary>
/// <param name="value">数值。</param>
/// <returns>是否是偶数。</returns>
static bool is_even(int value) {
	if (value == 0) {
		return true;
	}
	if (value == 1) {
		return false;
	}

	// 直接一口气跳两个数，以保证不用传递参数的同时就能保证递归是最后一步。
	return is_even(value - 2);
}

static bool is_even_cached_entry(int value) {
	return is_even_cached(value, true);
}

/// <summary>
/// 用尾递归带参数模式实现判断一个数是否是偶数。
/// </summary>
/// <param name="value">数值。</param>
/// <param name="result">临时存的结果。这个参数初始的时候给 true。</param>
/// <returns>是否是偶数。</returns>
static bool is_even_cached(int value, bool result) {
	if (value == 0) {
		return result;
	}
	if (value == 1) {
		return !result;
	}

	// 用参数存储结果，以优先保证 !result 结果先算出后传入，使得函数总是在最后一步执行。
	return is_even_cached(value - 1, !result);
}