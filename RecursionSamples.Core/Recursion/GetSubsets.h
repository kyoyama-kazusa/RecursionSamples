#pragma once

#include "Utils.h"
#include <stdio.h>

#define N 6
#define M 3
#define BUFFER_SIZE 20

void get_subsets(int, int, int *const, const int[N], int (*)[M], int *const);
int combination_of(int, int);
int factorial(int);

void entry(void) {
	const int values[N] = { 1, 2, 3, 4, 5, 6 };

	// Visual Studio 不支持 VLA（变长数组）特性，因为这里要用二维数组存结果
	// （整个是个大列表，每一个元素又是 M 个元素的数组），
	// 用 malloc 和 free 写起来有点费劲，我这里就不弄了，直接用原始的 #define 定义常量结果吧。
	int buffer[BUFFER_SIZE][M] = { { 0 } };
	int temp_array[M] = { 0 };
	int z = 0;
	get_subsets(N, M, temp_array, values, buffer, &z);

	printf("[\n");
	for (int i = 0; i < BUFFER_SIZE; i++) {
		printf("  ");
		print_array(buffer[i], M);
	}
	printf("\b\b]\n");
}

/// <summary>
/// 递归求得指定数字序列里的全部子集（数字不分先后顺序）。
/// </summary>
/// <param name="last">最后一个元素的索引（锚点）；初始为列表总长度。</param>
/// <param name="index">当前索引。</param>
/// <param name="temp_array">临时存储一下元素（临时缓冲区）。</param>
/// <param name="values">整个数字序列。</param>
/// <param name="result">记录结果的序列。需要预先分配内存。</param>
/// <param name="z">表示当前记录了多少个元素。</param>
static void get_subsets(int last, int index, int *const temp_array, const int values[N], int (*result)[M], int *const z) {
	for (int i = last; i >= index; i--) {
		temp_array[index - 1] = values[i - 1];
		if (index > 1) {
			// index != 0，说明前面有固定的数，但并非所有数字都固定，所以就递归算后面变动排列的数字。
			get_subsets(i - 1, index - 1, temp_array, values, result, z);
		}
		else {
			// index == 0 会走到这里，也就是说整个序列已经全部递归完成，走这里把结果导出。
			for (int j = 0; j < M; j++) {
				result[*z][j] = temp_array[j];
			}
			(*z)++;
		}
	}
}

/// <summary>
/// 求得 C(n, m) 的数值。
/// </summary>
/// <param name="n">数值 n（多少个元素）。</param>
/// <param name="m">数值 m（取其中多少个元素）。</param>
/// <returns>取出的总情况数。</returns>
static int combination_of(int n, int m) {
	return factorial(n) / (factorial(m) * factorial(n - m));
}

/// <summary>
/// 获取一个数的阶乘。
/// </summary>
/// <param name="n">数字。</param>
/// <returns>阶乘。</returns>
static int factorial(int n) {
	if (n == 1) {
		return 1;
	}
	return n * factorial(n - 1);
}