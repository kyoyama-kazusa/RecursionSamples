#pragma once

/// <summary>
/// ��ʾһ�������ö�١�
/// </summary>
typedef enum {
	/// <summary>
	/// ��ʾ���ϡ�
	/// </summary>
	Up,

	/// <summary>
	/// ��ʾ���¡�
	/// </summary>
	Down,

	/// <summary>
	/// ��ʾ����
	/// </summary>
	Left,

	/// <summary>
	/// ��ʾ���ҡ�
	/// </summary>
	Right
} Direction;

/// <summary>
/// ��ʾ�����ַ�����
/// </summary>
typedef const char *const DirectionString;

DirectionString get_direction_string(Direction);
