#include <DxLib.h>
#include "Shot.h"
#include "../Common/ImageMng.h"

Shot::Shot()
{
	_pos = Vector2f();
	_vel = Vector2f();
}

Shot::Shot(const Vector2f & pos, const Vector2f & vel)
{
	_pos = pos;
	_vel = vel;

	auto center = Vector2(_pos.x + (_shotSize.width / 2), _pos.y + (_shotSize.height / 2));
	auto size = _shotSize;
	_rect = Rect(center, size);

	animCnt = 0;
}


Shot::~Shot()
{
}

void Shot::Update()
{
	invCnt++;
	_pos += _vel;

	auto center = Vector2(_pos.x + (_shotSize.width / 2), _pos.y + (_shotSize.height / 2));
	auto size = _shotSize;
	_rect = Rect(center, size);

}

void Shot::Draw()
{
	animCnt = (invCnt / 5) % 7;
	DrawRectGraph(_pos.x, _pos.y, animCnt * _shotSize.width, 0, _shotSize.width, _shotSize.height,
				  IMAGE_ID("image/shot.png")[0], true, true);
}
