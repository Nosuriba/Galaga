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

	animCnt = 0;
}


Shot::~Shot()
{
	DeleteGraph(ImageMng::GetInstance().GetID("image/shot.png"));
}

void Shot::Update()
{
	invCnt++;
	_pos += _vel;
}

void Shot::Draw()
{
	animCnt = (invCnt / 5) % 7;
	DrawRectGraph(_pos.x, _pos.y, animCnt * _shotSize.width, 0, _shotSize.width, _shotSize.height,
				  LpImageMng.GetID("image/shot.png"), true, true);
}

bool Shot::CheckDestroy(const Rect & r)
{
	return false;
}
