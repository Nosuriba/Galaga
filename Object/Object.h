#pragma once

#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"

// ｱﾆﾒｰｼｮﾝ管理用の可変長配列
using anim_vec = std::vector<std::pair<int, int>>;

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
	virtual void Update() = 0;
	virtual void Draw();
	virtual const Obj GetObjID() const = 0;

	/// Vector2に代わるかもしれない
	const Vector2f& pos() const;
protected:
	Vector2f _pos;
	Vector2f _vel;
	Rect _rect;

	// ｱﾆﾒｰｼｮﾝの登録
	bool SetAnim(ANIM key, anim_vec& data);

	/// 
	bool animKey(const ANIM key);
	const ANIM& animKey() const;
	
	const Size _charSize = Size(30, 32);
private:
	void AnimUpdate();
	
	// pairの要素(first : ID, second : frame)
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt = 0;
	int _animID = 0;

};

