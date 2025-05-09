#pragma once

#include "../DataStructures/Stack.h"
#include <stdio.h>
#include <stdlib.h>

unsigned long long factorial_stack_based(int value);

void entry(void) {
	printf("0 �Ľ׳��� %lld��\n", factorial_stack_based(0));
	printf("1 �Ľ׳��� %lld��\n", factorial_stack_based(1));
	printf("3 �Ľ׳��� %lld��\n", factorial_stack_based(3));
	printf("10 �Ľ׳��� %lld��\n", factorial_stack_based(10));
	printf("15 �Ľ׳��� %lld��\n", factorial_stack_based(15));
}

/// <summary>
/// �������� n �Ľ׳ˣ���ջ + ѭ��ģ��ݹ顣
/// </summary>
/// <param name="n">���֡�</param>
/// <returns>�����</returns>
unsigned long long factorial_stack_based(int n) {
	Stack *stack = create_stack(4);

	unsigned long long result = 1;

	// ѹ���ʼ���񣨴� n ��ʼ�𲽼��� 0����
	while (n != 0) {
		push(stack, n);
		n--;
	}

	// ���ε�ջ��Ԫ��¼���������
	while (get_stack_size(stack) != 0) {
		result *= pop(stack);
	}

	// �ͷ���ʱ������ջ��
	free(stack);

	// ���ؽ����
	return result;
}
