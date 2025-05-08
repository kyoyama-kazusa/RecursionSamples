#include "../DataStructures/TicTaeToeBoard.h"
#include "../DataStructures/Utils.h"
#include <float.h>

// 如果带有此符号，则 AI 选格子会优先先选取中心单元格作为起始步骤，因为它人脑逻辑上讲可保证不失败或胜利，
// 而这一点在经典的 minimax 算法上来说是没有体现的。
// 但是要注意，这个符号只能用于 AI 先下的情况（因为后下棋子对于经典的 minimax 算法来说没有啥意义）。
#define CENTER_CELL_HAS_PRIORITY

/// <summary>
/// 根据盘面计算极小化极大算法 minimax 结果。
/// </summary>
/// <param name="board">盘面。</param>
/// <param name="alpha">alpha 值。</param>
/// <param name="beta">beta 值。</param>
/// <param name="is_maximizing">是否当前层搜索的是最大化操作。</param>
/// <returns>结果值。</returns>
double minimax(TicTacToeBoard *const board, double alpha, double beta, bool is_maximizing) {
#pragma region minimax 算法介绍
	// 这个函数能确保搜索找到当前局面双方均努力下棋时的最优策略，但这并不代表是真正的最优。
	// 
	// 在标准的 minimax 算法中，如果双方都采取最优策略，井字棋的初始状态下所有位置的评分确实都会是 0（平局），
	// 因为先手无法做到必胜（深度优先搜索就算下满棋局也不能直接分出胜负，毕竟这是在模拟两个人递归下棋时的情况）。
	// 此时，AI 会根据遍历顺序选择一个可用的位置，而不会优先选择中间的格子（索引 4），因为索引 0 是第一次遇到 0 分的位置；
	// 而索引 4 也是 0 分，因此遇到第一次 0 分后，后面都是 0 分，分数相同则不会替换下一步的下棋的位置。
	// 这是 minimax 的“理论正确性”和“实际策略”之间的差异。
	// 
	// Minimax 的核心目标是确保不输（至少平局），而非追求“人类直觉上的最优路径”。
	// 在井字棋中，无论第一步下哪里，只要双方都最优下法，结果都是平局。因此，理论算法无需额外优化。
	// 但在实际游戏中，如果你非得要提供优化策略，那么你需要增加启发式规则，但这确实超出了我们介绍递归逻辑的范畴，所以这里就不作优化了；
	// 不过，启发式规则确实是能显著提升 AI 的“拟人化”策略。
#pragma endregion

	// 递归终止条件：检查胜负或平局。
	if (is_player_win(board, AI_CELL)) {
		return 1; // AI 赢取胜利。
	}
	if (is_player_win(board, HUMAN_CELL)) {
		return -1; // 玩家赢取胜利。
	}
	if (is_player_tie(board)) {
		return 0; // 平局。
	}

	if (is_maximizing) {
		// AI（Max 层）：寻找最大值。

		double max_eval = -DBL_MAX;
		int available_moves[9]; // 表示全部可用步骤。
		int available_moves_count; // 表示有多少个可用的步骤。
		get_available_moves(board, available_moves, &available_moves_count);
		for (int i = 0; i < available_moves_count; i++) {
			// 尝试。
			board->board[available_moves[i]] = AI_CELL;

			// 评估分数。
			double eval = minimax(board, alpha, beta, false);

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
	else {
		// 玩家（Min 层）：寻找最小值。

		double min_eval = DBL_MAX;
		int available_moves[9]; // 表示全部可用步骤。
		int available_moves_count; // 表示有多少个可用的步骤。
		get_available_moves(board, available_moves, &available_moves_count);
		for (int i = 0; i < available_moves_count; i++) {
			// 尝试。
			board->board[available_moves[i]] = HUMAN_CELL;

			// 评估分数。
			double eval = minimax(board, alpha, beta, true);

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
	double best_score = -DBL_MAX; // 表示最好时候的分数。
	int result = -1; // 存储的结果。结果为可空的值（NULL 表示没有结果）。
	int available_moves[9]; // 表示全部可用步骤。
	int available_moves_count; // 表示有多少个可用的步骤。
	get_available_moves(board, available_moves, &available_moves_count);
	for (int i = 0; i < available_moves_count; i++) {
#ifdef CENTER_CELL_HAS_PRIORITY
		// 初始检查盘面是否为空盘。如果是的话，下中心单元格可能分更高。
		if (available_moves_count == 9 && available_moves[i] == 4) {
			best_score = 10;
			result = available_moves[i];
			continue;
		}
#endif // CENTER_CELL_HAS_PRIORITY

		// 尝试落子。
		board->board[available_moves[i]] = AI_CELL;

		// 计算分数。
		double score = minimax(board, -DBL_MAX, DBL_MAX, false);

		// 还原回去。
		board->board[available_moves[i]] = PLACEHOLDER_CELL;

		if (score > best_score) {
			best_score = score;
			result = available_moves[i];
		}
	}
	return result;
}