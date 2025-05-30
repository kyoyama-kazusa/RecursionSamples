#pragma once

#include "../DataStructures/SudokuGrid.h"
#include <stdlib.h>

bool backtrack_solve_grid_core(const SudokuGrid *const, SudokuGrid *const, int);
bool is_valid(const SudokuGrid *const, const int, const int);

void entry(void) {
	const char *const input = "..4.6..9.2..4..3....3..9...3...851...5....6....8..........7..8.9..2364....1.....7";

	SudokuGrid *const grid = parse_grid(input);
	print_grid(grid);

	// ����һ�ݡ�
	SudokuGrid solution = *grid;
	backtrack_solve_grid(grid, &solution);
	print_grid(&solution);

	free(grid);
}

/// <summary>
/// ʹ�û��ݷ����һ��������Ŀ��
/// </summary>
/// <param name="grid">������Ŀ��</param>
/// <param name="solution">�洢�����ָ�롣</param>
void backtrack_solve_grid(const SudokuGrid *const grid, SudokuGrid *const solution) {
	backtrack_solve_grid_core(grid, solution, 0);
}

static bool backtrack_solve_grid_core(const SudokuGrid *const grid, SudokuGrid *const solution, int next) {
	if (next == 81) {
		// ��Ŀ���ꡣ�˳���ǰ��ĵݹ顣
		return true;
	}

	if (solution->digits[next] == 0) {
		int r = next / 9, c = next % 9;

		// ���� 9 �������ԡ�
		for (int i = 0; i < 9; i++) {
			// ֱ��������� ++ ֱ���������Ͼ���ʼֵ���� 0��
			solution->digits[next]++;

			if (is_valid(solution, r, c)) {
				// �����Ϸ��������ݹ���һ�����ӡ�
				if (backtrack_solve_grid_core(grid, solution, next + 1)) {
					// �����Ŀ���꣬��ֱ���ߵ� true �Ǹ���֧��
					// ��ô���ǿ���ֱ�ӷ��� true���Է���������ݹ飬����һЩ���ô�������⡣
					return true;
				}
			}
		}

		// ���õ�ǰ��Ԫ�񣬱�ʾ�ݹ�������ӵ�ʱ��ʧ�ܡ�
		solution->digits[next] = 0;
	}
	else {
		// �����Ԫ��Ϊ�ո�������
		if (backtrack_solve_grid_core(grid, solution, next + 1)) {
			// �����Ŀ���꣬��ֱ���ߵ� true �Ǹ���֧��
			// ��ô���ǿ���ֱ�ӷ��� true���Է���������ݹ飬����һЩ���ô�������⡣
			return true;
		}
	}

	// �������ߵ�����˵����û�д��� return true ���߼���������Ҫ��ϸ�ķ���ÿһ����֧��ȥ��״̬��
	// ��Ȼû�� return true��Ҳ��˵����û���ꡣ��ô���� false ��ʾû�������
	return false;
}

static bool is_valid(const SudokuGrid *const grid, const int r, const int c) {
	int digit = grid->digits[r * 9 + c];
	for (int i = 0; i < 9; i++) {
		if (i != r && grid->digits[i * 9 + c] == digit
			|| i != c && grid->digits[r * 9 + i] == digit) {
			// ����л����ظ������� digit��
			return false;
		}
	}
	for (int ii = r / 3 * 3, i = ii; i < ii + 3; i++) {
		for (int jj = c / 3 * 3, j = jj; j < jj + 3; j++) {
			if ((i != r || j != c) && grid->digits[i * 9 + j] == digit) {
				// ��������ظ������� digit��
				return false;
			}
		}
	}

	// ��û�ظ������� true ��ʾ����
	return true;
}
