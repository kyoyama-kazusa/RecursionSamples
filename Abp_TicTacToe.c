#include "TicTaeToeBoard.h"
#include "Utils.h"
#include <limits.h>

/// <summary>
/// ����������㼫С�������㷨 minimax �����
/// </summary>
/// <param name="board">���档</param>
/// <param name="alpha">alpha ֵ��</param>
/// <param name="beta">beta ֵ��</param>
/// <param name="is_maximizing">�Ƿ�ǰ������������󻯲�����</param>
/// <returns>���ֵ��</returns>
int minimax(TicTacToeBoard *const board, int alpha, int beta, bool is_maximizing) {
	// �ݹ���ֹ���������ʤ����ƽ�֡�
	if (is_player_win(board, AI_CELL)) {
		return 10 - (9 - get_last_empty_spaces_count(board)); // AI Ӯȡʤ����
	}
	if (is_player_win(board, HUMAN_CELL)) {
		return -(10 - (9 - get_last_empty_spaces_count(board))); // ���Ӯȡʤ����
	}
	if (is_player_tie(board)) {
		return 0; // ƽ�֡�
	}

	// AI��Max �㣩��Ѱ�����ֵ��
	if (is_maximizing) {
		int max_eval = INT_MIN;
		int available_moves[9]; // ��ʾȫ�����ò��衣
		int available_moves_count; // ��ʾ�ж��ٸ����õĲ��衣
		get_available_moves(board, available_moves, &available_moves_count);
		for (int i = 0; i < available_moves_count; i++) {
			// ���ԡ�
			board->board[available_moves[i]] = AI_CELL;

			// ����������
			int eval = minimax(board, alpha, beta, false);

			// ��ԭ��ȥ��
			board->board[available_moves[i]] = PLACEHOLDER_CELL;

			max_eval = MAX(max_eval, eval);
			alpha = MAX(alpha, eval);
			if (beta <= alpha) {
				// ������֦��
				break;
			}
		}
		return max_eval;
	}

	// ��ң�Min �㣩��Ѱ����Сֵ��
	else {
		int min_eval = INT_MAX;
		int available_moves[9]; // ��ʾȫ�����ò��衣
		int available_moves_count; // ��ʾ�ж��ٸ����õĲ��衣
		get_available_moves(board, available_moves, &available_moves_count);
		for (int i = 0; i < available_moves_count; i++) {
			// ���ԡ�
			board->board[available_moves[i]] = HUMAN_CELL;

			// ����������
			int eval = minimax(board, alpha, beta, true);

			// ��ԭ��ȥ��
			board->board[available_moves[i]] = PLACEHOLDER_CELL;

			min_eval = MIN(min_eval, eval);
			beta = MIN(beta, eval);
			if (beta <= alpha) {
				// ������֦��
				break;
			}
		}
		return min_eval;
	}
}

/// <summary>
/// �� AI ѡ����õ�����λ�á�
/// </summary>
/// <param name="board">���档</param>
/// <returns>����һ���������ʾ����λ�á�</returns>
int ai_move(TicTacToeBoard *const board) {
	int best_score = INT_MIN; // ��ʾ���ʱ��ķ�����
	int result = -1; // �洢�Ľ����
	int available_moves[9]; // ��ʾȫ�����ò��衣
	int available_moves_count; // ��ʾ�ж��ٸ����õĲ��衣
	get_available_moves(board, available_moves, &available_moves_count);
	for (int i = 0; i < available_moves_count; i++) {
		// �������ӡ�
		board->board[available_moves[i]] = AI_CELL;

		// ���������
		int score = minimax(board, INT_MIN, INT_MAX, false);

		// ��ԭ��ȥ��
		board->board[available_moves[i]] = PLACEHOLDER_CELL;

		if (score > best_score) {
			best_score = score;
			result = available_moves[i];
		}
	}
	return result;
}