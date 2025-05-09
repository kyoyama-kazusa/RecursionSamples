#include "SudokuGrid.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool backtrack_solve_grid_core(const SudokuGrid *const, SudokuGrid *const, int);
bool is_valid(const SudokuGrid *const, const int, const int);

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
/// 使用回溯法解决一个数独题目。
/// </summary>
/// <param name="grid">数独题目。</param>
/// <param name="solution">存储结果的指针。</param>
void backtrack_solve_grid(const SudokuGrid *const grid, SudokuGrid *const solution) {
	backtrack_solve_grid_core(grid, solution, 0);
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

static bool backtrack_solve_grid_core(const SudokuGrid *const grid, SudokuGrid *const solution, int next) {
	if (next == 81) {
		// 题目解完。退出当前层的递归。
		return true;
	}

	if (solution->digits[next] == 0) {
		int r = next / 9, c = next % 9;

		// 尝试 9 个可能性。
		for (int i = 0; i < 9; i++) {
			// 直接填。这里用 ++ 直接自增，毕竟初始值就是 0。
			solution->digits[next]++;

			if (is_valid(solution, r, c)) {
				// 填数合法，继续递归下一个格子。
				if (backtrack_solve_grid_core(grid, solution, next + 1)) {
					// 如果题目解完，会直接走到 true 那个分支。
					// 那么我们可以直接返回 true，以防后面无穷递归，或者一些不好处理的问题。
					return true;
				}
			}
		}

		// 重置当前单元格，表示递归这个格子的时候失败。
		solution->digits[next] = 0;
	}
	else {
		// 这个单元格不为空格，跳过。
		if (backtrack_solve_grid_core(grid, solution, next + 1)) {
			// 如果题目解完，会直接走到 true 那个分支。
			// 那么我们可以直接返回 true，以防后面无穷递归，或者一些不好处理的问题。
			return true;
		}
	}

	// 代码能走到这里说明它没有触发 return true 的逻辑。这里需要你细心分析每一个分支出去的状态。
	// 既然没有 return true，也就说明题没解完。那么返回 false 表示没完成它。
	return false;
}

static bool is_valid(const SudokuGrid *const grid, const int r, const int c) {
	int digit = grid->digits[r * 9 + c];
	for (int i = 0; i < 9; i++) {
		if (i != r && grid->digits[i * 9 + c] == digit
			|| i != c && grid->digits[r * 9 + i] == digit) {
			// 这个行或列重复出现了 digit。
			return false;
		}
	}
	for (int ii = r / 3 * 3, i = ii; i < ii + 3; i++) {
		for (int jj = c / 3 * 3, j = jj; j < jj + 3; j++) {
			if ((i != r || j != c) && grid->digits[i * 9 + j] == digit) {
				// 这个宫里重复出现了 digit。
				return false;
			}
		}
	}

	// 都没重复，返回 true 表示允许。
	return true;
}
