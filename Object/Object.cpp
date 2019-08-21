#include <DxLib.h>
#include "Object.h"
#include "Shot.h"
#include "../DebugDisp.h"

int Object::_leadCnt = 0;
enTbl_pair Object::_moveTblInfo = {0,0};

Object::Object()
{
	_isTable = false;
	_isAlive = true;
	_isDeath = false;

	_invCnt = 0;
	_animID = 0;
	_enAction = 0;

	/*for (auto& shot : _shots)
	{
		shot = std::make_shared<Shot>(Vector2d(0, 0));
	}*/
}

Object::~Object()
{
}

Rect Object::GetRect() const
{
	return _rect;
}

shot_array Object::GetShot() const
{
	return _shots;
}

void Object::ShotDelete(const shared_shot & shot)
{
	for (auto& s : _shots)
	{
		if (s != nullptr && s == shot)
		{
			s = nullptr;
		}
	}
}

void Object::SetSigEnd(const Vector2d& sigEnd)
{
	/// 何もしない
}

bool Object::IsAlive() const
{
	return _isAlive;
}

void Object::ChangeAlive()
{
	_isAlive = false;
}

bool Object::GetDeath() const
{
	return _isDeath;
}

const Vector2d & Object::GetPos() const
{
	return _pos;
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

void Object::ResetAnim()
{
	_invCnt = 0;
	_animID = 0;
}

bool Object::animKey(const ANIM key)
{
	/// 例外処理
	if (key < ANIM::NORMAL || key > ANIM::MAX)
	{
		return false;
	}
 	_animKey = key;

	return true;
}

void Object::AnimUpdate(const int & animSpeed)
{
	if (_invCnt >= _animMap[_animKey][_animID].second)
	{
		auto debug = _animMap[_animKey][_animMap[_animKey].size() - 1].second;
		_animID	   = (_animID + 1) % _animMap[_animKey].size();
		_invCnt    = (_invCnt < _animMap[_animKey][_animMap[_animKey].size() - 1].second ? _invCnt : 0);
	}
	_leadCnt = (_leadCnt < _animMap[_animKey][_animMap[_animKey].size() - 1].second ? _leadCnt : 0);
	_invCnt += animSpeed;
}

const ANIM& Object::animKey() const
{
	return _animKey;
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

	for (auto shot : _shots)
	{
		if (shot != nullptr)
		{
			shot->Draw(static_cast<int>(GetObjID()));
		}
	}
	DrawRotaGraph(_pos.x, _pos.y, 1.0, _rad, _animMap[_animKey][_animID].first, true);
}

void Object::LeadAnimUpdate()
{
	++_leadCnt;
}

bool Object::IsMoveTbl() const
{
	return _isTable;
}

void Object::SetTblInfo(const enTbl_pair& tblInfo)
{
	/// 最初の敵がﾃｰﾌﾞﾙに配置された時、情報を更新する
	if (_isTable)
	{
		_moveTblInfo = tblInfo;
	}
}