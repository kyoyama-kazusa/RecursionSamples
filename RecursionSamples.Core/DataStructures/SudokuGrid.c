#include "SudokuGrid.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
