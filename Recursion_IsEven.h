#pragma once

#include <stdbool.h>
#include <stdio.h>

bool is_even(int);

void entry(void) {
	printf("0 %s偶数。\n", is_even(0) ? "是" : "不是");
	printf("3 %s偶数。\n", is_even(3) ? "是" : "不是");
	printf("10 %s偶数。\n", is_even(10) ? "是" : "不是");
	printf("17 %s偶数。\n", is_even(17) ? "是" : "不是");
	printf("160 %s偶数。\n", is_even(160) ? "是" : "不是");
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
	return !is_even(value - 1);
}
