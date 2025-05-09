#include "List.h"
#include "Stack.h"
#include <stdio.h>
#include <stdlib.h>

/// <summary>
/// 创建一个栈内存的数据结构。
/// </summary>
/// <param name="initial_capacity">初始容量。</param>
/// <returns>栈的实例。需要先调用 dispose_stack 后调用 free 函数释放。</returns>
Stack *create_stack(int initial_capacity) {
	Stack *result = (Stack *)malloc(sizeof(Stack));
	if (!result) {
		printf("内存分配失败。");
		exit(-1);
	}

	result->backing_list = create_list(initial_capacity);
	return result;
}

/// <summary>
/// 将指定元素入栈到栈里。
/// </summary>
/// <param name="stack">栈。</param>
/// <param name="value">数值。</param>
void push(Stack *const stack, int value) {
	list_add(stack->backing_list, value);
}

/// <summary>
/// 将栈里的最后一个元素弹出。
/// </summary>
/// <param name="stack">栈。</param>
/// <returns>出栈的数值。</returns>
int pop(Stack *const stack) {
	return list_remove_at(stack->backing_list, stack->backing_list->size - 1);
}

/// <summary>
/// 查看栈的顶部元素。
/// </summary>
/// <param name="stack">栈。</param>
/// <returns>顶部元素。</returns>
int peek(const Stack *const stack) {
	return stack->backing_list->data[stack->backing_list->size - 1];
}

/// <summary>
/// 获取当前栈的元素数量。
/// </summary>
/// <param name="stack">栈。</param>
/// <returns>元素数量。</returns>
int get_stack_size(const Stack *const stack) {
	return stack->backing_list->size;
}

/// <summary>
/// 遍历集合里的每一个元素。
/// </summary>
/// <param name="stack">栈。</param>
/// <param name="traverse_action">遍历的回调函数。</param>
void traverse(const Stack *const stack, StackTraverseAction traverse_action) {
	for (int i = 0; i < stack->backing_list->size; i++) {
		traverse_action(stack->backing_list->data[i]);
	}
}

/// <summary>
/// 释放一个栈的内存存储空间。
/// </summary>
/// <param name="stack">栈。</param>
void dispose_stack(Stack *const stack) {
	free(stack->backing_list->data);
	stack->backing_list->data = NULL;
	stack->backing_list->size = 0;
	stack->backing_list->capacity = 0;
}
