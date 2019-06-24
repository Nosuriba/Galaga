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
	invCnt++;
	(this->*_updater)();
}

void Enemy::Draw()
{
	/// 仮でｱﾆﾒｰｼｮﾝをさせている(後でｱﾆﾒｰｼｮﾝの位置を設定している)
	animCnt = (invCnt / 10) % 2;
	DrawRectGraph(_pos.x, _pos.y, _charSize.width * animCnt, 0 , _charSize.width, _charSize.height,
				  LpImageMng.GetID("image/enemy.png"), true, true);
}

const Obj Enemy::GetObjID() const
{
	return Obj::ENEMY;
}
