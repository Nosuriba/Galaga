#pragma once

#include <vector>
#include <memory>
#include <map>
#include "../Vector2.h"
#include "../Input.h"

enum class ANIM
{
	ID,
	FRAME,
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
	virtual void Draw() = 0;
	virtual const Obj GetObjID() const = 0;
protected:
	Vector2f _pos;
	Vector2f _vel;
	Rect _rect;

	int invCnt = 0;
	int animCnt = 0;

	std::map<std::string, std::vector<int>> _animMap;

	const Size _charSize = Size(30, 32);
};

