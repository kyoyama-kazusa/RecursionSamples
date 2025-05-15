#pragma once

#include <stdio.h>
#include <string.h>

/// <summary>
/// 定义一个打印函数，专门用于打印柱子从参数 #1 往参数 #2 移动的过程。
/// </summary>
typedef void (*ColumnMovingPrinter)(const char *const, const char *const);

void printer(const char *const, const char *const);
void solve(int, const char *const, const char *const, const char *const, ColumnMovingPrinter);

void entry(void) {
	solve(3, "初始列", "辅助列", "目标列", printer);
}

static void printer(const char *const base, const char *const target) {
	char sequences[3] = { 'a', 'b', 'c' };
	char baseColumnChar = strcmp(base, "初始列") == 0 ? sequences[0] : strcmp(base, "辅助列") == 0 ? sequences[1] : sequences[2];
	char targetColumnChar = strcmp(target, "初始列") == 0 ? sequences[0] : strcmp(target, "辅助列") == 0 ? sequences[1] : sequences[2];
	printf("移动%s的圆盘到%s去（%c -> %c）\n", base, target, baseColumnChar, targetColumnChar);
}

static void solve(
	int count,
	const char *const base,
	const char *const auxiliary,
	const char *const target,
	ColumnMovingPrinter printer
) {
#pragma region 汉诺塔处理本质
	// 我知道你肯定理解不了，一大堆都是套壳，本质就那一个 if 和 printer 操作。你肯定想知道为什么这个套壳能完成目标任务。
	//
	// 我们直接拿 count = 3 来举例就行：
	// solve(3, base, auxiliary, target)
	// ├─ solve(2, base, target, auxiliary)
	// │  ├─ solve(1, base, auxiliary, target)
	// │  │  ├─ solve(0, base, target, auxiliary) → 返回
	// │  │  → 打印 base→target
	// │  │  ├─ solve(0, auxiliary, base, target) → 返回
	// │  ├─ 打印 base→auxiliary
	// │  ├─ solve(1, target, base, auxiliary)
	// │  │  ├─ solve(0, target, auxiliary, base) → 返回
	// │  │  → 打印 target→auxiliary
	// │  │  ├─ solve(0, base, target, auxiliary) → 返回
	// ├─ 打印 base→target
	// ├─ solve(2, auxiliary, base, target)
	// │  ├─ solve(1, auxiliary, target, base)
	// │  │  ├─ solve(0, auxiliary, base, target) → 返回
	// │  │  → 打印 auxiliary→base
	// │  │  ├─ solve(0, target, auxiliary, base) → 返回
	// │  ├─ 打印 auxiliary→target
	// │  ├─ solve(1, base, auxiliary, target)
	// │  │  ├─ solve(0, base, target, auxiliary) → 返回
	// │  │  → 打印 base→target
	// │  │  ├─ solve(0, auxiliary, base, target) → 返回
	//
	// 关键机制：
	// 1、参数交换的魔法：
	//   在 solve(count - 1, base, target, auxiliary) 中，参数会顺序变为 (base, target, auxiliary)，
	//   这实际上将目标柱从 target 改成了 auxiliary，辅助柱从 auxiliary 改为了 target
	//   这种参数轮换让同一个函数能处理不同位置的子任务。
	//
	// 2、递归深度优先
	//   程序会优先执行最深层的递归调用，直到遇到 count == 0 时才会返回。
	//   当 count == 1 的时候，实际执行的路径是：
	//      1. 进入 solve(0, ...) 直接立即返回
	//      2. 打印移动单个圆盘的操作
	//      3. 进入另一个 solve(0, ...) 然后也是立即返回
	//
	// 3、执行时序控制
	//   printer 位于两个递归调用之间，这确保了：
	//      1. 上层的盘子必须优先移动（第一个递归调用）
	//      2. 当前盘子移动（打印语句）
	//      3. 下层盘子后移动（第二个递归调用）
	//   从本质上讲，你可以把不递归的语句和递归的语句拆开来分析。
	//
	// 在同一个函数里，递归后面的语句你可以直接从人脑的理解思维上给理解为“整个递归完成了之后所做的事情”。
	// 比如说这个地方，printer 函数放在第一个递归部分的后面，你可以直接理解成“最下面的盘子必须上方所有盘子全移动了，它才会动”。
	// 所以这个递归巧妙在，实际执行的逻辑并非是我看起来这个层级就遇到的内容，虽然看起来像是一个层级，但递归在函数里必须要理解成“一大坨操作”，
	// 必须这一坨操作都完成了，递归才叫完成。
#pragma endregion

	if (count == 0) {
		// 递归完成。
		return;
	}

	// 先递归移动的是非最底层圆盘的每一个。
	solve(count - 1, base, auxiliary, target, printer);

	// 到这里就说明底层圆盘没动，但上面全部都到辅助列了。
	// 打印底层圆盘的信息，说明移动走向。
	printer(base, target);

	// 然后递归移动剩下的部分。因为此时辅助列放满了非底层的圆盘，而目标列已经有一个底层圆盘了，所以现在递归剩下的就行了。
	solve(count - 1, auxiliary, base, target, printer);
}
