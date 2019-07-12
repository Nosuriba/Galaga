#include <DxLib.h>
#include <stdlib.h>
#include "Enemy.h"
#include "../Common/ImageMng.h"
#include "../DebugDisp.h"
#include "../DebugConOut.h"

Enemy::Enemy()
{
}

Enemy::Enemy(EnemyState state)
{
	_size = std::get<static_cast<int>(EN_STATE::SIZE)>(state);
	auto center = Vector2(std::get<static_cast<int>(EN_STATE::POS)>(state).x + _size.width / 2,
						  std::get<static_cast<int>(EN_STATE::POS)>(state).y + _size.height / 2);
	_pos = center;
	_rect = Rect(center, _size);
	_aimPos = std::get<static_cast<int>(EN_STATE::AIM)>(state);

	Init(std::get<static_cast<int>(EN_STATE::TYPE)>(state));
	animKey(ANIM::NORMAL);

	/// 三角関数を使った移動方向の計算
	auto theta = atan2(_aimPos.y - _pos.y, _aimPos.x - _pos.x);
	auto cost = cos(theta);
	auto sint = sin(theta);

	_vel = Vector2(3 * cost, 3 * sint);

	///	速度がなかった時に最低速度を渡すようにしている
	if (_vel.y == 0)
	{
		_vel.y = (sint >= 0.0 ? 1 : -1);
	}

	_updater = &Enemy::TargetUpdate;
}

Enemy::~Enemy()
{
	TRACE("敵の死亡\n");
}

void Enemy::Idle()
{
	_updater = &Enemy::IdleUpdate;
}

void Enemy::Target()
{
	_updater = &Enemy::TargetUpdate;
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

void Enemy::IdleUpdate()
{
}

void Enemy::TargetUpdate()
{
	if (_vel.x >= 0)
	{
		_vel.x = (_pos.x >= _aimPos.x ? 0 : _vel.x);
	}
	else
	{
		_vel.x = (_pos.x <= _aimPos.x ? 0 : _vel.x);
	}

	if (_vel.y >= 0)
	{
		_vel.y = (_pos.y >= _aimPos.y ? 0 : _vel.y);
	}
	else
	{
		_vel.y = (_pos.y <= _aimPos.y ? 0 : _vel.y);
	}

	if (_vel == Vector2(0, 0))
	{
		Idle();
	}
}

void Enemy::RotationUpdate()
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

void Enemy::Init(EN_TYPE type)
{
	anim_vec data;
	auto id = static_cast<int>(type) * 2;

	data.emplace_back(IMAGE_ID("enemy")[0 + id], 30);
	data.emplace_back(IMAGE_ID("enemy")[1 + id], 30);
	SetAnim(ANIM::NORMAL, data);

	data.emplace_back(IMAGE_ID("en_blast")[0], 15);
 	for (int i = 1; i < 5; ++i)
	{
		data.emplace_back(IMAGE_ID("en_blast")[i], 5);
	}
	/// ｱﾆﾒｰｼｮﾝの終了位置を設定している
	data.emplace_back(-1, 10);

	SetAnim(ANIM::DEATH, data);
}

void Enemy::Update()
{
	(this->*_updater)();

	if (DestryCheck())
	{
		return;
	}

	/// 仮の死亡処理
	if (rand() % 1200 == 0)
	{
		animKey(ANIM::DEATH);
		_isAlive = false;
		ResetInvCnt();
	}

	_pos += _vel;

	auto center = Vector2(_pos.x + _size.width / 2, _pos.y + _size.height / 2);
	_rect = Rect(center, _size);

	/// 仮でﾃﾞﾊﾞｯｸﾞ用の描画をしている
	_dbgDrawBox(_rect.Left()  - _size.width / 2, _rect.Top()	- _size.height / 2,
				_rect.Right() - _size.width / 2, _rect.Bottom() - _size.height / 2, 0xff0000, true);
}

void Enemy::Draw()
{
}

const Obj Enemy::GetObjID() const
{
	return Obj::ENEMY;
}
