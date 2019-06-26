#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

bool Object::SetAnim(const ANIM key, const anim_vec&& data)
{
	/// ±ÆÒ°¼®Ý‚Ì“o˜^
	if (_animMap.find(key) == _animMap.end())
	{
		std::move(data.begin(), data.end(), std::back_inserter(_animMap[key]));
		return true;
	}

	/// “o˜^Ž¸”s
	return false;
} 

void Object::AnimUpdate()
{
	if (_invCnt++ > _animMap[_animKey][_animID].second)
	{
		_invCnt = 0;
		_animID = (_animID + 1) % _animMap[_animKey].size();
	}
}

void Object::Draw()
{
	if (_animID > _animMap[_animKey].size())
	{
		return;
	}
	DrawGraph(_pos.x, _pos.y, _animMap[_animKey][_animID].first, true);
}