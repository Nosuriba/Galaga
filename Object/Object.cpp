#include "Object.h"

Object::Object()
{
}

Object::~Object()
{
}

void Object::Draw(int id)
{
	DxLib::DrawRectGraph(_pos.x, _pos.y, 0, 0, charSize.x, charSize.y, id, true, true);
}
