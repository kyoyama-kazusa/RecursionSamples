#pragma once

#include <stdio.h>

#ifndef MAX
// 定义求得两个参数哪一个大。
#define MAX(a,b) (((a) > (b)) ? (a) : (b))
#endif // !MAX
#ifndef MIN
// 定义求得两个参数哪一个小。
#define MIN(a,b) (((a) < (b)) ? (a) : (b))
#endif // !MIN

void print_array(int *, int);
