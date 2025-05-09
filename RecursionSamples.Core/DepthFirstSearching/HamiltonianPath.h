#pragma once

#include "../DataStructures/Coordinate.h"
#include "../DataStructures/Direction.h"
#include <stdbool.h>
#include <stdio.h>

#define N 6
#define PUZZLE_CELLS_COUNT ((N) * (N) - 5)

typedef signed char Cell;

void print_puzzle(const Cell(*const)[N]);
bool dfs(const Cell(*const)[N], Cell(*)[N], Coordinate, Direction *, int);
bool is_solved(const Cell(*const)[N], const Cell(*const)[N]);
bool is_valid_coordinate(Coordinate, const Cell(*const)[N], const Cell(*const)[N]);
Coordinate get_coordinate(Coordinate, Direction);

/// <summary>
/// 表示四个方向，用于循环。
/// </summary>
static const Direction all_directions[4] = { Up, Down, Left, Right };

void entry(void) {
	// 题目（S - 起点，S - 终点）。
	// ### E#
	// #### #
	// ######
	// # S##
	// ######
	// ######
	// 
	// 题解：
	// ↑→↑←↑←←↓→↓←↓↓↓→↑→↓→→→↑←←↑→↑→↑↑←

	// 题目。
	Cell puzzle[N][N] = {
		{ 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 1, 0 },
		{ 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1 }
	};
	print_puzzle(puzzle);
	printf("题解：\n");

	// 答案。
	Direction solution[PUZZLE_CELLS_COUNT] = { 0 };

	// 状态表。
	Cell status_map[N][N] = { { 0 } };

	// 起终点坐标（终点坐标不需要，仅用于调试）。
	Coordinate start = { .x = 3, .y = 2 };
	Coordinate end = { .x = 0, .y = 4 };
	dfs(puzzle, status_map, start, solution, 0);
}

/// <summary>
/// 打印盘面。
/// </summary>
/// <param name="puzzle">盘面。用过的格子用井号占位；否则空格占位。</param>
static void print_puzzle(const Cell(*const puzzle)[N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			printf("%c", puzzle[i][j] ? '#' : ' ');
		}
		printf("\n");
	}
	printf("\n");
}

/// <summary>
/// 深度优先递归找哈密顿路径。
/// </summary>
/// <param name="puzzle">题目。</param>
/// <param name="status_map">状态表，记录的是题目格子的使用状态。</param>
/// <param name="start">起点坐标。</param>
/// <param name="current">当前遍历到的坐标。</param>
/// <param name="solution">题解。</param>
/// <param name="index">当前走到了第几个单元格。</param>
/// <returns>是否找到了题目的解。用于判断和递归返回。</returns>
static bool dfs(
	const Cell(*const puzzle)[N],
	Cell(*status_map)[N],
	Coordinate current,
	Direction *solution,
	int index
) {
	// 上来先标记单元格用过。
	status_map[current.x][current.y] = 1;

	// 然后标记了之后，检查题是否已经解出。一般用 is_solved(puzzle, status_map) 来判断是否格子都用了。
	// 不过这里可以直接判断 index 是不是等于 PUZZLE_CELLS_COUNT，因为它记录的是走了多少个合法单元格（递归的层数），
	// 走满所有单元格就说明题解出来了，毕竟递归逻辑的校验部分是保证了走的格子一定是合法的，所以这里就不用考虑那些东西了。
	if (is_solved(puzzle, status_map)) {
		// 解出了。打印它并退出当前层的递归。
		// 这个单元格状态成功，而且不用继续算后面的四个方向了，毕竟单元格都用完了，不用再继续下一层递归了。
		for (int i = 0; i < PUZZLE_CELLS_COUNT; i++) {
			printf("%s", get_direction_string(solution[i]));
		}
		printf("\n");

		// 返回 true，后面四个方向都不走了。
		return true;
	}

	// 如果题还没解出来，说明有空位还没用。下面开始递归四个方向。
	for (int i = 0; i < 4; i++) {
		// 获取新方向走过去的坐标，然后检查这个坐标是否可以这么走（越界、合法、是否被用过等）。
		Coordinate new_coordinate = get_coordinate(current, all_directions[i]);
		if (is_valid_coordinate(new_coordinate, puzzle, status_map)) {
			// 方向合法就递归下一个单元格。
			solution[index] = all_directions[i];
			if (dfs(puzzle, status_map, new_coordinate, solution, index + 1)) {
				// 上一层返回 true 了，说明找出了解，这里我们也退出这一层，后面回溯啥的都不走了。
				return true;
			}
		}
	}

	// 回溯 - 不标记这个单元格。
	// 当前层的代码能走到这里，说明玩家四个方向都已经尝试过。不论它是否成功（成功或失败），都将走到这里。
	// 对于这个游戏而言，能走到这里就说明前面的状态都处理过了，此时就需要还原这个单元格的使用状态（从“使用过”改回“没使用”）。
	status_map[current.x][current.y] = 0;
	solution[index] = 0;
	return false;
}

/// <summary>
/// 检查这个盘面是否全部单元格都使用过了。
/// </summary>
/// <param name="puzzle">题目，用于比对格子是否需要参与校验。</param>
/// <param name="status_map">状态表。</param>
/// <returns>布尔值，表示是否所有单元格都用过（解决了）。</returns>
static bool is_solved(const Cell(*const puzzle)[N], const Cell(*const status_map)[N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (puzzle[i][j] && !status_map[i][j]) {
				// 题目使用了这个格子，但是这个单元格还是 0 的状态（没用过）。
				return false;
			}
		}
	}

	// 所有单元格都用了。
	return true;
}

/// <summary>
/// 检查当前坐标是否在盘面上合法（不越界，也在盘面里是使用单元格，也没有在路径使用过）。
/// </summary>
/// <param name="coordinate">坐标。</param>
/// <param name="puzzle">盘面。</param>
/// <param name="status_map">状态表。</param>
/// <returns>布尔值表示是否合法。</returns>
static inline bool is_valid_coordinate(Coordinate coordinate, const Cell(*const puzzle)[N], const Cell(*const status_map)[N]) {
	// 检查坐标是否越界。
	if (coordinate.x < 0 || coordinate.x >= N || coordinate.y < 0 || coordinate.y >= N) {
		return false;
	}

	// 没越界，检查坐标是否在题目里使用。
	if (!puzzle[coordinate.x][coordinate.y]) {
		return false;
	}

	// 坐标会在题目里使用，检查坐标是否已经被深度优先过程使用过。
	if (status_map[coordinate.x][coordinate.y]) {
		return false;
	}

	// 状态表也没有使用过它，说明它可以用。
	return true;
}

/// <summary>
/// 获取按指定方向前进一步的单元格。
/// </summary>
/// <param name="original">当前单元格。</param>
/// <param name="direction">前进方向。</param>
/// <returns>新单元格。</returns>
static inline Coordinate get_coordinate(Coordinate original, Direction direction) {
	switch (direction) {
	case Up:
		return (Coordinate) { .x = original.x - 1, .y = original.y };
	case Down:
		return (Coordinate) { .x = original.x + 1, .y = original.y };
	case Left:
		return (Coordinate) { .x = original.x, .y = original.y - 1 };
	case Right:
		return (Coordinate) { .x = original.x, .y = original.y + 1 };
	default:
		return (Coordinate) { .x = 0, .y = 0 };
	}
}
