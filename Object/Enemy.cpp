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

	_updater = &Enemy::MoveUpdate;
}

Enemy::~Enemy()
{
}

void Enemy::Rotation()
{
	_updater = &Enemy::RotationUpdate;
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

void Enemy::RotationUpdate()
{
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
	animCnt++;
	(this->*_updater)();
}

void Enemy::Draw()
{
	/// 仮でｱﾆﾒｰｼｮﾝをさせている(後でｱﾆﾒｰｼｮﾝの位置を設定している)
	int cnt = (animCnt / 60) % 2;
	DrawRectGraph(_pos.x, _pos.y, charSize.x * cnt, 0 , charSize.x, charSize.y,
				  ImageMng::GetInstance().GetID("image/enemy.png"), true, true);
}
