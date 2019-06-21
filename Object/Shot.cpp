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
	_pos += _vel;
}

void Shot::Draw()
{
	animCnt = (invCnt / 10) % 8;
	DrawRectGraph(_pos.x, _pos.y, animCnt * shotSize.x, 0, shotSize.x, shotSize.y,
						  ImageMng::GetInstance().GetID("image/shot.png"), true, true);
}

bool Shot::CheckDestroy(const Rect & r)
{
	return false;
}
