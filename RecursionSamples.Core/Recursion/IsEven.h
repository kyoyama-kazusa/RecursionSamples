/*
* ����һ�����Ƿ���ż��
* 
* ����Ȼ���Բ��õݹ飬���ǹ�����ʵ��һ�¡�ʵ�ֵķ�ʽ��Ȼ���ҵ�һ����ʼ״̬��ǿ�Ƹ������Ƕ�ֵ��Ȼ�����������С��ģֱ�������ֵ����ܱ����ء�
* ����˵���� 4 �Ƿ���ż������ô����״̬ f(4) ��Ȼ������ǰһ��״̬ f(3) ��ȡ���������Ϊ��ż���棩������ f(4) = !f(3)����ô���ݹ��̲���������
*/

#pragma once

#include <stdbool.h>
#include <stdio.h>

bool is_even(int);

void entry(void) {
	printf("0 %sż����\n", is_even(0) ? "��" : "����");
	printf("3 %sż����\n", is_even(3) ? "��" : "����");
	printf("10 %sż����\n", is_even(10) ? "��" : "����");
	printf("17 %sż����\n", is_even(17) ? "��" : "����");
	printf("160 %sż����\n", is_even(160) ? "��" : "����");
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
	return !is_even(value - 1);
}
