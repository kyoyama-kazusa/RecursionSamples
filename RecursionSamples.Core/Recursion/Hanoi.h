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
	solve(3, "��ʼ��", "Ŀ����", "������", printer);
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
	const char *const target,
	const char *const auxiliary,
	ColumnMovingPrinter printer
) {
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
