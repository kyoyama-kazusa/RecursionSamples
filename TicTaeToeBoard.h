#pragma once

#include <stdbool.h>

/// <summary>
/// ��ʾ AI �����ַ���
/// </summary>
#define AI_CELL 'x'

/// <summary>
/// ��ʾ��������ַ���
/// </summary>
#define HUMAN_CELL 'o'

/// <summary>
/// ��ʾ�ո�
/// </summary>
#define PLACEHOLDER_CELL ' '


/// <summary>
/// ����һ�����������档
/// </summary>
typedef struct TicTacToeBoard {
	/// <summary>
	/// ��ʾ���ӡ�
	/// </summary>
	char board[9];
} TicTacToeBoard;

void initialize_tic_tac_toe_board(TicTacToeBoard *const);
void print_tic_tac_toe_board(const TicTacToeBoard *const);
void get_available_moves(const TicTacToeBoard *const, int *const, int *);
int get_last_empty_spaces_count(const TicTacToeBoard *const);
bool is_player_win(const TicTacToeBoard *const, char);
bool is_player_tie(const TicTacToeBoard *const);
