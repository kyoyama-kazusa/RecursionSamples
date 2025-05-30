/*
* 计算一个数是否是偶数
* 
* 这显然可以不用递归，但是故意我实现一下。实现的方式自然是找到一个初始状态，强制告诉他是定值；然后让这个数减小规模直到这个定值结果能被返回。
* 比如说计算 4 是否是偶数，那么它的状态 f(4) 显然等于它前一个状态 f(3) 的取反情况（因为奇偶交替）。所以 f(4) = !f(3)，那么传递过程不就来了吗。
*/

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
