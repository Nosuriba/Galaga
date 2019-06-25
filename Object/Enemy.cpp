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

	SET_IMAGE_ID("enemy", "image/enemy.png", Vector2(10, 3), Vector2(_charSize.width, _charSize.height));
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

void Enemy::Init()
{
}

void Enemy::Update(const Input& p)
{
	_invCnt++;
	(this->*_updater)();
}

void Enemy::Draw()
{
	DrawGraph(_pos.x, _pos.y, IMAGE_ID("enemy")[0], true);
}

const Obj Enemy::GetObjID() const
{
	return Obj::ENEMY;
}