#pragma once
#include "Vector2.h"
class Shot
{
public:
	Shot();
	Shot(const Vector2d& pos, const Vector2d& vel);
	~Shot();

	bool IsOutScreen() const;
	void Update();
	void Draw(const int& id);

private:
	Vector2d _pos;
	Vector2d _vel;
	Size _size;
	Rect _rect;

	bool _isShot;		// true : �ł��Ă���, false : �ł��Ă��Ȃ�

	const Size _shotSize;
};

