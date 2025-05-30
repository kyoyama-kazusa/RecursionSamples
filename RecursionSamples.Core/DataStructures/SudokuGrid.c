#include "SudokuGrid.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// <summary>
/// 解析一个字符串，将其解析为等价的数独盘面信息，并返回。
/// </summary>
/// <param name="str">一个数独盘面字符串。</param>
/// <returns>盘面信息。盘面需要 free 进行释放。</returns>
SudokuGrid *const parse_grid(const char *const str) {
	if (strlen(str) != 81) {
		puts("字符串长度必须是 81。");
		exit(-2);
	}

	SudokuGrid *result = (SudokuGrid *)malloc(sizeof(SudokuGrid));
	if (!result) {
		puts("内存分配失败。");
		exit(-1);
	}

	for (int i = 0; i < 81; i++) {
		int digit = str[i] == '.' || str[i] == '0' ? 0 : str[i] >= '0' && str[i] <= '9' ? str[i] - '0' : -1;
		if (digit == -1) {
			puts("初始化失败：字符串包含异常字符 - 它必须是数字或小数点。");
			exit(-2);
		}
		result->digits[i] = digit;
	}

	return result;
}

/// <summary>
/// 打印一个数独题目。
/// </summary>
/// <param name="grid">数独题目。</param>
void print_grid(const SudokuGrid *const grid) {
	for (int i = 0; i < 81; i++) {
		printf("%d", grid->digits[i]);
		if ((i + 1) % 9 == 0) {
			printf("\n");
		}
	}
	printf("\n");
}
