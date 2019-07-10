﻿#include <DxLib.h>
#include <stdlib.h>
#include "Enemy.h"
#include "../Common/ImageMng.h"
#include "../DebugDisp.h"
#include "../DebugConOut.h"

Enemy::Enemy()
{
}

Enemy::Enemy(const Vector2& pos)
{
	_pos = pos;

	auto center = Vector2(_pos.x + _charSize.width / 2, _pos.y + _charSize.height / 2);
	auto size = _charSize;
	_rect = Rect(center, size);
	Init();
	animKey(ANIM::NORMAL);
	_updater = &Enemy::MoveUpdate;
}

Enemy::~Enemy()
{
	TRACE("敵の死亡\n");
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

	data.emplace_back(IMAGE_ID("en_blast")[0], 10);
 	for (int i = 1; i < 5; ++i)
	{
		data.emplace_back(IMAGE_ID("en_blast")[i], 5);
	}
	/// ｱﾆﾒｰｼｮﾝの終了位置を設定している
	data.emplace_back(-1, 0);

	SetAnim(ANIM::BLAST, data);
}

void Enemy::Update()
{
	(this->*_updater)();

	if (!_isAlive)
	{
		return;
	}

	if (rand() % 1200 == 0)
	{
		animKey(ANIM::BLAST);
		_isAlive = false;
		ResetInvCnt();
	}

	auto center = Vector2(_pos.x + _charSize.width / 2, _pos.y + _charSize.height / 2);
	auto size = _charSize;
	_rect = Rect(center, size);

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