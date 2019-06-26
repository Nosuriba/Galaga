#pragma once
#include "Vector2.h"
class Shot
{
public:
	Shot();
	Shot(const Vector2f& pos, const Vector2f& vel);
	~Shot();
	void Update();
	void Draw();
private:
	Vector2f _pos;
	Vector2f _vel;
	Rect _rect;

	const Size _shotSize = Size(20,20);
};

