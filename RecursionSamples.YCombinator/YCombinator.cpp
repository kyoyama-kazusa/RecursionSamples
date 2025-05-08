#include <iostream>
#include <functional>

/// <summary>
/// ��ʾһ��ӳ�亯����
/// </summary>
/// <typeparam name="T">��ʾ��������͡�</typeparam>
/// <typeparam name="TResult">��ʾ���ص����͡�</typeparam>
template<class T, class TResult>
using Projection = std::function<TResult(T)>;

/// <summary>
/// <para>����һ�� Y-����ӣ����ڴ����ݹ� lambda ���ʽ�������ʹ��������ʽ�������������lambda ���ʽ���ĵݹ鴦��</para>
/// <para>
/// ����˵��Ҫ����׳ˣ���Ϊ lambda ���ʽ�����������������޷��ݹ������������������������ͨ������һ������ f��
/// ��������ִ�еݹ�׳˼��㣬Ȼ���������ʽ�����ȥ���Ϳ��Եõ�һ���������������ֻҪ����̶������Ϳ��Եõ��׳˽����
/// </para>
/// </summary>
/// <typeparam name="T">�����Ԫ�ص��������͡�</typeparam>
/// <typeparam name="TResult">���������������͡�</typeparam>
/// <param name="f">������</param>
/// <returns>ͨ�� Y-����Ӵ��������ĵݹ� lambda ���ʽ��</returns>
template<class T, class TResult>
Projection<T, TResult> y_combinator(Projection<Projection<T, TResult>, Projection<T, TResult>> f) {
	// Y-����ӵ�д����f(y(f))(����)�����е� y �� Y-����ӣ��������������
	return [f](T value) { return f(y_combinator(f))(value); };
}

int main()
{
	// ����һ�� lambda ���ʽ����� lambda ���ʽ���ڴ���׳����㡣
	// ���� lambda ���ʽ������Ϊȱ�����������޷��ݹ飬��Ҫ������һ�� lambda ����������ʾ����ݹ�ʽ�ӡ�
	// ���������׷���û�취�����ˣ���Ҫ�� Y-�����ת��Ϊ������������ʽ�ӣ�
	// ���� lambda ���ʽ�Ϳ�����������ʱ����һ��������ʾ��ݹ�ĺ����������ݹ�����ˡ�
	Projection<Projection<int, int>, Projection<int, int>> factorial = [](Projection<int, int> lambda) {
		return [lambda](int value) {
			if (value == 0 || value == 1) {
				return 1;
			}
			return value * lambda(value - 1);
		};
	};

	// ת���ɿɵ��õĺ�����
	auto converted = y_combinator(factorial);

	// ��������
	auto input = 6;
	std::cout << input << " �Ľ׳��� " << converted(input) << "��" << std::endl;
	return 0;
}
