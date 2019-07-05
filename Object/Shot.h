#pragma once
#include "Vector2.h"
class Shot
{
public:
	Shot();
	Shot(const Vector2& pos);
	~Shot();
	void Update();
	void Draw();
private:
	Vector2 _pos;
	Vector2 _vel;
	Rect _rect;

	const Size _shotSize = Size(20,20);
};

