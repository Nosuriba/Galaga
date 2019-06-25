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

bool Object::SetAnim(const ANIM key, const anim_vec&& data)
{
	/// ±ÆÒ°¼®Ý‚Ì“o˜^
	if (_animMap.find(key) == _animMap.end())
	{
		/*_animMap[key]*/
		//_animMap[key] = data;
		std::move(data.begin(), data.end(), std::back_inserter(_animMap[key]));
		return true;
	}

	/// “o˜^Ž¸”s
	return false;
}
