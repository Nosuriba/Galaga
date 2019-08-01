#pragma once

#include "Vector2.h"

class Collision
{
public:
	Collision();
	~Collision();
	bool IsCollision(const Rect& rcA, const Rect& rcB) const;
};

