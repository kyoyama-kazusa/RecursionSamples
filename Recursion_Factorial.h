#pragma once

#include <stdio.h>

unsigned long long factorial(int value);

void entry(void) {
	printf("0 �Ľ׳��� %lld��\n", factorial(0, 1));
	printf("1 �Ľ׳��� %lld��\n", factorial(1, 1));
	printf("3 �Ľ׳��� %lld��\n", factorial(3, 1));
	printf("10 �Ľ׳��� %lld��\n", factorial(10, 1));
	printf("15 �Ľ׳��� %lld��\n", factorial(15, 1));
}

/// <summary>
/// ���ָ�����ֵĽ׳ˡ�
/// </summary>
/// <param name="value">��ֵ��</param>
/// <returns>�׳˽����</returns>
static unsigned long long factorial(int value) {
	if (value == 0) {
		return 1;
	}
	return value * factorial(value - 1);
}