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

	void LeadUpdate();
	int GetEnemyNum() const;


	bool GetDeath() const;

	const Vector2d& pos() const;
protected:
	// ±ÆÒ°¼®İ‚Ì“o˜^
	bool SetAnim(ANIM key, anim_vec& data);
	void SetEnemyNum(const int& num);

	bool DestryCheck();

	void SetInvCnt(const int& leadCnt);
	void ResetInvCnt();

	// key‚Ìó‘Ô‚ğ•ÏX‚µ‚Ä‚¢‚é
	bool animKey(const ANIM key);
	// key‚Ìî•ñ‚ğæ“¾‚µ‚Ä‚¢‚é
	const ANIM& animKey() const;

	Vector2d _pos;
	Vector2d _vel;
	Size _size;
	Rect _rect;
	double _angle;
	bool _isAlive = true;		// true : ¶‘¶, false : €–S
	bool _isDeath = false;		// true : “G‚Ìíœ, false : €–Sˆ—’†

	static int _leadCnt;
private:
	void AnimUpdate();
	
	// pair‚Ì—v‘f(first : ID, second : frame)
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt = 0;
	int _animID = 0;

	int _enNum;

};

