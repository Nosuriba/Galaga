#pragma once

#include "Vector2.h"

class Collision
{
public:
	Collision();
	~Collision();
	bool CheckCol(const Rect& rcA, const Rect& rcB) const;
};

