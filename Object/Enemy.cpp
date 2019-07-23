#include <DxLib.h>
#include <stdlib.h>
#include "Enemy.h"
#include "../DebugDisp.h"
#include "../DebugConOut.h"

Enemy::Enemy() : _sigMax(10), _distance(30)
{
}

Enemy::Enemy(const EnemyState& state) : _sigMax(10) , _distance(30)
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

void Enemy::Curve()
{
	/// ｼｸﾞﾓｲﾄﾞを使った移動範囲の設定
	_sigCnt	  = -_sigMax;
	_sPos = _pos;
	_updater = &Enemy::CurveUpdate;
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
	/// 最初に登録した敵と同じｱﾆﾒｰｼｮﾝをするようにしたが、
	/// 処理の修正をした方がいいと思う
	_rad = 0;
	SetInvCnt(_leadCnt);
	_updater = &Enemy::MoveUpdate;
}

void Enemy::Shot()
{
	_updater = &Enemy::ShotUpdate;
}

void Enemy::CurveUpdate()
{
	auto sigmoid = [](const double& x){ return 1.0 / (1.0 + exp(-1.0 * x));};

	if (_sigCnt >= _sigMax)
	{
		Rotation();
	}
	auto range = Vector2d(_nextPos.x - _sPos.x, _nextPos.y - _sPos.y);
	double X = (_sigCnt + _sigMax) / (_sigMax * 2);
	double Y = sigmoid(_sigCnt);
	/// 角度計算
	auto ePos = Vector2d(X * range.x + _sPos.x, Y * range.y * _sPos.y);
	CalRad(_pos, ePos, 90);

	_pos.y = Y * range.y + _sPos.y;
	_pos.x = X * range.x + _sPos.x;

	_sigCnt += 0.3;
	CalRad(_pos, _nextPos, 90);
	_dbgDrawCircle(_nextPos.x, _nextPos.y, 2, 0xffffff, true);
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
	auto ePos = _rotCenter + Vector2d(_rotDistance * cost,
									  _rotDistance * sint);
	 CalRad(_pos, ePos, 90);
	_pos = ePos;
	_rotAngle = (_rotDir.y < 0 ? _rotAngle - 4 : _rotAngle + 4);

	_rotDistance -= 0.1;

	if (_rotDistance <= 10)
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
	_rotCenter = _pos + Vector2d(_distance *  _rotDir.x,
								 _distance * -_rotDir.y);

	auto theta = atan2(_pos.y - _rotCenter.y, _pos.x - _rotCenter.x);
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

	_dbgDrawCircle(_rotCenter.x, _rotCenter.y, 5, 0x00ff00, true);
	/// 仮でﾃﾞﾊﾞｯｸﾞ用の描画をしている
	for (auto point : dbgPoint)
	{
		_dbgDrawCircle (point.x, point.y,3, 0xffffff);
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
