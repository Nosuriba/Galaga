#include "Vector2.h"

/// ‹éŒ`‚Ìİ’è
const int Rect::Left() const
{
	return center.x - (size.x / 2);
}

const int Rect::Right() const
{
	return center.x + (size.x / 2);
}

const int Rect::Top() const
{
	return center.y - (size.y / 2);
}

const int Rect::Bottom() const
{
	return center.y + (size.y / 2);
}

const int Rect::Width() const
{
	return size.x;
}

const int Rect::Height() const
{
	return size.y;
}
