#pragma once

#include "../DataStructures/Utils.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// 统计指定数字的位数。
/// </summary>
/// <param name="n">数字。</param>
/// <returns>这个数有多少位。</returns>
int num_digits(long long n) {
	if (n == 0) return 1;
	int count = 0;
	while (n != 0) {
		n /= 10;
		count++;
	}
	return count;
}

/// <summary>
/// 将两个非负整数使用 Karatsuba 分治算法相乘。
/// </summary>
/// <param name="x">左边这个数。</param>
/// <param name="y">右边这个数。</param>
/// <returns>结果。</returns>
long long karatsuba(long long x, long long y) {
	// 如果两个数都是一位数就直接返回结果（递归出口）。
	if (x < 10 || y < 10) {
		return x * y;
	}

	// 计算两个数的位数大小。
	int n = MAX(num_digits(x), num_digits(y));
	int half = n / 2;

	// 将 x 和 y 拆分。
	long long pow10 = (long long)pow(10, half);
	long long high1 = x / pow10;
	long long low1 = x % pow10;
	long long high2 = y / pow10;
	long long low2 = y % pow10;

	// 三次递归调用。
	long long z0 = karatsuba(low1, low2);
	long long z1 = karatsuba(low1 + high1, low2 + high2);
	long long z2 = karatsuba(high1, high2);

	// 整合结果。
	return z2 * (long long)pow(10, 2 * half) + (z1 - z2 - z0) * pow10 + z0;
}

void entry(void) {
	long long a, b;
	printf("请输入两个数字用于相乘：");
	if (scanf("%lld %lld", &a, &b) != 2) {
		printf("输入有问题 - 必须有两个整数参与计算，中间用空格分隔。\n");
		return;
	}

	if (a < 0 || b < 0) {
		printf("请必须输入两个数字都是非负整数。\n");
		return;
	}

	long long result = karatsuba(a, b);
	printf("结果：%lld\n", result);
}
