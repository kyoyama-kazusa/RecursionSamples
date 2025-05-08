#pragma once

#include <stdio.h>

unsigned long long factorial(int, unsigned long long);

void entry(void) {
	printf("0 �Ľ׳��� %lld��\n", factorial(0, 1));
	printf("1 �Ľ׳��� %lld��\n", factorial(1, 1));
	printf("3 �Ľ׳��� %lld��\n", factorial(3, 1));
	printf("10 �Ľ׳��� %lld��\n", factorial(10, 1));
	printf("15 �Ľ׳��� %lld��\n", factorial(15, 1));
}

/// <summary>
/// β�ݹ麯����β�ݹ�ĵݹ��߼�������������������һ������������ط���
/// </summary>
/// <param name="value">��ֵ��</param>
/// <param name="accumulator">���۽����</param>
/// <returns>�����</returns>
static unsigned long long factorial(int value, unsigned long long accumulator) {
	if (value == 0) {
		// �ݹ���� - ֱ�ӷ��ش���Ĳ�����
		return accumulator;
	}

	// ����β�ݹ���� - ����Ҫ�ò������ս�����õݹ��߼�һ���� return ���ִ�е�ʱ����Ϊ���һ��ִ�С�
	// ��ʹ������д return factorial(value - 1) * value Ҳ���У�
	// ��Ϊ�������һ�� * value ����Ȼ��ŷ��ء�
	return factorial(value - 1, value * accumulator);
}
