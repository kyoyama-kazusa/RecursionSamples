#include "TicTaeToeBoard.h"
#include <stdbool.h>
#include <stdio.h>

/// <summary>
/// 表示所有可以胜利的情况（用单元格索引表示）。
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
/// 初始化一个盘面。
/// </summary>
/// <param name="board">盘面。</param>
void initialize_tic_tac_toe_board(TicTacToeBoard *const board) {
	for (int i = 0; i < 9; i++) {
		board->board[i] = PLACEHOLDER_CELL;
	}
}

/// <summary>
/// 打印一个棋盘。
/// </summary>
/// <param name="board">棋盘。</param>
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
/// 根据指定的棋盘获取可落子的位置，然后用一个缓冲区数组表示结果序列，并返回一个数字表示数组可用长度。
/// </summary>
/// <param name="board">盘面数据。</param>
/// <param name="positions_buffer">
/// <para>缓冲区，存储结果（保证最少可以放入 9 个元素）。</para>
/// <para>如果是非 Visual Studio 环境可以用 C99 的“int positions_buffer[static 9]”语法表示传入数组且元素最少得 9 个。</para>
/// </param>
/// <param name="available_positions_count">表示参数 positions_buffer 可用的元素个数（前几个元素可用）。</param>
void get_available_moves(const TicTacToeBoard *const board, int *const positions_buffer, int *available_positions_count) {
	// 初始化参数。
	*available_positions_count = 0;

	// 循环 9 个位置看看是不是空格。如果是，就选取它作为可用位置。
	for (int i = 0; i < 9; i++) {
		if (board->board[i] == PLACEHOLDER_CELL) {
			positions_buffer[(*available_positions_count)++] = i;
		}
	}
}

/// <summary>
/// 检查指定玩家（参数 player_char 传入对应玩家使用的符号）是否胜利。
/// </summary>
/// <param name="board">盘面数据。</param>
/// <param name="player_char">玩家的代用符号。</param>
/// <returns>是否胜利。</returns>
bool is_player_win(const TicTacToeBoard *const board, char player_char) {
	// 循环遍历所有 8 个情况。
	for (int case_id = 0; case_id < 8; case_id++) {
		// 循环三个指示单元格，是不是所有格子都是同一个符号，都等于 player_char。
		bool is_all_marks_equal_to_player_char = true;
		for (int i = 0; i < 3; i++) {
			int position = win_conditions[case_id][i];
			if (board->board[position] != player_char) {
				is_all_marks_equal_to_player_char = false;
				break;
			}
		}

		// 如果是，就返回 true 表示玩家 player_char 这一方胜利。
		if (is_all_marks_equal_to_player_char) {
			return true;
		}
	}

	// 否则就不一定胜利（还得继续）。
	return false;
}

/// <summary>
/// 表示当前盘面状态是否平局。
/// </summary>
/// <param name="board">盘面。</param>
/// <returns>是否平局。</returns>
bool is_player_tie(const TicTacToeBoard *const board) {
	for (int i = 0; i < 9; i++) {
		if (board->board[i] == PLACEHOLDER_CELL) {
			return false;
		}
	}
	return true;
}
