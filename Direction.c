#include "Direction.h"

/// <summary>
/// 方向字符串。
/// </summary>
static DirectionString d[4] = { "↑", "↓", "←", "→" };

/// <summary>
/// 获取指定方向的打印符号。
/// </summary>
/// <param name="direction">方向。</param>
/// <returns>符号字符。</returns>
DirectionString get_direction_string(Direction direction) {
	return d[(int)direction];
}
