#pragma once

#include "List.h"

/// <summary>
/// ��ʾһ��ջ��
/// </summary>
typedef struct {
	/// <summary>
	/// ��ʾ�ײ��˳���
	/// </summary>
	List *backing_list;
} Stack;

/// <summary>
/// ��ʾ����ÿһ��ջ���Ԫ��ʱִ�еĺ���ָ�롣
/// </summary>
typedef void (*StackTraverseAction)(int);

void push(Stack *const, int);
void traverse(const Stack *const, StackTraverseAction);
void dispose_stack(Stack *const stack);
int pop(Stack *const);
int peek(const Stack *const);
Stack *create_stack(int);
