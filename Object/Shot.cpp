#include <DxLib.h>
#include "Shot.h"
#include "../Game.h"
#include "../DebugDisp.h"
#include "../Common/ImageMng.h"

Shot::Shot()
{
}

Shot::Shot(const Vector2d& pos, const Vector2d& vel) : _shotSize(4, 4)
{
	_shot._pos = pos;
	_shot._vel = vel;
	_shot._size = _shotSize;
	auto center = Vector2(_shot._pos.x + (_shot._size.width / 2), _shot._pos.y + (_shot._size.height / 2));

	_shot._rect = Rect(center, _shot._size);
}

Shot::~Shot()
{
}

void Shot::Update()
{
	_shot._pos += _shot._vel;

	auto center = Vector2(_shot._pos.x + (_shot._size.width / 2), _shot._pos.y + (_size.height / 2));
	_shot._rect = Rect(center, _size);
}

void Shot::Draw(const int& id)
{
	DrawGraph(_shot._pos.x, _shot._pos.y, IMAGE_ID("shot")[id], true);

	_dbgDrawCircle(_shot._pos.x, _shot._pos.y, _shot._size.height / 2, 0xffffff, true);;

}

const Rect Shot::GetRect() const
{
	return _shot._rect;
}

bool Shot::IsOutScreen() const
{
	return (_shot._rect.Top() > LpGame.gameScreenSize.y ||
			_shot._rect.Bottom() < 0);
}
