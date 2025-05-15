#pragma once

#include <stdio.h>
#include <string.h>

/// <summary>
/// ����һ����ӡ������ר�����ڴ�ӡ���ӴӲ��� #1 ������ #2 �ƶ��Ĺ��̡�
/// </summary>
typedef void (*ColumnMovingPrinter)(const char *const, const char *const);

void printer(const char *const, const char *const);
void solve(int, const char *const, const char *const, const char *const, ColumnMovingPrinter);

void entry(void) {
	solve(3, "��ʼ��", "������", "Ŀ����", printer);
}

static void printer(const char *const base, const char *const target) {
	char sequences[3] = { 'a', 'b', 'c' };
	char baseColumnChar = strcmp(base, "��ʼ��") == 0 ? sequences[0] : strcmp(base, "������") == 0 ? sequences[1] : sequences[2];
	char targetColumnChar = strcmp(target, "��ʼ��") == 0 ? sequences[0] : strcmp(target, "������") == 0 ? sequences[1] : sequences[2];
	printf("�ƶ�%s��Բ�̵�%sȥ��%c -> %c��\n", base, target, baseColumnChar, targetColumnChar);
}

static void solve(
	int count,
	const char *const base,
	const char *const auxiliary,
	const char *const target,
	ColumnMovingPrinter printer
) {
#pragma region ��ŵ��������
	// ��֪����϶���ⲻ�ˣ�һ��Ѷ����׿ǣ����ʾ���һ�� if �� printer ��������϶���֪��Ϊʲô����׿������Ŀ������
	//
	// ����ֱ���� count = 3 ���������У�
	// solve(3, base, auxiliary, target)
	// ���� solve(2, base, target, auxiliary)
	// ��  ���� solve(1, base, auxiliary, target)
	// ��  ��  ���� solve(0, base, target, auxiliary) �� ����
	// ��  ��  �� ��ӡ base��target
	// ��  ��  ���� solve(0, auxiliary, base, target) �� ����
	// ��  ���� ��ӡ base��auxiliary
	// ��  ���� solve(1, target, base, auxiliary)
	// ��  ��  ���� solve(0, target, auxiliary, base) �� ����
	// ��  ��  �� ��ӡ target��auxiliary
	// ��  ��  ���� solve(0, base, target, auxiliary) �� ����
	// ���� ��ӡ base��target
	// ���� solve(2, auxiliary, base, target)
	// ��  ���� solve(1, auxiliary, target, base)
	// ��  ��  ���� solve(0, auxiliary, base, target) �� ����
	// ��  ��  �� ��ӡ auxiliary��base
	// ��  ��  ���� solve(0, target, auxiliary, base) �� ����
	// ��  ���� ��ӡ auxiliary��target
	// ��  ���� solve(1, base, auxiliary, target)
	// ��  ��  ���� solve(0, base, target, auxiliary) �� ����
	// ��  ��  �� ��ӡ base��target
	// ��  ��  ���� solve(0, auxiliary, base, target) �� ����
	//
	// �ؼ����ƣ�
	// 1������������ħ����
	//   �� solve(count - 1, base, target, auxiliary) �У�������˳���Ϊ (base, target, auxiliary)��
	//   ��ʵ���Ͻ�Ŀ������ target �ĳ��� auxiliary���������� auxiliary ��Ϊ�� target
	//   ���ֲ����ֻ���ͬһ�������ܴ���ͬλ�õ�������
	//
	// 2���ݹ��������
	//   ���������ִ�������ĵݹ���ã�ֱ������ count == 0 ʱ�Ż᷵�ء�
	//   �� count == 1 ��ʱ��ʵ��ִ�е�·���ǣ�
	//      1. ���� solve(0, ...) ֱ����������
	//      2. ��ӡ�ƶ�����Բ�̵Ĳ���
	//      3. ������һ�� solve(0, ...) Ȼ��Ҳ����������
	//
	// 3��ִ��ʱ�����
	//   printer λ�������ݹ����֮�䣬��ȷ���ˣ�
	//      1. �ϲ�����ӱ��������ƶ�����һ���ݹ���ã�
	//      2. ��ǰ�����ƶ�����ӡ��䣩
	//      3. �²����Ӻ��ƶ����ڶ����ݹ���ã�
	//   �ӱ����Ͻ�������԰Ѳ��ݹ�����͵ݹ��������������
	//
	// ��ͬһ��������ݹ�������������ֱ�Ӵ����Ե����˼ά�ϸ����Ϊ�������ݹ������֮�����������顱��
	// ����˵����ط���printer �������ڵ�һ���ݹ鲿�ֵĺ��棬�����ֱ�����ɡ�����������ӱ����Ϸ���������ȫ�ƶ��ˣ����Żᶯ����
	// ��������ݹ������ڣ�ʵ��ִ�е��߼��������ҿ���������㼶�����������ݣ���Ȼ����������һ���㼶�����ݹ��ں��������Ҫ���ɡ�һ�����������
	// ������һ�����������ˣ��ݹ�Ž���ɡ�
#pragma endregion

	if (count == 0) {
		// �ݹ���ɡ�
		return;
	}

	// �ȵݹ��ƶ����Ƿ���ײ�Բ�̵�ÿһ����
	solve(count - 1, base, auxiliary, target, printer);

	// �������˵���ײ�Բ��û����������ȫ�������������ˡ�
	// ��ӡ�ײ�Բ�̵���Ϣ��˵���ƶ�����
	printer(base, target);

	// Ȼ��ݹ��ƶ�ʣ�µĲ��֡���Ϊ��ʱ�����з����˷ǵײ��Բ�̣���Ŀ�����Ѿ���һ���ײ�Բ���ˣ��������ڵݹ�ʣ�µľ����ˡ�
	solve(count - 1, auxiliary, base, target, printer);
}
