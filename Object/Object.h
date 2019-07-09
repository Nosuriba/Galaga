#pragma once

#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"
#include "../DebugDisp.h"

// ±∆“∞ºÆ›ä«óùópÇÃâ¬ïœí∑îzóÒ
using anim_vec = std::vector<std::pair<int, int>>;

enum class ANIM
{
	NORMAL,		// í èÌ
	BLAST,		// îöîj
	EX,			// ì¡éÍ
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
	virtual bool GetAlive() const = 0;

	void SetKey(int key);

	/// Vector2Ç…ë„ÇÌÇÈÇ©Ç‡ÇµÇÍÇ»Ç¢
	const Vector2& pos() const;
protected:
	Vector2 _pos;
	Rect _rect;
	bool _isAlive = true;

	// ±∆“∞ºÆ›ÇÃìoò^
	bool SetAnim(ANIM key, anim_vec& data);

	bool animKey(const ANIM key);
	const ANIM& animKey() const;

	int _dbgKey;
	
	const Size _charSize = Size(30, 32);
private:
	void AnimUpdate();
	
	// pairÇÃóvëf(first : ID, second : frame)
	std::map<ANIM, anim_vec> _animMap;

	ANIM _animKey;
	int _invCnt = 0;
	int _animID = 0;

};

