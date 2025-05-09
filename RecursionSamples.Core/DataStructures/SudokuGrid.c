#include "SudokuGrid.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool backtrack_solve_grid_core(const SudokuGrid *const, SudokuGrid *const, int);
bool is_valid(const SudokuGrid *const, const int, const int);

/// <summary>
/// ����һ���ַ������������Ϊ�ȼ۵�����������Ϣ�������ء�
/// </summary>
/// <param name="str">һ�����������ַ�����</param>
/// <returns>������Ϣ��������Ҫ free �����ͷš�</returns>
SudokuGrid *const parse_grid(const char *const str) {
	if (strlen(str) != 81) {
		puts("�ַ������ȱ����� 81��");
		exit(-2);
	}

	SudokuGrid *result = (SudokuGrid *)malloc(sizeof(SudokuGrid));
	if (!result) {
		puts("�ڴ����ʧ�ܡ�");
		exit(-1);
	}

	for (int i = 0; i < 81; i++) {
		int digit = str[i] == '.' || str[i] == '0' ? 0 : str[i] >= '0' && str[i] <= '9' ? str[i] - '0' : -1;
		if (digit == -1) {
			puts("��ʼ��ʧ�ܣ��ַ��������쳣�ַ� - �����������ֻ�С���㡣");
			exit(-2);
		}
		result->digits[i] = digit;
	}

	return result;
}

/// <summary>
/// ʹ�û��ݷ����һ��������Ŀ��
/// </summary>
/// <param name="grid">������Ŀ��</param>
/// <param name="solution">�洢�����ָ�롣</param>
void backtrack_solve_grid(const SudokuGrid *const grid, SudokuGrid *const solution) {
	backtrack_solve_grid_core(grid, solution, 0);
}

/// <summary>
/// ��ӡһ��������Ŀ��
/// </summary>
/// <param name="grid">������Ŀ��</param>
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
