#pragma once

#include "../DataStructures/SudokuGrid.h"
#include <stdlib.h>

bool backtrack_solve_grid_core(const SudokuGrid *const, SudokuGrid *const, int);
bool is_valid(const SudokuGrid *const, const int, const int);

void entry(void) {
	const char *const input = "..4.6..9.2..4..3....3..9...3...851...5....6....8..........7..8.9..2364....1.....7";

	SudokuGrid *const grid = parse_grid(input);
	print_grid(grid);

	// 拷贝一份。
	SudokuGrid solution = *grid;
	backtrack_solve_grid(grid, &solution);
	print_grid(&solution);

	free(grid);
}

/// <summary>
/// 使用回溯法解决一个数独题目。
/// </summary>
/// <param name="grid">数独题目。</param>
/// <param name="solution">存储结果的指针。</param>
void backtrack_solve_grid(const SudokuGrid *const grid, SudokuGrid *const solution) {
	backtrack_solve_grid_core(grid, solution, 0);
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
