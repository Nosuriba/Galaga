#include <DxLib.h>
#include "Enemy.h"
#include "../Common/ImageMng.h"
#include "../DebugDisp.h"

Enemy::Enemy()
{
}

Enemy::Enemy(const Vector2& pos)
{
	_pos = pos;

	auto center = Vector2(_pos.x + _charSize.width / 2, _pos.y + _charSize.height / 2);
	auto size = _charSize;
	_rect = Rect(center, size);

	SET_IMAGE_ID("enemy", "image/enemy.png", Vector2(10, 3), Vector2(_charSize.width, _charSize.height));
	Init();
	animKey(ANIM::NORMAL);
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
	anim_vec data;

	data.emplace_back(IMAGE_ID("enemy")[0], 30);
	data.emplace_back(IMAGE_ID("enemy")[1], 30);
	SetAnim(ANIM::NORMAL, data);
}

void Enemy::Update()
{
	(this->*_updater)();

	auto center = Vector2(_pos.x + _charSize.width / 2, _pos.y + _charSize.height / 2);
	auto size = _charSize;
	_rect = Rect(center, size);

	_isAlive = !(CheckHitKey(_dbgKey));

	/// 仮でﾃﾞﾊﾞｯｸﾞ用の描画をしている
	_dbgDrawBox(_rect.Left(), _rect.Top(), _rect.Right(), _rect.Bottom(), 0xff0000, true);
}

void Enemy::Draw()
{
}

const Obj Enemy::GetObjID() const
{
	return Obj::ENEMY;
}

bool Enemy::GetAlive() const
{
	return _isAlive;
}