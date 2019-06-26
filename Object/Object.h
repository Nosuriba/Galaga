#pragma once

#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"

// ｱﾆﾒｰｼｮﾝ管理用の可変長配列
using anim_vec = std::vector<std::pair<int, int>>;

/// 中身を修正する可能性あり
enum class ANIM
{
	NORMAL,		// 通常
	BLAST,		// 爆破
	EX,			// 特殊
	MAX
};

enum class Obj
{
	PLAYER,
	ENEMY,
	MAX
};
class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Update(const Input& p) = 0;
	virtual void Draw();
	virtual const Obj GetObjID() const = 0;
protected:
	Vector2f _pos;
	Vector2f _vel;
	Rect _rect;

	ANIM _animKey;
	int _invCnt  = 0;
	int _animID = 0;

	bool SetAnim(const ANIM key, const anim_vec&& data);
	void AnimUpdate();

	const Size _charSize = Size(30, 32);

private:
	// first : animOffset, second : frame
	std::map<ANIM, anim_vec> _animMap;
};

