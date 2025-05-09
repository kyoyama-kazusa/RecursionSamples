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
/// ��ʾ�ĸ���������ѭ����
/// </summary>
static const Direction all_directions[4] = { Up, Down, Left, Right };

void entry(void) {
	// ��Ŀ��S - ��㣬S - �յ㣩��
	// ### E#
	// #### #
	// ######
	// # S##
	// ######
	// ######
	// 
	// ��⣺
	// ��������������������������������������������������������������

	// ��Ŀ��
	Cell puzzle[N][N] = {
		{ 1, 1, 1, 0, 1, 1 },
		{ 1, 1, 1, 1, 0, 1 },
		{ 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 1, 0 },
		{ 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1 }
	};
	print_puzzle(puzzle);
	printf("��⣺\n");

	// �𰸡�
	Direction solution[PUZZLE_CELLS_COUNT] = { 0 };

	// ״̬��
	Cell status_map[N][N] = { { 0 } };

	// ���յ����꣨�յ����겻��Ҫ�������ڵ��ԣ���
	Coordinate start = { .x = 3, .y = 2 };
	Coordinate end = { .x = 0, .y = 4 };
	dfs(puzzle, status_map, start, solution, 0);
}

/// <summary>
/// ��ӡ���档
/// </summary>
/// <param name="puzzle">���档�ù��ĸ����þ���ռλ������ո�ռλ��</param>
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
/// ������ȵݹ��ҹ��ܶ�·����
/// </summary>
/// <param name="puzzle">��Ŀ��</param>
/// <param name="status_map">״̬����¼������Ŀ���ӵ�ʹ��״̬��</param>
/// <param name="start">������ꡣ</param>
/// <param name="current">��ǰ�����������ꡣ</param>
/// <param name="solution">��⡣</param>
/// <param name="index">��ǰ�ߵ��˵ڼ�����Ԫ��</param>
/// <returns>�Ƿ��ҵ�����Ŀ�Ľ⡣�����жϺ͵ݹ鷵�ء�</returns>
static bool dfs(
	const Cell(*const puzzle)[N],
	Cell(*status_map)[N],
	Coordinate current,
	Direction *solution,
	int index
) {
	// �����ȱ�ǵ�Ԫ���ù���
	status_map[current.x][current.y] = 1;

	// Ȼ������֮�󣬼�����Ƿ��Ѿ������һ���� is_solved(puzzle, status_map) ���ж��Ƿ���Ӷ����ˡ�
	// �����������ֱ���ж� index �ǲ��ǵ��� PUZZLE_CELLS_COUNT����Ϊ����¼�������˶��ٸ��Ϸ���Ԫ�񣨵ݹ�Ĳ�������
	// �������е�Ԫ���˵���������ˣ��Ͼ��ݹ��߼���У�鲿���Ǳ�֤���ߵĸ���һ���ǺϷ��ģ���������Ͳ��ÿ�����Щ�����ˡ�
	if (is_solved(puzzle, status_map)) {
		// ����ˡ���ӡ�����˳���ǰ��ĵݹ顣
		// �����Ԫ��״̬�ɹ������Ҳ��ü����������ĸ������ˣ��Ͼ���Ԫ�������ˣ������ټ�����һ��ݹ��ˡ�
		for (int i = 0; i < PUZZLE_CELLS_COUNT; i++) {
			printf("%s", get_direction_string(solution[i]));
		}
		printf("\n");

		// ���� true�������ĸ����򶼲����ˡ�
		return true;
	}

	// ����⻹û�������˵���п�λ��û�á����濪ʼ�ݹ��ĸ�����
	for (int i = 0; i < 4; i++) {
		// ��ȡ�·����߹�ȥ�����꣬Ȼ������������Ƿ������ô�ߣ�Խ�硢�Ϸ����Ƿ��ù��ȣ���
		Coordinate new_coordinate = get_coordinate(current, all_directions[i]);
		if (is_valid_coordinate(new_coordinate, puzzle, status_map)) {
			// ����Ϸ��͵ݹ���һ����Ԫ��
			solution[index] = all_directions[i];
			if (dfs(puzzle, status_map, new_coordinate, solution, index + 1)) {
				// ��һ�㷵�� true �ˣ�˵���ҳ��˽⣬��������Ҳ�˳���һ�㣬�������ɶ�Ķ������ˡ�
				return true;
			}
		}
	}

	// ���� - ����������Ԫ��
	// ��ǰ��Ĵ������ߵ����˵������ĸ������Ѿ����Թ����������Ƿ�ɹ����ɹ���ʧ�ܣ��������ߵ����
	// ���������Ϸ���ԣ����ߵ������˵��ǰ���״̬��������ˣ���ʱ����Ҫ��ԭ�����Ԫ���ʹ��״̬���ӡ�ʹ�ù����Ļء�ûʹ�á�����
	status_map[current.x][current.y] = 0;
	solution[index] = 0;
	return false;
}

/// <summary>
/// �����������Ƿ�ȫ����Ԫ��ʹ�ù��ˡ�
/// </summary>
/// <param name="puzzle">��Ŀ�����ڱȶԸ����Ƿ���Ҫ����У�顣</param>
/// <param name="status_map">״̬��</param>
/// <returns>����ֵ����ʾ�Ƿ����е�Ԫ���ù�������ˣ���</returns>
static bool is_solved(const Cell(*const puzzle)[N], const Cell(*const status_map)[N]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (puzzle[i][j] && !status_map[i][j]) {
				// ��Ŀʹ����������ӣ����������Ԫ���� 0 ��״̬��û�ù�����
				return false;
			}
		}
	}

	// ���е�Ԫ�����ˡ�
	return true;
}

/// <summary>
/// ��鵱ǰ�����Ƿ��������ϺϷ�����Խ�磬Ҳ����������ʹ�õ�Ԫ��Ҳû����·��ʹ�ù�����
/// </summary>
/// <param name="coordinate">���ꡣ</param>
/// <param name="puzzle">���档</param>
/// <param name="status_map">״̬��</param>
/// <returns>����ֵ��ʾ�Ƿ�Ϸ���</returns>
static inline bool is_valid_coordinate(Coordinate coordinate, const Cell(*const puzzle)[N], const Cell(*const status_map)[N]) {
	// ��������Ƿ�Խ�硣
	if (coordinate.x < 0 || coordinate.x >= N || coordinate.y < 0 || coordinate.y >= N) {
		return false;
	}

	// ûԽ�磬��������Ƿ�����Ŀ��ʹ�á�
	if (!puzzle[coordinate.x][coordinate.y]) {
		return false;
	}

	// ���������Ŀ��ʹ�ã���������Ƿ��Ѿ���������ȹ���ʹ�ù���
	if (status_map[coordinate.x][coordinate.y]) {
		return false;
	}

	// ״̬��Ҳû��ʹ�ù�����˵���������á�
	return true;
}

/// <summary>
/// ��ȡ��ָ������ǰ��һ���ĵ�Ԫ��
/// </summary>
/// <param name="original">��ǰ��Ԫ��</param>
/// <param name="direction">ǰ������</param>
/// <returns>�µ�Ԫ��</returns>
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
