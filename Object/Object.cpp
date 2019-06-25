#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

std::map<ANIM, anim_vec> Object::GetAnim() const
{
	return _animMap;
}

bool Object::SetAnim(const ANIM key, const anim_vec& data)
{
	/// ��Ұ��݂̓o�^
	if (_animMap.find(key) == _animMap.end())
	{
		_animMap[key] = data;
		return true;
	}

	/// �o�^���s
	return false;
}
