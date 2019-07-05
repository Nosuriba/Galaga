#include <DxLib.h>
#include "Shot.h"
#include "../Common/ImageMng.h"

Shot::Shot()
{
}

Shot::Shot(const Vector2 & pos)
{
	_pos = pos;

	auto center = Vector2(_pos.x + (_shotSize.width / 2), _pos.y + (_shotSize.height / 2));
	auto size = _shotSize;
	_rect = Rect(center, size);

	SET_IMAGE_ID("shot", "image/shot.png");
}

Shot::~Shot()
{
}

void Shot::Update()
{
	_pos += _vel;

	auto center = Vector2(_pos.x + (_shotSize.width / 2), _pos.y + (_shotSize.height / 2));
	auto size	= _shotSize;
	_rect = Rect(center, size);

}

void Shot::Draw()
{
	DrawGraph(_pos.x, _pos.y, IMAGE_ID("shot")[0], true);

}
