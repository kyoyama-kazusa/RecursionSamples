#pragma once

#include <stdbool.h>

/// <summary>
/// 表示数独盘面。
/// </summary>
typedef struct {
	/// <summary>
	/// 表示里面存储的数值。
	/// </summary>
	int digits[81];
} SudokuGrid;

SudokuGrid *const parse_grid(const char *const);
void print_grid(const SudokuGrid *const);
void backtrack_solve_grid(const SudokuGrid *const, SudokuGrid *const);
