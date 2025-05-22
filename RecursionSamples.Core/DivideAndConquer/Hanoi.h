#pragma once

#include <stdio.h>
#include <string.h>

/// <summary>
/// 定义一个打印函数，专门用于打印柱子从参数 #1 往参数 #2 移动的过程。
/// </summary>
typedef void (*ColumnMovingPrinter)(const char *const, const char *const);

void printer(const char *const, const char *const);
void solve(int, const char *const, const char *const, const char *const, ColumnMovingPrinter);

void entry(void) {
	solve(3, "初始列", "目标列", "辅助列", printer);
}

static void printer(const char *const base, const char *const target) {
	char sequences[3] = { 'a', 'b', 'c' };
	char baseColumnChar = strcmp(base, "初始列") == 0 ? sequences[0] : strcmp(base, "辅助列") == 0 ? sequences[1] : sequences[2];
	char targetColumnChar = strcmp(target, "初始列") == 0 ? sequences[0] : strcmp(target, "辅助列") == 0 ? sequences[1] : sequences[2];
	printf("移动%s的圆盘到%s去（%c -> %c）\n", base, target, baseColumnChar, targetColumnChar);
}

static void solve(
	int count,
	const char *const base,
	const char *const target,
	const char *const auxiliary,
	ColumnMovingPrinter printer
) {
	if (count == 0) {
		// 递归完成。
		return;
	}

	// 先递归移动的是非最底层圆盘的每一个。
	solve(count - 1, base, auxiliary, target, printer);

	// 到这里就说明底层圆盘没动，但上面全部都到辅助列了。
	// 打印底层圆盘的信息，说明移动走向。
	printer(base, target);

	// 然后递归移动剩下的部分。因为此时辅助列放满了非底层的圆盘，而目标列已经有一个底层圆盘了，所以现在递归剩下的就行了。
	solve(count - 1, auxiliary, base, target, printer);
}
