#include "TicTaeToeBoard.h"
#include "Utils.h"
#include <limits.h>

/// <summary>
/// 根据盘面计算极小化极大算法 minimax 结果。
/// </summary>
/// <param name="board">盘面。</param>
/// <param name="alpha">alpha 值。</param>
/// <param name="beta">beta 值。</param>
/// <param name="is_maximizing">是否当前层搜索的是最大化操作。</param>
/// <returns>结果值。</returns>
int minimax(TicTacToeBoard *const board, int alpha, int beta, bool is_maximizing) {
	// 递归终止条件：检查胜负或平局。
	if (is_player_win(board, AI_CELL)) {
		return 10 - (9 - get_last_empty_spaces_count(board)); // AI 赢取胜利。
	}
	if (is_player_win(board, HUMAN_CELL)) {
		return -(10 - (9 - get_last_empty_spaces_count(board))); // 玩家赢取胜利。
	}
	if (is_player_tie(board)) {
		return 0; // 平局。
	}

	// AI（Max 层）：寻找最大值。
	if (is_maximizing) {
		int max_eval = INT_MIN;
		int available_moves[9]; // 表示全部可用步骤。
		int available_moves_count; // 表示有多少个可用的步骤。
		get_available_moves(board, available_moves, &available_moves_count);
		for (int i = 0; i < available_moves_count; i++) {
			// 尝试。
			board->board[available_moves[i]] = AI_CELL;

			// 评估分数。
			int eval = minimax(board, alpha, beta, false);

			// 还原回去。
			board->board[available_moves[i]] = PLACEHOLDER_CELL;

			max_eval = MAX(max_eval, eval);
			alpha = MAX(alpha, eval);
			if (beta <= alpha) {
				// 触发剪枝。
				break;
			}
		}
		return max_eval;
	}

	// 玩家（Min 层）：寻找最小值。
	else {
		int min_eval = INT_MAX;
		int available_moves[9]; // 表示全部可用步骤。
		int available_moves_count; // 表示有多少个可用的步骤。
		get_available_moves(board, available_moves, &available_moves_count);
		for (int i = 0; i < available_moves_count; i++) {
			// 尝试。
			board->board[available_moves[i]] = HUMAN_CELL;

			// 评估分数。
			int eval = minimax(board, alpha, beta, true);

			// 还原回去。
			board->board[available_moves[i]] = PLACEHOLDER_CELL;

			min_eval = MIN(min_eval, eval);
			beta = MIN(beta, eval);
			if (beta <= alpha) {
				// 触发剪枝。
				break;
			}
		}
		return min_eval;
	}
}

/// <summary>
/// 让 AI 选择到最好的落子位置。
/// </summary>
/// <param name="board">盘面。</param>
/// <returns>返回一个结果，表示落子位置。</returns>
int ai_move(TicTacToeBoard *const board) {
	int best_score = INT_MIN; // 表示最好时候的分数。
	int result = -1; // 存储的结果。
	int available_moves[9]; // 表示全部可用步骤。
	int available_moves_count; // 表示有多少个可用的步骤。
	get_available_moves(board, available_moves, &available_moves_count);
	for (int i = 0; i < available_moves_count; i++) {
		// 尝试落子。
		board->board[available_moves[i]] = AI_CELL;

		// 计算分数。
		int score = minimax(board, INT_MIN, INT_MAX, false);

		// 还原回去。
		board->board[available_moves[i]] = PLACEHOLDER_CELL;

		if (score > best_score) {
			best_score = score;
			result = available_moves[i];
		}
	}
	return result;
}