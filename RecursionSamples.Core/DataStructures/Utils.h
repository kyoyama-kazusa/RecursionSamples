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

// 将变量、表达式等内容转为等价的字符串写法。
#define nameof(x) #x

void print_array(int *, int);
