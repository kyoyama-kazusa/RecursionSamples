#include "Direction.h"

/// <summary>
/// �����ַ�����
/// </summary>
static DirectionString d[4] = { "��", "��", "��", "��" };

/// <summary>
/// ��ȡָ������Ĵ�ӡ���š�
/// </summary>
/// <param name="direction">����</param>
/// <returns>�����ַ���</returns>
DirectionString get_direction_string(Direction direction) {
	return d[(int)direction];
}
