/*
* ���������齫��
*
* ��ѹ�����󵱳�һ����Ϸ���̣�Ȼ�����齫һ��һ����ô�����������ϡ���ʱ�����齫�����Ϸ����������Էֲ㡣
* ������Ϸǿ�ƹ涨��һ���齫��ռ�����̵� 2 * 2 ���ĸ���Ԫ��λ�ã�������㣩������Ҳ���ں���������ڷŵ�״̬��
* ��������ֻ�����齫�ưڷ�����һ���齫�Ƶ��Ϸ���ȫ�ص��������ص�һ�룬�����ķ�֮һ����һ��ı߽ǵ����������������ص�״̬��
* ������Ϸ�涨�����齫ֻ�����ϲ�ģ�������ѹ�ŵ��齫������ֻѹ�� 1/4 ��һ��Ҳ���С�
* ��ô������ָ��һ���齫�����ҳ������齫�����·�ѹ�ŵ�ȫ���齫���������齫������Щ�齫�������齫�Ƶ�ֱ�ӻ�����Լ��
* ������������������Щ�齫����Զ���޷������ߡ�
*
* ����㷨��Ҫ������ȵݹ���У������Ҵ�����齫��ʼ�����ҡ�������齫���·����� 9 ��������Ϊѹ�ŵİڷ�״̬λ�ã�����
*
*   (1) ���Ͻǣ�
*   (2) �Ϸ�һ�����
*   (3) ���Ͻǣ�
*   (4) ���һ�����
*   (5) ���·���
*   (6) �ұ�һ�����
*   (7) ���½ǣ�
*   (8) �·�һ�����
*   (9) ���½ǡ�
*
* һ���� 9 �������ֱ��ǿ������� 9 �������Ȼ���� 9 ���������һ�����Ƿ�ʵ�����������������ơ�����У���˵������ѹ���ˡ�
* ѹ���˵��Ƽ�����Ϊ��һ�ε�Ŀ���ƣ�Ȼ�������������������еݹ�ѹ�ŵ��ƣ�ֱ�ӻ���ѹ�ŵģ�����������ȫ�г��������������Ľ���ˡ�
*/

#pragma once

#include "../DataStructures/Coordinate.h"
#include <stdbool.h>
#include <stdio.h>


/// <summary>
/// ��ʾ��������Ĳ�����
/// </summary>
#define LAYERS_COUNT 4

/// <summary>
/// ��ʾ���������¼����Ļ��������ȡ�
/// </summary>
#define BUFFER_LENGTH 20


/// <summary>
/// ��ʾƫ������
/// </summary>
static const int offsets[3] = { -1, 0, 1 };

/// <summary>
/// ���ȱ�
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

	// �ڷſ�����ݡ�
	// ������ײ� 9 ����Ȼ����һ���� 4 ��������һ���� 1 ��������һ���� 4 ����
	// Ҳ����˵ blocks ��������Ϊ 0 ������ײ㣬����Խ��Խ�ϲ㡣
	const Coordinate *const blocks[LAYERS_COUNT] = { layer1, layer2, layer3, layer4 };

	// ��������
	Coordinate buffer[BUFFER_LENGTH];
	int length = 0;

	// �ݹ����ѹ�ŵ����ꡣ
	// ����������ǵ� 2 ���Ψһ��������꣬��ô���²���� 9 + 4 һ�� 13 ��λ�á�
	dfs(2, layer3[0], blocks, buffer, &length);

	// ��ӡѹס�Ŀ�����ꡣ��ӡ���Ӧ���� 13 ����
	for (int i = 0; i < length; i++) {
		printf("(%d, %d)\n", buffer[i].x, buffer[i].y);
	}
}

/// <summary>
/// ����������ȣ����������²��Ƿ���ѹ�ţ�ѹ����Щ��
/// </summary>
/// <param name="layer">��ǰ�㡣</param>
/// <param name="block">��ǰ������ꡣ</param>
/// <param name="blocks">���еĿ顣</param>
/// <param name="buffer">�洢ѹ�ŵ�����Ŀ顣</param>
/// <param name="length">���� buffer ��ʵ�ʴ洢Ԫ�صĳ��ȡ�</param>
static void dfs(int layer, Coordinate block, const Coordinate *const *const blocks, Coordinate *const buffer, int *const length) {
	if (layer <= 0) {
		// �Ѿ������ˣ����ü��������ˡ�
		return;
	}

	for (int i = layer; i < LAYERS_COUNT; i++) {
		for (int x_offset_index = 0; x_offset_index < 3; x_offset_index++) {
			for (int y_offset_index = 0; y_offset_index < 3; y_offset_index++) {
				// �����ѹ�ŵ����ꡣ
				Coordinate new_block = { block.x + offsets[x_offset_index], block.y + offsets[y_offset_index] };

				if (// �ж�ѹ�ŵ������Ƿ������ԭ�����������б��
					block_array_array_contains(blocks, layer - 1, new_block)
					// ѹ�ŵġ��ж���������Ƿ��Ѿ���¼���������¼����������
					&& !block_array_contains(buffer, *length, new_block)) {

					// ���뵽���б��
					buffer[*length] = new_block;
					(*length)++;

					// Ȼ��ݹ����ġ�
					dfs(layer - 1, new_block, blocks, buffer, length);
				}
			}
		}
	}
}

/// <summary>
/// �����Ƿ�ָ����Ϳ�������Ѿ�������Ŀ�����������еĻ��ͷ��� true��
/// </summary>
/// <param name="blocks">��¼�˵Ŀ顣</param>
/// <param name="layer">�㡣</param>
/// <param name="block">���ꡣ</param>
/// <returns>һ�����������</returns>
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
/// �����Ƿ�ָ����Ϳ�������Ѿ�������Ŀ�����������еĻ��ͷ��� true��
/// </summary>
/// <param name="blocks">��¼�˵Ŀ顣</param>
/// <param name="length">��¼�˵Ŀ��Ԫ��������</param>
/// <param name="block">���ꡣ</param>
/// <returns>һ�����������</returns>
static bool block_array_contains(const Coordinate *const blocks, int length, Coordinate block) {
	for (int i = 0; i < length; i++) {
		if (blocks[i].x == block.x && blocks[i].y == block.y) {
			return true;
		}
	}
	return false;
}
