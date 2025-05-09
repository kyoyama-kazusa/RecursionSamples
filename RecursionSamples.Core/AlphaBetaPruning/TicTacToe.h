#pragma once

#include "../DataStructures/TicTaeToeBoard.h"
#include <stdio.h>

double minimax(TicTacToeBoard *const, double, double, bool);
int ai_move(TicTacToeBoard *const);
int get_human_input(const TicTacToeBoard *const);

void entry(void) {
	TicTacToeBoard playground;
	initialize_tic_tac_toe_board(&playground);

	printf("�����忪ʼ��AI ���֣����� %c������Һ��֣����� %c����\n", AI_CELL, HUMAN_CELL);

	while (true) {
		// AI �غϡ�
		int ai_choice = ai_move(&playground);
		playground.board[ai_choice] = AI_CELL;
		printf("\nAI ���Ӻ�����̣�\n");
		print_tic_tac_toe_board(&playground);

		// ���ʤ����
		if (is_player_win(&playground, AI_CELL)) {
			printf("AI ��ʤ��\n");
			break;
		}
		if (is_player_tie(&playground)) {
			printf("ƽ�֡�\n");
			break;
		}

		// ��һغϡ�
		int human_choice = get_human_input(&playground);
		playground.board[human_choice] = HUMAN_CELL;
		printf("\n������Ӻ�����̣�\n");
		print_tic_tac_toe_board(&playground);

		// ���ʤ����
		if (is_player_win(&playground, HUMAN_CELL)) {
			printf("��һ�ʤ��\n");
			break;
		}
		if (is_player_tie(&playground)) {
			printf("ƽ�֡�\n");
			break;
		}
	}
}

/// <summary>
/// ��ȡ��Ч���û����루��Ԫ�����������������λ�����ӡ�������벻�Ϸ���ǿ���������룬ֱ������Ϸ�Ϊֹ��
/// </summary>
/// <param name="playground">���档</param>
/// <returns>��������յĺϷ�λ��������</returns>
static int get_human_input(const TicTacToeBoard *const playground) {
	int result; // ��ʾ�û�ѡ��ĸ��ӡ�
	bool is_input_valid = true; // ��ʱ����ֵ�洢�Ƿ�������ȷ���ҺϷ���
	printf("����������λ�ã�0 - 8����\n");
	do
	{
		// ���ڵ�һ�α���ǿ����Ϊ true�����������������ʾ�϶���һ���ǲ�����ʾ�ġ�
		// ���ǣ�һ�����������ִ�� do ѭ���壬˵������ is_input_valid һ���� false����Ȼ������ѭ���ˣ���
		if (!is_input_valid) {
			printf("��������������λ�ã�0 - 8����\n");
		}

		// ��֤���������Ƿ���Ч�������� 0 - 8 ֮���������
		// ע��Ⱥ����������ֵ����������ȼ���ͣ����������ұ���һ����ʽ��ȫ������ִ�����˲Żḳֵ��
		if (is_input_valid = scanf("%d", &result) == 1 && result >= 0 && result < 9) {
			// ����������ͨ����������Ҫ��֤�Ƿ������������ӵ�λ���ϡ�
			int available_positions[9];
			int available_positions_count;
			get_available_moves(playground, available_positions, &available_positions_count);
			for (int i = 0; i < available_positions_count; i++) {
				if (result == available_positions[i]) {
					// �������û�ù����ڿ����б����
					goto Verify;
				}
			}

			// ���ǣ�����ߵ�������û������ break����˵�����п���λ�þ������ˣ�����Ȼ���С�
			// ǿ���޸ı��� is_input_valid Ϊ false �Խ�����һ�� do ѭ���塣
			is_input_valid = false;
		}

	Verify:;
	} while (!is_input_valid);
	return result;
}
