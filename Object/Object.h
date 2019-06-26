#pragma once

#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"

// ±ÆÒ°¼®İŠÇ——p‚Ì‰Â•Ï’·”z—ñ
using anim_vec = std::vector<std::pair<int, int>>;

/// ’†g‚ğC³‚·‚é‰Â”\«‚ ‚è
enum class ANIM
{
	NORMAL,		// ’Êí
	BLAST,		// ”š”j
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

	// ±ÆÒ°¼®İ‚Ì“o˜^
	bool SetAnim(ANIM key, anim_vec& data);
	void AnimUpdate();

	const Size _charSize = Size(30, 32);

private:
	// pair‚Ì—v‘f(first : ID, second : frame)
	std::map<ANIM, anim_vec> _animMap;
};

