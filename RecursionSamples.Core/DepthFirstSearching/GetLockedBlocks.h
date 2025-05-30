/*
* 计算锁定麻将牌
*
* 把压根矩阵当成一个游戏棋盘，然后让麻将一个一个这么堆砌在棋盘上。此时允许麻将叠到上方，这样可以分层。
* 现在游戏强制规定，一张麻将牌占据棋盘的 2 * 2 的四个单元格位置（方便计算），这样也便于后续计算错开摆放的状态。
* 假设我们只允许麻将牌摆放在下一层麻将牌的上方完全重叠，或者重叠一半，或者四分之一（有一半的边角叠起来）这样三种重叠状态。
* 现在游戏规定我拿麻将只能拿上层的，不能拿压着的麻将，哪怕只压了 1/4 或一半也不行。
* 那么现在我指定一个麻将，请找出整个麻将所有下方压着的全部麻将（锁定的麻将），哪些麻将受这张麻将牌的直接或间接制约，
* 即不拿走它，下面这些麻将牌永远都无法被拿走。
*
* 这个算法需要深度优先递归进行，比如我从这个麻将开始往下找。找这个麻将的下方所有 9 个可能作为压着的摆放状态位置，即：
*
*   (1) 左上角；
*   (2) 上方一半错开；
*   (3) 右上角；
*   (4) 左边一半错开；
*   (5) 正下方；
*   (6) 右边一半错开；
*   (7) 左下角；
*   (8) 下方一半错开；
*   (9) 右下角。
*
* 一共有 9 个情况。直接强制穷举这 9 个情况，然后看这 9 个情况在下一层里是否实际真正存在这样的牌。如果有，就说明它被压着了。
* 压着了的牌继续作为这一次的目标牌，然后计算这张牌下面的所有递归压着的牌（直接或间接压着的）。最后把他们全列出来，就是这个题的结果了。
*/

#pragma once

#include "../DataStructures/Coordinate.h"
#include <stdbool.h>
#include <stdio.h>


/// <summary>
/// 表示本问题里的层数。
/// </summary>
#define LAYERS_COUNT 4

/// <summary>
/// 表示本问题里记录结果的缓冲区长度。
/// </summary>
#define BUFFER_LENGTH 20


/// <summary>
/// 表示偏移量。
/// </summary>
static const int offsets[3] = { -1, 0, 1 };

/// <summary>
/// 长度表。
/// </summary>
static const int lengths[4] = { 9, 4, 1, 4 };


void dfs(int, Coordinate, const Coordinate *const *const, Coordinate *const, int *const);
bool block_array_contains(const Coordinate *const, int, Coordinate);
bool block_array_array_contains(const Coordinate *const *const, int, Coordinate);


void entry(void) {
	const Coordinate layer1[9] = {
		{ 0, 0 }, { 0, 2 }, { 0, 4 },
		{ 2, 0 }, { 2, 2 }, { 2, 4 },
		{ 4, 0 }, { 4, 2 }, { 4, 4 }
	};
	const Coordinate layer2[4] = { { 1, 1 }, { 1, 3 }, { 3, 1 }, { 3, 3 } };
	const Coordinate layer3[1] = { { 2, 2 } };
	const Coordinate layer4[4] = { { 1, 1 }, { 1, 3 }, { 3, 1 }, { 3, 3 } };

	// 摆放块的数据。
	// 块是最底层 9 个，然后上一层有 4 个，再上一层有 1 个，再上一侧有 4 个。
	// 也就是说 blocks 变量索引为 0 的是最底层，数字越大越上层。
	const Coordinate *const blocks[LAYERS_COUNT] = { layer1, layer2, layer3, layer4 };

	// 缓存结果。
	Coordinate buffer[BUFFER_LENGTH];
	int length = 0;

	// 递归求得压着的坐标。
	// 样例传入的是第 2 层的唯一的这个坐标，那么它下层的有 9 + 4 一共 13 个位置。
	dfs(2, layer3[0], blocks, buffer, &length);

	// 打印压住的块的坐标。打印结果应该是 13 个。
	for (int i = 0; i < length; i++) {
		printf("(%d, %d)\n", buffer[i].x, buffer[i].y);
	}
}

/// <summary>
/// 进行深度优先，查找它的下层是否有压着，压着哪些。
/// </summary>
/// <param name="layer">当前层。</param>
/// <param name="block">当前块的坐标。</param>
/// <param name="blocks">所有的块。</param>
/// <param name="buffer">存储压着的坐标的块。</param>
/// <param name="length">参数 buffer 的实际存储元素的长度。</param>
static void dfs(int layer, Coordinate block, const Coordinate *const *const blocks, Coordinate *const buffer, int *const length) {
	if (layer <= 0) {
		// 已经到底了，不用继续向下了。
		return;
	}

	for (int i = layer; i < LAYERS_COUNT; i++) {
		for (int x_offset_index = 0; x_offset_index < 3; x_offset_index++) {
			for (int y_offset_index = 0; y_offset_index < 3; y_offset_index++) {
				// 构造出压着的坐标。
				Coordinate new_block = { block.x + offsets[x_offset_index], block.y + offsets[y_offset_index] };

				if (// 判断压着的坐标是否存在于原本给的坐标列表里。
					block_array_array_contains(blocks, layer - 1, new_block)
					// 压着的。判断这个坐标是否已经记录过。如果记录过就跳过。
					&& !block_array_contains(buffer, *length, new_block)) {

					// 加入到总列表里。
					buffer[*length] = new_block;
					(*length)++;

					// 然后递归后面的。
					dfs(layer - 1, new_block, blocks, buffer, length);
				}
			}
		}
	}
}

/// <summary>
/// 计算是否指定层和块的数据已经存在了目标序列里。如果有的话就返回 true。
/// </summary>
/// <param name="blocks">记录了的块。</param>
/// <param name="layer">层。</param>
/// <param name="block">坐标。</param>
/// <returns>一个布尔结果。</returns>
static bool block_array_array_contains(const Coordinate *const *const blocks, int layer, Coordinate block) {
	for (int i = 0; i < LAYERS_COUNT; i++) {
		for (int j = 0; j < lengths[i]; j++) {
			if (block_array_contains(blocks[i], lengths[i], block)) {
				return true;
			}
		}
	}
	return false;
}

/// <summary>
/// 计算是否指定层和块的数据已经存在了目标序列里。如果有的话就返回 true。
/// </summary>
/// <param name="blocks">记录了的块。</param>
/// <param name="length">记录了的块的元素数量。</param>
/// <param name="block">坐标。</param>
/// <returns>一个布尔结果。</returns>
static bool block_array_contains(const Coordinate *const blocks, int length, Coordinate block) {
	for (int i = 0; i < length; i++) {
		if (blocks[i].x == block.x && blocks[i].y == block.y) {
			return true;
		}
	}
	return false;
}
