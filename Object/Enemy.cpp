#include <DxLib.h>
#include <stdlib.h>
#include "Enemy.h"
#include "../Common/ImageMng.h"
#include "../DebugDisp.h"
#include "../DebugConOut.h"

Enemy::Enemy()
{
}

Enemy::Enemy(const EnemyState& state)
{
	_size = std::get<static_cast<int>(EN_STATE::SIZE)>(state);
	auto center = Vector2(std::get<static_cast<int>(EN_STATE::POS)>(state).x + _size.width / 2,
						  std::get<static_cast<int>(EN_STATE::POS)>(state).y + _size.height / 2);
	_pos	 = Vector2d(center.x, center.y);
	_vel	 = Vector2d();
	_rect	 = Rect(center, _size);
	_nextPos = _pos;
	_aimPos  = std::get<static_cast<int>(EN_STATE::AIM)>(state);
	_rad	 = 0.0;
	_moveDir = std::get<static_cast<int>(EN_STATE::MOVEINFO)>(state);
	_moveCnt = 0;


	Init(std::get<static_cast<int>(EN_STATE::TYPE)>(state),
		 std::get<static_cast<int>(EN_STATE::ID)>(state));

	SetEnemyNum(std::get<static_cast<int>(EN_STATE::NUM)>(state));
	animKey(ANIM::NORMAL);

	Curve();
}

Enemy::~Enemy()
{
	TRACE("敵の死亡\n");
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
	_sigCnt = -30;
	_sigRange = abs(_sigCnt);
	_updater = &Enemy::CurveUpdate;
}

void Enemy::Target()
{
	auto theta = atan2(_aimPos.y - _pos.y, _aimPos.x - _pos.x);
	auto cost = cos(theta);
	auto sint = sin(theta);

	//CalAngle(_pos, _aimPos);

	_vel = Vector2d(3 * cost, 3 * sint);
	_updater = &Enemy::TargetUpdate;
}

void Enemy::Rotation()
{
	auto theta = atan2(_pos.y - 40 - _pos.y, _pos.x - 40 - _pos.x);
	_rotAngle = theta * (360 / (2 * DX_PI));

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

void Enemy::CurveUpdate()
{
	if (_sigCnt >= _sigRange)
	{
		++_moveCnt;
		if (_moveCnt == _moveDir.size())
		{
			dbgPoint.clear();
			Rotation();
			// Target();
			return;
		}
		else
		{
			Curve();
			return;
		}
	}
	_vel.x = 1 * _moveDir[_moveCnt].x;
	_vel.y = Sigmoid(1.0, _sigCnt) * _moveDir[_moveCnt].y;
	_nextPos = _vel * Vector2d(1, 3);
	//CalAngle(_pos, _nextPos);
	_sigCnt += 0.3;
	if (abs((int)(_sigCnt)) % 10 == 0)
	{
		dbgPoint.push_back(_pos + _vel);
	}
	
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

	if (_vel == Vector2d(0,0))
	{
		/// 配置時のずれを補正している
		_pos = Vector2d(_aimPos.x, _aimPos.y);
		Move();
	}
}

void Enemy::RotationUpdate()
{
	static Vector2d center = _pos - Vector2d(-40, -40);
	_rotAngle = (_moveDir[0].x < 0 ? _rotAngle - 1 : _rotAngle + 1);

	auto cost = cos(_rotAngle * (DX_TWO_PI / 360));
	auto sint = sin(_rotAngle * (DX_TWO_PI / 360));
	_pos = center + Vector2d(40 * cost + -40 * sint,
							 40 * sint + 40 * cost);
}

void Enemy::MoveUpdate()
{
	/// 最初に登録した敵と同じｱﾆﾒｰｼｮﾝをするようにしたが、
	/// 処理の修正をした方がいいと思う
	_rad = 0;
	SetInvCnt(_leadCnt);
}

void Enemy::ShotUpdate()
{
}

void Enemy::CalRad(const Vector2d & sPos, const Vector2d & ePos)
{
	static int debug;
	auto r = atan2(ePos.y - sPos.y, ePos.x - sPos.x);

	/*if (r < 0)
	{
		r = r + (2 * DX_PI);
	}*/
	r = r * (360 / (2 * DX_PI));
	debug = r;
	_dbgDrawFormatString(0, 100, 0xffff00, "%d", debug);
	_rad = r * (DX_TWO_PI / 360);
}

double Enemy::Sigmoid(const double & gain, const double & x)
{
	auto debug = exp(-gain * x);
	return 1.0 / (1.0 + exp(-gain * x));
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
