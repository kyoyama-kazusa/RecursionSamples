#pragma once

/// <summary>
/// 表示一个方向的枚举。
/// </summary>
typedef enum {
	/// <summary>
	/// 表示朝上。
	/// </summary>
	Up,

	/// <summary>
	/// 表示朝下。
	/// </summary>
	Down,

	/// <summary>
	/// 表示朝左。
	/// </summary>
	Left,

	/// <summary>
	/// 表示朝右。
	/// </summary>
	Right
} Direction;

/// <summary>
/// 表示方向字符串。
/// </summary>
typedef const char *const DirectionString;

DirectionString get_direction_string(Direction);
