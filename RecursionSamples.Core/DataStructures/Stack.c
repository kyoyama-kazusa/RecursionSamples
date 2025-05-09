#include "List.h"
#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// ����һ��ջ�ڴ�����ݽṹ��
/// </summary>
/// <param name="initial_capacity">��ʼ������</param>
/// <returns>ջ��ʵ������Ҫ�ȵ��� dispose_stack ����� free �����ͷš�</returns>
Stack *create_stack(int initial_capacity) {
	Stack *result = (Stack *)malloc(sizeof(Stack));
	if (!result) {
		printf("�ڴ����ʧ�ܡ�");
		exit(-1);
	}

	result->backing_list = create_list(initial_capacity);
	return result;
}

/// <summary>
/// ��ָ��Ԫ����ջ��ջ�
/// </summary>
/// <param name="stack">ջ��</param>
/// <param name="value">��ֵ��</param>
void push(Stack *const stack, int value) {
	list_add(stack->backing_list, value);
}

/// <summary>
/// ��ջ������һ��Ԫ�ص�����
/// </summary>
/// <param name="stack">ջ��</param>
/// <returns>��ջ����ֵ��</returns>
int pop(Stack *const stack) {
	return list_remove_at(stack->backing_list, stack->backing_list->size - 1);
}

/// <summary>
/// �鿴ջ�Ķ���Ԫ�ء�
/// </summary>
/// <param name="stack">ջ��</param>
/// <returns>����Ԫ�ء�</returns>
int peek(const Stack *const stack) {
	return stack->backing_list->data[stack->backing_list->size - 1];
}

/// <summary>
/// ��ȡ��ǰջ��Ԫ��������
/// </summary>
/// <param name="stack">ջ��</param>
/// <returns>Ԫ��������</returns>
int get_stack_size(const Stack *const stack) {
	return stack->backing_list->size;
}

/// <summary>
/// �����������ÿһ��Ԫ�ء�
/// </summary>
/// <param name="stack">ջ��</param>
/// <param name="traverse_action">�����Ļص�������</param>
void traverse(const Stack *const stack, StackTraverseAction traverse_action) {
	for (int i = 0; i < stack->backing_list->size; i++) {
		traverse_action(stack->backing_list->data[i]);
	}
}

/// <summary>
/// �ͷ�һ��ջ���ڴ�洢�ռ䡣
/// </summary>
/// <param name="stack">ջ��</param>
void dispose_stack(Stack *const stack) {
	free(stack->backing_list->data);
	stack->backing_list->data = NULL;
	stack->backing_list->size = 0;
	stack->backing_list->capacity = 0;
}
