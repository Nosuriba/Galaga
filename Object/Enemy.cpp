#include <DxLib.h>
#include <stdlib.h>
#include "Enemy.h"
#include "../DebugDisp.h"
#include "../DebugConOut.h"

Enemy::Enemy() : _sigMax(10), _distance(60)
{
}

Enemy::~Enemy()
{
}

void Enemy::Init(EN_TYPE type, EN_ID id)
{
	anim_vec data;
	auto enType = static_cast<int>(type) * 2;
	auto enID = static_cast<int>(id) * 10;

	data.emplace_back(IMAGE_ID("enemy")[0 + enType + enID], 30);
	data.emplace_back(IMAGE_ID("enemy")[1 + enType + enID], 60);
	SetAnim(ANIM::NORMAL, data);

	data.emplace_back(IMAGE_ID("en_blast")[0], 15);
	for (int i = 1; i < 5; ++i)
	{
		data.emplace_back(IMAGE_ID("en_blast")[i], 15 + (5 * i));
	}
	/// ｱﾆﾒｰｼｮﾝの終了位置を設定している
	data.emplace_back(-1, 60);

	SetAnim(ANIM::DEATH, data);
}

void Enemy::Sigmoid()
{
	/// ｼｸﾞﾓｲﾄﾞを使った移動範囲の設定
	_sigCnt	 = -_sigMax;
	_sPos	 = _pos;
	_updater = &Enemy::SigmoidUpdate;
}

void Enemy::Target()
{
	auto theta = atan2(_aimPos.y - _pos.y, _aimPos.x - _pos.x);
	auto cost = cos(theta);
	auto sint = sin(theta);

	CalRad(_pos, _aimPos, 0);

	_vel	 = Vector2d(3 * cost, 3 * sint);
	_updater = &Enemy::TargetUpdate;
}

void Enemy::Rotation()
{
	MakeRotaInfo(_distance);
	_updater = &Enemy::RotationUpdate;
}

void Enemy::Move()
{
	_rad = 0;
	/// 先頭のｱﾆﾒｰｼｮﾝｶｳﾝﾄを渡している
	SetInvCnt(_leadCnt);
	_updater = &Enemy::MoveUpdate;
}

void Enemy::Shot()
{
	_updater = &Enemy::ShotUpdate;
}

void Enemy::SigmoidUpdate()
{
	auto sigmoid = [](const double& x){ return 1.0 / (1.0 + exp(-1.0 * x));};

	auto range = Vector2d(_ePos.x - _sPos.x, _ePos.y - _sPos.y);
	double X = (_sigCnt + _sigMax) / (_sigMax * 2);
	double Y = sigmoid(_sigCnt);
	/// 角度計算
	auto ePos = Vector2d(X * range.x + _sPos.x, Y * range.y * _sPos.y);
	CalRad(_pos, ePos, 90);

	_pos.y = Y * range.y + _sPos.y;
	_pos.x = X * range.x + _sPos.x;

	_sigCnt += 0.2;
	CalRad(_pos, _ePos, 90);
	_dbgDrawCircle(_ePos.x, _ePos.y, 2, 0xffffff, true);

	if (_sigCnt >= _sigMax)
	{
		_rotDir.x = (range.x >= 0 ? 1: -1);
		_rotDir.y = (range.y >= 0 ? -1 : 1);
		Rotation();
	}
}
 
void Enemy::TargetUpdate()
{
	CalRad(_pos, _aimPos, 90);
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

	if (_vel == Vector2d(0,0))
	{
		/// 配置時のずれを補正している
		_pos = Vector2d(_aimPos.x, _aimPos.y);
		Move();
	}
}

void Enemy::RotationUpdate()
{
	auto cost = cos(_rotAngle * (DX_PI / 180));
	auto sint = sin(_rotAngle * (DX_PI / 180));
	auto ePos = _rotCenter - Vector2d(_rotDistance * cost,
									  _rotDistance * sint);
	 CalRad(_pos, ePos, 90);
	_pos = ePos;
	_rotAngle += 4 * _rotDir.x * _rotDir.y;

	_rotDistance -= 0.1;

	if (_rotDistance <= _distance / 2)
	{
		Target();
	}
}

void Enemy::MoveUpdate()
{
}

void Enemy::ShotUpdate()
{
}

void Enemy::CalRad(const Vector2d & sPos, const Vector2d & ePos, const double& angle)
{
	_rad = atan2(ePos.y - sPos.y, ePos.x - sPos.x);

	_rad += angle * (DX_PI / 180);

	auto debug = _rad * (180 / DX_PI);
}
void Enemy::MakeRotaInfo(const double & distance)
{
	_rotDistance = distance;
	_rotCenter = _pos + Vector2d(0, _distance * _rotDir.y);

	auto theta = atan2(_rotCenter.y - _pos.y, _rotCenter.x - _pos.x);
	_rotAngle  = theta * (180 / DX_PI);
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
