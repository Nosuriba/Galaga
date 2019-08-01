#include <cmath>
#include "Collision.h"

Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::CheckCol(const Rect & rcA, const Rect & rcB) const 
{
	return abs(rcA.center.x - rcB.center.x) < (rcA.Width()  + rcB.Width()) / 2 &&
		   abs(rcA.center.y - rcB.center.y) < (rcA.Height() + rcB.Height()) / 2;
}
