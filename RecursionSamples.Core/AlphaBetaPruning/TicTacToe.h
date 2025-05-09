#pragma once

#include "../DataStructures/TicTaeToeBoard.h"
#include <stdio.h>

double minimax(TicTacToeBoard *const, double, double, bool);
int ai_move(TicTacToeBoard *const);
int get_human_input(const TicTacToeBoard *const);

void entry(void) {
	TicTacToeBoard playground;
	initialize_tic_tac_toe_board(&playground);

	printf("井字棋开始！AI 先手（符号 %c），玩家后手（符号 %c）。\n", AI_CELL, HUMAN_CELL);

	while (true) {
		// AI 回合。
		int ai_choice = ai_move(&playground);
		playground.board[ai_choice] = AI_CELL;
		printf("\nAI 落子后的棋盘：\n");
		print_tic_tac_toe_board(&playground);

		// 检查胜负。
		if (is_player_win(&playground, AI_CELL)) {
			printf("AI 获胜！\n");
			break;
		}
		if (is_player_tie(&playground)) {
			printf("平局。\n");
			break;
		}

		// 玩家回合。
		int human_choice = get_human_input(&playground);
		playground.board[human_choice] = HUMAN_CELL;
		printf("\n玩家落子后的棋盘：\n");
		print_tic_tac_toe_board(&playground);

		// 检查胜负。
		if (is_player_win(&playground, HUMAN_CELL)) {
			printf("玩家获胜！\n");
			break;
		}
		if (is_player_tie(&playground)) {
			printf("平局。\n");
			break;
		}
	}
}

/// <summary>
/// 获取有效的用户输入（单元格索引），以在这个位置落子。如果输入不合法会强制重新输入，直到输入合法为止。
/// </summary>
/// <param name="playground">盘面。</param>
/// <returns>输入的最终的合法位置索引。</returns>
static int get_human_input(const TicTacToeBoard *const playground) {
	int result; // 表示用户选择的格子。
	bool is_input_valid = true; // 临时布尔值存储是否输入正确而且合法。
	printf("请输入落子位置（0 - 8）：\n");
	do
	{
		// 由于第一次变量强制置为 true，所以重新输入的提示肯定第一次是不作提示的。
		// 但是，一旦会回来重新执行 do 循环体，说明变量 is_input_valid 一定是 false（不然就跳出循环了）。
		if (!is_input_valid) {
			printf("请重新输入落子位置（0 - 8）：\n");
		}

		// 验证基础输入是否有效（必须是 0 - 8 之间的数）。
		// 注意等号运算符（赋值运算符）优先级最低，所以这里右边这一坨表达式先全部都得执行完了才会赋值。
		if (is_input_valid = scanf("%d", &result) == 1 && result >= 0 && result < 9) {
			// 基础输入检查通过，但还需要验证是否下在了有棋子的位置上。
			int available_positions[9];
			int available_positions_count;
			get_available_moves(playground, available_positions, &available_positions_count);
			for (int i = 0; i < available_positions_count; i++) {
				if (result == available_positions[i]) {
					// 这个格子没用过（在可用列表里）。
					goto Verify;
				}
			}

			// 但是，如果走到这里来没有跳出 break，就说明所有可用位置均检查过了，但仍然不行。
			// 强制修改变量 is_input_valid 为 false 以进行下一轮 do 循环体。
			is_input_valid = false;
		}

	Verify:;
	} while (!is_input_valid);
	return result;
}
