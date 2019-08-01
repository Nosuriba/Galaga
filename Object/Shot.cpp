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
	_pos = pos;
	_vel = vel;
	_size = _shotSize;
	auto center = Vector2(_pos.x + (_size.width / 2), _pos.y + (_size.height / 2));

	_rect = Rect(center, _size);

	_isShot = false;
}

Shot::~Shot()
{
}

void Shot::Update()
{
	if (IsOutScreen())
	{
		_isShot = false;
	}
	_pos += _vel;

	auto center = Vector2(_pos.x + (_size.width / 2), _pos.y + (_size.height / 2));
	_rect = Rect(center, _size);
}

void Shot::Draw(const int& id)
{
	DrawGraph(_pos.x, _pos.y, IMAGE_ID("shot")[id], true);

	_dbgDrawCircle(_pos.x, _pos.y, _size.height / 2, 0xffffff, true);;

}

bool Shot::IsOutScreen() const
{
	return (_rect.Top() > LpGame.gameScreenSize.y ||
			_rect.Bottom() < 0);
}
