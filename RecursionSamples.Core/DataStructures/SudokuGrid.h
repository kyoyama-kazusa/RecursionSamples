#pragma once

#include <stdbool.h>

/// <summary>
/// ��ʾ�������档
/// </summary>
typedef struct {
	/// <summary>
	/// ��ʾ����洢����ֵ��
	/// </summary>
	int digits[81];
} SudokuGrid;

SudokuGrid *const parse_grid(const char *const);
void print_grid(const SudokuGrid *const);
void backtrack_solve_grid(const SudokuGrid *const, SudokuGrid *const);
