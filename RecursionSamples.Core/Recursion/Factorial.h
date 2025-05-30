/*
* �׳�����
* 
* ����һ��������������Ľ׳ˡ�
* һ�����Ľ׳˵��ڴ� 1 ��ʼ�������������ֱ�����������ĳ˻����� 5 �Ľ׳˵��� 1 * 2 * 3 * 4 * 5���� 120��
* 
* �׳�����ǳ��ʺ����ڳ�ѧ�ݹ飬�ݹ�ı�������һ��������������������ǰһ��״̬ͨ������ﵽ��һ��״̬������ǰ������״̬�ļ����߼���һ�µġ�
* ��Ȼ��f(n - 1) * n �͵��� f(n)���� f(n - 1) �ĵ����ֿ��Ե��� f(n - 2) * (n - 1)��������ô������ʽ�Ӿ��ҵ��ˡ�
* �ݹ�ı���������ͬ�ĺ������˴������ f��������ظ�������ֻ����ÿһ�ε����ݹ�ģ����ԭ����ͬ��ֱ����� f ����ֱ�ӷ��ؽ��ʱ������
*/

#pragma once

#include <stdio.h>

unsigned long long factorial(int value);

void entry(void) {
	printf("0 �Ľ׳��� %lld��\n", factorial(0));
	printf("1 �Ľ׳��� %lld��\n", factorial(1));
	printf("3 �Ľ׳��� %lld��\n", factorial(3));
	printf("10 �Ľ׳��� %lld��\n", factorial(10));
	printf("15 �Ľ׳��� %lld��\n", factorial(15));
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