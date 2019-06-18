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
	Object::Draw(ImageMng::GetInstance().GetID("image/enemy.png"));
}
