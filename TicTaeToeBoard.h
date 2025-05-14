#pragma once

#include <stdbool.h>

/// <summary>
/// 表示 AI 棋子字符。
/// </summary>
#define AI_CELL 'x'

/// <summary>
/// 表示玩家棋子字符。
/// </summary>
#define HUMAN_CELL 'o'

/// <summary>
/// 表示空格。
/// </summary>
#define PLACEHOLDER_CELL ' '


/// <summary>
/// 定义一个井字棋盘面。
/// </summary>
typedef struct TicTacToeBoard {
	/// <summary>
	/// 表示棋子。
	/// </summary>
	char board[9];
} TicTacToeBoard;

void initialize_tic_tac_toe_board(TicTacToeBoard *const);
void print_tic_tac_toe_board(const TicTacToeBoard *const);
void get_available_moves(const TicTacToeBoard *const, int *const, int *);
int get_last_empty_spaces_count(const TicTacToeBoard *const);
bool is_player_win(const TicTacToeBoard *const, char);
bool is_player_tie(const TicTacToeBoard *const);
