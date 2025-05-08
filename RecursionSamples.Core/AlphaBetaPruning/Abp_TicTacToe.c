#include "../DataStructures/TicTaeToeBoard.h"
#include "../DataStructures/Utils.h"
#include <float.h>

// ������д˷��ţ��� AI ѡ���ӻ�������ѡȡ���ĵ�Ԫ����Ϊ��ʼ���裬��Ϊ�������߼��Ͻ��ɱ�֤��ʧ�ܻ�ʤ����
// ����һ���ھ���� minimax �㷨����˵��û�����ֵġ�
// ����Ҫע�⣬�������ֻ������ AI ���µ��������Ϊ�������Ӷ��ھ���� minimax �㷨��˵û��ɶ���壩��
#define CENTER_CELL_HAS_PRIORITY

/// <summary>
/// ����������㼫С�������㷨 minimax �����
/// </summary>
/// <param name="board">���档</param>
/// <param name="alpha">alpha ֵ��</param>
/// <param name="beta">beta ֵ��</param>
/// <param name="is_maximizing">�Ƿ�ǰ������������󻯲�����</param>
/// <returns>���ֵ��</returns>
double minimax(TicTacToeBoard *const board, double alpha, double beta, bool is_maximizing) {
#pragma region minimax �㷨����
	// ���������ȷ�������ҵ���ǰ����˫����Ŭ������ʱ�����Ų��ԣ����Ⲣ�����������������š�
	// 
	// �ڱ�׼�� minimax �㷨�У����˫������ȡ���Ų��ԣ�������ĳ�ʼ״̬������λ�õ�����ȷʵ������ 0��ƽ�֣���
	// ��Ϊ�����޷�������ʤ������������������������Ҳ����ֱ�ӷֳ�ʤ�����Ͼ�������ģ�������˵ݹ�����ʱ���������
	// ��ʱ��AI ����ݱ���˳��ѡ��һ�����õ�λ�ã�����������ѡ���м�ĸ��ӣ����� 4������Ϊ���� 0 �ǵ�һ������ 0 �ֵ�λ�ã�
	// ������ 4 Ҳ�� 0 �֣����������һ�� 0 �ֺ󣬺��涼�� 0 �֣�������ͬ�򲻻��滻��һ���������λ�á�
	// ���� minimax �ġ�������ȷ�ԡ��͡�ʵ�ʲ��ԡ�֮��Ĳ��졣
	// 
	// Minimax �ĺ���Ŀ����ȷ�����䣨����ƽ�֣�������׷������ֱ���ϵ�����·������
	// �ھ������У����۵�һ�������ֻҪ˫���������·����������ƽ�֡���ˣ������㷨��������Ż���
	// ����ʵ����Ϸ�У������ǵ�Ҫ�ṩ�Ż����ԣ���ô����Ҫ��������ʽ���򣬵���ȷʵ���������ǽ��ܵݹ��߼��ķ��룬��������Ͳ����Ż��ˣ�
	// ����������ʽ����ȷʵ������������ AI �ġ����˻������ԡ�
#pragma endregion

	// �ݹ���ֹ���������ʤ����ƽ�֡�
	if (is_player_win(board, AI_CELL)) {
		return 1; // AI Ӯȡʤ����
	}
	if (is_player_win(board, HUMAN_CELL)) {
		return -1; // ���Ӯȡʤ����
	}
	if (is_player_tie(board)) {
		return 0; // ƽ�֡�
	}

	if (is_maximizing) {
		// AI��Max �㣩��Ѱ�����ֵ��

		double max_eval = -DBL_MAX;
		int available_moves[9]; // ��ʾȫ�����ò��衣
		int available_moves_count; // ��ʾ�ж��ٸ����õĲ��衣
		get_available_moves(board, available_moves, &available_moves_count);
		for (int i = 0; i < available_moves_count; i++) {
			// ���ԡ�
			board->board[available_moves[i]] = AI_CELL;

			// ����������
			double eval = minimax(board, alpha, beta, false);

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
	else {
		// ��ң�Min �㣩��Ѱ����Сֵ��

		double min_eval = DBL_MAX;
		int available_moves[9]; // ��ʾȫ�����ò��衣
		int available_moves_count; // ��ʾ�ж��ٸ����õĲ��衣
		get_available_moves(board, available_moves, &available_moves_count);
		for (int i = 0; i < available_moves_count; i++) {
			// ���ԡ�
			board->board[available_moves[i]] = HUMAN_CELL;

			// ����������
			double eval = minimax(board, alpha, beta, true);

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
	double best_score = -DBL_MAX; // ��ʾ���ʱ��ķ�����
	int result = -1; // �洢�Ľ�������Ϊ�ɿյ�ֵ��NULL ��ʾû�н������
	int available_moves[9]; // ��ʾȫ�����ò��衣
	int available_moves_count; // ��ʾ�ж��ٸ����õĲ��衣
	get_available_moves(board, available_moves, &available_moves_count);
	for (int i = 0; i < available_moves_count; i++) {
#ifdef CENTER_CELL_HAS_PRIORITY
		// ��ʼ��������Ƿ�Ϊ���̡�����ǵĻ��������ĵ�Ԫ����ָܷ��ߡ�
		if (available_moves_count == 9 && available_moves[i] == 4) {
			best_score = 10;
			result = available_moves[i];
			continue;
		}
#endif // CENTER_CELL_HAS_PRIORITY

		// �������ӡ�
		board->board[available_moves[i]] = AI_CELL;

		// ���������
		double score = minimax(board, -DBL_MAX, DBL_MAX, false);

		// ��ԭ��ȥ��
		board->board[available_moves[i]] = PLACEHOLDER_CELL;

		if (score > best_score) {
			best_score = score;
			result = available_moves[i];
		}
	}
	return result;
}