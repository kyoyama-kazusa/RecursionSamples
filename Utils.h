#pragma once

#include <stdio.h>

#ifndef MAX
// �����������������һ����
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif // !MAX
#ifndef MIN
// �����������������һ��С��
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif // !MIN

void print_array(int *, int);
