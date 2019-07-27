﻿#include <DxLib.h>
#include <stdlib.h>
#include "Enemy.h"
#include "../DebugDisp.h"
#include "../DebugConOut.h"

Enemy::Enemy() : _sigMax(10), _distance(40)
{
}

Enemy::~Enemy()
{
}

void Enemy::Wait()
{
	_updater = &Enemy::WaitUpdate;
}

void Enemy::Sigmoid()
{
	/// ｼｸﾞﾓｲﾄﾞを使った移動範囲の設定
	_sigCnt	  = -_sigMax;
	_sigBegin = _pos;
	_sigRange = _sigEnd - _sigBegin;
	_updater  = &Enemy::SigmoidUpdate;
}

void Enemy::Target()
{
	auto theta = atan2(_aimPos.y - _pos.y, _aimPos.x - _pos.x);
	auto cost = cos(theta);
	auto sint = sin(theta);

	_vel	 = Vector2d(3 * cost, 3 * sint);
	_updater = &Enemy::TargetUpdate;
}

void Enemy::Rotation()
{
	MakeRotaInfo();
	_updater = &Enemy::RotationUpdate;
}

void Enemy::Move()
{
	_tblFlag = true;
	_rad = 0;
	/// 先頭のｱﾆﾒｰｼｮﾝｶｳﾝﾄを渡している
	SetInvCnt(_leadCnt);
	_updater = &Enemy::MoveUpdate;
}

void Enemy::WaitUpdate()
{
	if (_waitCnt <= 0)
	{
		Sigmoid();
	}
	--_waitCnt;
}

void Enemy::SigmoidUpdate()
{
	if (_sigCnt >= _sigMax)
	{
		_rotDir.x = (_sigRange.x >= 0 ? 1 : -1);
		_rotDir.y = (_sigRange.y >= 0 ? -1 : 1);
		Rotation();
		return;
	}

	auto sigmoid = [](const double& x){ return 1.0 / (1.0 + exp(-1.0 * x));};
	double X = (_sigCnt + _sigMax) / (_sigMax * 2);
	double Y = sigmoid(_sigCnt);

	/// 敵の移動(移動する幅のXとYをグラフに変換して移動させている)
	_pos.x = X * _sigRange.x + _sigBegin.x;
	_pos.y = Y * _sigRange.y + _sigBegin.y;
	
	_sigCnt += 0.3;
	CalRad(_pos, _sigEnd, 90);
}
 
void Enemy::TargetUpdate()
{
	/// 目標地点までのﾗｼﾞｱﾝの計算
	auto theta = atan2(_aimPos.y - _pos.y, _aimPos.x + _moveTblInfo.first - _pos.x);
	auto cost = cos(theta);
	auto sint = sin(theta);

	/// 目標地点に着いたとき、速度を0にする処理
	if (_vel.x >= 0)
	{
		_vel.x = (_pos.x >= _aimPos.x + _moveTblInfo.first ? 0 : _vel.x);
	}
	else
	{
		_vel.x = (_pos.x <= _aimPos.x + _moveTblInfo.first ? 0 : _vel.x);
	}

	if (_vel.y >= 0)
	{
		_vel.y = (_pos.y >= _aimPos.y ? 0 : _vel.y);
	}
	else
	{
		_vel.y = (_pos.y <= _aimPos.y ? 0 : _vel.y);
	}

	CalRad(_pos, _aimPos, 90);

	/// 目標地点までの速度計算
	_vel.x = (_vel.x == 0 ? 0 : 3 * cost);
	_vel.y = (_vel.y == 0 ? 0 : 3 * sint);
	
	if (_vel == Vector2d(0,0))
	{
		/// 配置時のずれを補正している
		_pos = Vector2d(_aimPos.x + _moveTblInfo.first, _aimPos.y);
		Move();
	}
}

void Enemy::RotationUpdate()
{
	auto cost = cos(_angle * (DX_PI / 180));
	auto sint = sin(_angle * (DX_PI / 180));
	auto ePos = _rotCenter - Vector2d(_distance * cost,
									  _distance * sint);
	 CalRad(_pos, ePos, 90);
	_pos = ePos;

	_angle += 4 * _rotDir.x * _rotDir.y;
	_rotAngle += 4;

	if (_rotAngle >= 360)
	{
		Target();
	}
}

void Enemy::MoveUpdate()
{
	_pos.x += _moveTblInfo.second;
}

void Enemy::CalRad(const Vector2d & sPos, const Vector2d & ePos, const double& angle)
{
	_rad = atan2(ePos.y - sPos.y, ePos.x - sPos.x);

	_rad += angle * (DX_PI / 180);

	auto debug = _rad * (180 / DX_PI);
}
void Enemy::MakeRotaInfo()
{
	_rotCenter = _pos + Vector2d(_distance * _rotDir.x, _distance / 2 * -_rotDir.y);

	auto theta  = atan2(_rotCenter.y - _pos.y, _rotCenter.x - _pos.x);
	_angle		= theta * (180 / DX_PI);
	_rotAngle	= 0;
}

void Enemy::Update()
{
	if (DestryCheck())
	{
		return;
	}
	(this->*_updater)();
	_pos += _vel;

	auto center = Vector2(_pos.x + _size.width / 2, _pos.y + _size.height / 2);
	_rect = Rect(center, _size);

	/// debug用で敵を削除している
	static char now;
	static char old;
	old = now;
	now = CheckHitKey(KEY_INPUT_C);

	if (now && !old)
	{
		animKey(ANIM::DEATH);
		_isAlive = false;
		ResetInvCnt();
	}

	if (_updater == &Enemy::RotationUpdate)
	{
		_dbgDrawCircle(_rotCenter.x, _rotCenter.y, 5, 0x00ff00, true);
	}
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
