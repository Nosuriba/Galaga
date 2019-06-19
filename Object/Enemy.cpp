#include <DxLib.h>
#include "Enemy.h"
#include "../Common/ImageMng.h"

Enemy::Enemy()
{
}

Enemy::Enemy(const Vector2f& pos, const Vector2f& vel)
{
	_pos = pos;
	_vel = vel;
}

Enemy::~Enemy()
{
}

void Enemy::Update(const Input& p)
{
}

void Enemy::Draw()
{
	//DrawRectGraph(_pos.x, _pos.y, 0, 0, charSize.x, charSize.y,
	//			  ImageMng::GetInstance().GetID("image/enemy.png"), true, true);

	DrawGraph(_pos.x, _pos.y, ImageMng::GetInstance().GetID("image/enemy.png", Vector2(10, 3), Vector2(charSize.x, charSize.y))[1], true);
}
