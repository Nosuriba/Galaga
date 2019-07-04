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

	/// debug用の描画で色々遊んでいる
	_dbgDrawBox(_rect.Left(), _rect.Top(), _rect.Right(), _rect.Bottom(), 0x00ff00, true);
	_dbgDrawCircle(_rect.center.x, _rect.center.y, _charSize.width / 2, 0xff0000, true);
	_dbgDrawLine(_rect.Left(), _rect.Top(), _rect.Right(), _rect.Bottom(), 0xddddaa, 2);
	_dbgDrawLine(_rect.Right(), _rect.Top(), _rect.Left(), _rect.Bottom(), 0xddddaa, 2);
	//for (int i = 0; i < 300; ++i)
	//{/// 後で見る
	//	_dbgDrawPixel(_rect.Left() + (i % _charSize.width), _rect.Right() + (i / _charSize.height), 0xffffff);
	//}
	

	DrawGraph(_pos.x, _pos.y, _animMap[_animKey][_animID].first, true);
}

const Vector2f & Object::pos() const
{
	return _pos;
}
