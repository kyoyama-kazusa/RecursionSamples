#pragma once

#include <stdio.h>
#include <stdbool.h>

bool is_even(int);
bool is_even_cached_entry(int);
bool is_even_cached(int, bool);

void entry(void) {
	printf("������ݹ����ģʽ��0 - ��ͨβ�ݹ飻1 - ������β�ݹ飩�����ûɶ����\n");

	int mode;
	int ignored = scanf("%d", &mode);
	bool (*function_pointer)(int) = mode == 0 ? is_even : is_even_cached_entry;
	printf("0 %sż����\n", function_pointer(0) ? "��" : "����");
	printf("3 %sż����\n", function_pointer(3) ? "��" : "����");
	printf("10 %sż����\n", function_pointer(10) ? "��" : "����");
	printf("17 %sż����\n", function_pointer(17) ? "��" : "����");
	printf("160 %sż����\n", function_pointer(160) ? "��" : "����");
}

/// <summary>
/// �ж�һ�����Ƿ���ż����
/// </summary>
/// <param name="value">��ֵ��</param>
/// <returns>�Ƿ���ż����</returns>
static bool is_even(int value) {
	if (value == 0) {
		return true;
	}
	if (value == 1) {
		return false;
	}

	// ֱ��һ���������������Ա�֤���ô��ݲ�����ͬʱ���ܱ�֤�ݹ������һ����
	return is_even(value - 2);
}

static bool is_even_cached_entry(int value) {
	return is_even_cached(value, true);
}

/// <summary>
/// ��β�ݹ������ģʽʵ���ж�һ�����Ƿ���ż����
/// </summary>
/// <param name="value">��ֵ��</param>
/// <param name="result">��ʱ��Ľ�������������ʼ��ʱ��� true��</param>
/// <returns>�Ƿ���ż����</returns>
static bool is_even_cached(int value, bool result) {
	if (value == 0) {
		return result;
	}
	if (value == 1) {
		return !result;
	}

	// �ò����洢����������ȱ�֤ !result �����������룬ʹ�ú������������һ��ִ�С�
	return is_even_cached(value - 1, !result);
}