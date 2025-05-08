#include <iostream>
#include <functional>

/// <summary>
/// 表示一个映射函数。
/// </summary>
/// <typeparam name="T">表示输入的类型。</typeparam>
/// <typeparam name="TResult">表示返回的类型。</typeparam>
template<class T, class TResult>
using Projection = std::function<TResult(T)>;

/// <summary>
/// <para>声明一个 Y-组合子，用于创建递归 lambda 表达式。你可以使用这个表达式完成匿名函数（lambda 表达式）的递归处理。</para>
/// <para>
/// 比如说我要计算阶乘，因为 lambda 表达式不带函数名，所以无法递归自身，于是我们用这个函数，通过外套一个函数 f，
/// 用来辅助执行递归阶乘计算，然后将整个表达式传入进去，就可以得到一个函数；这个函数只要传入固定参数就可以得到阶乘结果。
/// </para>
/// </summary>
/// <typeparam name="T">输入的元素的数据类型。</typeparam>
/// <typeparam name="TResult">输出结果的数据类型。</typeparam>
/// <param name="f">函数。</param>
/// <returns>通过 Y-组合子创建出来的递归 lambda 表达式。</returns>
template<class T, class TResult>
Projection<T, TResult> y_combinator(Projection<Projection<T, TResult>, Projection<T, TResult>> f) {
	// Y-组合子的写法：f(y(f))(参数)，其中的 y 是 Y-组合子（这个函数本身）。
	return [f](T value) { return f(y_combinator(f))(value); };
}

int main()
{
	// 创建一个 lambda 表达式，这个 lambda 表达式用于处理阶乘运算。
	// 但是 lambda 表达式自身因为缺少名称所以无法递归，需要外面套一个 lambda 参数用来表示这个递归式子。
	// 但是这种套法就没办法调用了，需要用 Y-组合子转换为能正常运作的式子，
	// 这样 lambda 表达式就可以在外面临时创建一个变量表示其递归的函数名用作递归调用了。
	Projection<Projection<int, int>, Projection<int, int>> factorial = [](Projection<int, int> lambda) {
		return [lambda](int value) {
			if (value == 0 || value == 1) {
				return 1;
			}
			return value * lambda(value - 1);
		};
	};

	// 转换成可调用的函数。
	auto converted = y_combinator(factorial);

	// 输出结果。
	auto input = 6;
	std::cout << input << " 的阶乘是 " << converted(input) << "。" << std::endl;
	return 0;
}
