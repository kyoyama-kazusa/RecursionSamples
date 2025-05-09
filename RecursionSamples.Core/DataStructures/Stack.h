#pragma once

#include "List.h"

/// <summary>
/// 表示一个栈。
/// </summary>
typedef struct {
	/// <summary>
	/// 表示底层的顺序表。
	/// </summary>
	List *backing_list;
} Stack;

/// <summary>
/// 表示遍历每一个栈里的元素时执行的函数指针。
/// </summary>
typedef void (*StackTraverseAction)(int);

void push(Stack *const, int);
void traverse(const Stack *const, StackTraverseAction);
void dispose_stack(Stack *const stack);
int pop(Stack *const);
int peek(const Stack *const);
Stack *create_stack(int);
