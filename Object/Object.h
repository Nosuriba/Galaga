#pragma once

#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"
#include "../DebugDisp.h"

// ±ÆÒ°¼®İŠÇ——p‚Ì‰Â•Ï’·”z—ñ
using anim_vec = std::vector<std::pair<int, int>>;

enum class ANIM
{
	NORMAL,		// ’Êí
	DEATH,		// €–S
	EX,			// “Áê
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

	bool GetDeath() const;

	const Vector2& pos() const;
protected:
	Vector2 _pos;
	Rect _rect;
	bool _isAlive = true;		// true : ¶‘¶, false : €–S
	bool _isDeath = false;		// true : “G‚Ìíœ, false : €–Sˆ—’†

	// ±ÆÒ°¼®İ‚Ì“o˜^
	bool SetAnim(ANIM key, anim_vec& data);

	bool DestryCheck();

	void ResetInvCnt();

	// key‚Ìó‘Ô‚ğ•ÏX‚µ‚Ä‚¢‚é
	bool animKey(const ANIM key);
	// key‚Ìî•ñ‚ğæ“¾‚µ‚Ä‚¢‚é
	const ANIM& animKey() const;
	const Size _charSize;
private:
	void AnimUpdate();
	
	// pair‚Ì—v‘f(first : ID, second : frame)
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt = 0;
	int _animID = 0;

};

