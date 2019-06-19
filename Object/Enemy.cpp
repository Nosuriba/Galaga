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

	_updater = &Enemy::IdleUpdate;
}

Enemy::~Enemy()
{
}

void Enemy::Idle()
{
	_updater = &Enemy::IdleUpdate;
}

void Enemy::Move()
{
	_updater = &Enemy::MoveUpdate;
}

void Enemy::Shot()
{
	_updater = &Enemy::ShotUpdate;
}

void Enemy::Die()
{
	_updater = &Enemy::DieUpdate;
}

void Enemy::IdleUpdate()
{
}

void Enemy::MoveUpdate()
{
}

void Enemy::ShotUpdate()
{
}

void Enemy::DieUpdate()
{
}

void Enemy::Update(const Input& p)
{
	(this->*_updater)();
}

void Enemy::Draw()
{
	/// こっちが本命
	//DrawRectGraph(_pos.x, _pos.y, 0, 0, charSize.x, charSize.y,
	//			  ImageMng::GetInstance().GetID("image/enemy.png"), true, true);

	int img = ImageMng::GetInstance().GetID("image/enemy.png", Vector2(10, 3), Vector2(charSize.x, charSize.y))[1];
	DrawGraph(_pos.x, _pos.y, img, true);
}
