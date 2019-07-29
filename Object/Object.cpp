#include "Object.h"
#include "../DebugDisp.h"

int Object::_leadCnt = 0;
enTbl_pair Object::_moveTblInfo = {0,0};

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

bool Object::DestryCheck()
{
	if (_isAlive)
	{
		return false;
	}

	if (_animKey == ANIM::DEATH)
	{
		_isDeath = (_animMap[_animKey][_animID].first == -1);
	}
	return true;
}

void Object::SetInvCnt(const int & leadCnt)
{
	_invCnt = leadCnt;
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

//const ANIM& Object::animKey() const
//{
//	return _animKey;
//}

void Object::AnimUpdate()
{
	if (_invCnt >= _animMap[_animKey][_animID].second)
	{
		auto debug = _animMap[_animKey][_animMap[_animKey].size() - 1].second;
		_animID	   = (_animID + 1) % _animMap[_animKey].size();
		_invCnt    = (_invCnt < _animMap[_animKey][_animMap[_animKey].size() - 1].second ? _invCnt : 0);
	}
	_leadCnt = (_leadCnt < _animMap[_animKey][_animMap[_animKey].size() - 1].second  ? _leadCnt : 0);
	++_invCnt;
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

	DrawRotaGraph(_pos.x, _pos.y, 1.0, _rad, _animMap[_animKey][_animID].first, true);
}

void Object::LeadAnimUpdate()
{
	++_leadCnt;
}

bool Object::CheckMoveTbl() const
{
	return _tblFlag;
}

void Object::SetMoveTbl(const enTbl_pair& tblInfo)
{
	if (_tblFlag)
	{
		_moveTblInfo = tblInfo;
	}
	
}

int Object::GetEnemyNum() const
{
	return _enNum;
}

bool Object::GetDeath() const
{
	return _isDeath;
}