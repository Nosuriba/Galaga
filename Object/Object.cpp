#include "Object.h"
#include "../DebugDisp.h"
Object::Object()
{
}

Object::~Object()
{
}

bool Object::SetAnim(ANIM key, anim_vec& data)
{
	return _animMap.try_emplace(key, std::move(data)).second;
}

void Object::ResetInvCnt()
{
	_invCnt = 0;
}

bool Object::animKey(const ANIM key)
{
	/// ó·äOèàóù
	if (key < ANIM::NORMAL || key > ANIM::MAX)
	{
		return false;
	}
	_animKey = key;

	return true;
}

const ANIM& Object::animKey() const
{
	return _animKey;
}

void Object::AnimUpdate()
{
	if (_invCnt >= _animMap[_animKey][_animID].second)
	{
		_invCnt = 0;
		_animID = (_animID + 1) % _animMap[_animKey].size();
	}
	++_invCnt;
	DeathUpdate();
}

void Object::DeathUpdate()
{
	if (!_isAlive && _animKey == ANIM::BLAST)
	{
		/// å„Ç≈èCê≥
		_isDeath = (_animMap[_animKey][_animID].first == -1);
	}
}

void Object::Draw()
{
	if (_animMap.find(_animKey) == _animMap.end())
	{
		return;
	}
	if (_animID > _animMap[_animKey].size())
	{
		return;
	}

	AnimUpdate();
	//DrawGraph(_pos.x, _pos.y, _animMap[_animKey][_animID].first, true);

	DrawRotaGraph(_pos.x, _pos.y, 1.0, 0, _animMap[_animKey][_animID].first, true);
}

bool Object::GetDeath() const
{
	return _isDeath;
}

const Vector2 & Object::pos() const
{
	return _pos;
}
