#include "TicTaeToeBoard.h"
#include <stdbool.h>
#include <stdio.h>

/// <summary>
/// ��ʾ���п���ʤ����������õ�Ԫ��������ʾ����
/// </summary>
static const int win_conditions[8][3] = {
	{ 0, 1, 2 },
	{ 3, 4, 5 },
	{ 6, 7, 8 },
	{ 0, 3, 6 },
	{ 1, 4, 7 },
	{ 2, 5, 8 },
	{ 0, 4, 8 },
	{ 2, 4, 6 }
};


/// <summary>
/// ��ʼ��һ�����档
/// </summary>
/// <param name="board">���档</param>
void initialize_tic_tac_toe_board(TicTacToeBoard *const board) {
	for (int i = 0; i < 9; i++) {
		board->board[i] = PLACEHOLDER_CELL;
	}
}

/// <summary>
/// ��ӡһ�����̡�
/// </summary>
/// <param name="board">���̡�</param>
void print_tic_tac_toe_board(const TicTacToeBoard *const board) {
	printf(".---.---.---.\n");
	printf("| %c | %c | %c |\n", board->board[0], board->board[1], board->board[2]);
	printf(":---+---+---:\n");
	printf("| %c | %c | %c |\n", board->board[3], board->board[4], board->board[5]);
	printf(":---+---+---:\n");
	printf("| %c | %c | %c |\n", board->board[6], board->board[7], board->board[8]);
	printf("'---'---'---'\n");
}

/// <summary>
/// ����ָ�������̻�ȡ�����ӵ�λ�ã�Ȼ����һ�������������ʾ������У�������һ�����ֱ�ʾ������ó��ȡ�
/// </summary>
/// <param name="board">�������ݡ�</param>
/// <param name="positions_buffer">
/// <para>���������洢�������֤���ٿ��Է��� 9 ��Ԫ�أ���</para>
/// <para>����Ƿ� Visual Studio ���������� C99 �ġ�int positions_buffer[static 9]���﷨��ʾ����������Ԫ�����ٵ� 9 ����</para>
/// </param>
/// <param name="available_positions_count">��ʾ���� positions_buffer ���õ�Ԫ�ظ�����ǰ����Ԫ�ؿ��ã���</param>
void get_available_moves(const TicTacToeBoard *const board, int *const positions_buffer, int *available_positions_count) {
	// ��ʼ��������
	*available_positions_count = 0;

	// ѭ�� 9 ��λ�ÿ����ǲ��ǿո�����ǣ���ѡȡ����Ϊ����λ�á�
	for (int i = 0; i < 9; i++) {
		if (board->board[i] == PLACEHOLDER_CELL) {
			positions_buffer[(*available_positions_count)++] = i;
		}
	}
}

/// <summary>
/// ���ָ����ң����� player_char �����Ӧ���ʹ�õķ��ţ��Ƿ�ʤ����
/// </summary>
/// <param name="board">�������ݡ�</param>
/// <param name="player_char">��ҵĴ��÷��š�</param>
/// <returns>�Ƿ�ʤ����</returns>
bool is_player_win(const TicTacToeBoard *const board, char player_char) {
	// ѭ���������� 8 �������
	for (int case_id = 0; case_id < 8; case_id++) {
		// ѭ������ָʾ��Ԫ���ǲ������и��Ӷ���ͬһ�����ţ������� player_char��
		bool is_all_marks_equal_to_player_char = true;
		for (int i = 0; i < 3; i++) {
			int position = win_conditions[case_id][i];
			if (board->board[position] != player_char) {
				is_all_marks_equal_to_player_char = false;
				break;
			}
		}

		// ����ǣ��ͷ��� true ��ʾ��� player_char ��һ��ʤ����
		if (is_all_marks_equal_to_player_char) {
			return true;
		}
	}

	// ����Ͳ�һ��ʤ�������ü�������
	return false;
}

/// <summary>
/// ��ʾ��ǰ����״̬�Ƿ�ƽ�֡�
/// </summary>
/// <param name="board">���档</param>
/// <returns>�Ƿ�ƽ�֡�</returns>
bool is_player_tie(const TicTacToeBoard *const board) {
	for (int i = 0; i < 9; i++) {
		if (board->board[i] == PLACEHOLDER_CELL) {
			return false;
		}
	}
	return true;
}
