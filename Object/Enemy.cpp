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
	sigCnt = -10;
	sigRange = 10;
	_updater = &Enemy::CurveUpdate;
}

void Enemy::Target()
{
	auto theta = atan2(_aimPos.y - _pos.y, _aimPos.x - _pos.x);
	auto cost = cos(theta);
	auto sint = sin(theta);

	//CalAngle(_pos, _aimPos);

	_vel = Vector2d(3 * cost, 3 * sint);

	if (_vel.x == 0)
	{
		_vel.x = (cost >= 0.0 ? 1 : -1);
	}
	if (_vel.y == 0)
	{
		_vel.y = (sint >= 0.0 ? 1 : -1);
	}

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

void Enemy::CurveUpdate()
{
	/// Yの値が一定値を以下、以上になった時
	/// この中の処理に入るような仕組みを作っていく？
	if (sigCnt >= sigRange)
	{
		++_moveCnt;
		if (_moveCnt == _moveDir.size())
		{
			Target();
			return;
		}
		else
		{
			Curve();
			return;
		}
		
	}
	_vel.x = 1 * _moveDir[_moveCnt].x;
	_vel.y = Sigmoid(1.0, sigCnt) * _moveDir[_moveCnt].y;
	_nextPos += _vel;
	//CalAngle(_pos, _nextPos);
	//sigCnt += 1.0; 
	sigCnt += 0.1;

	// auto vec = atan2f(_nextPos.y - _pos.y, _nextPos.x - _pos.x);
	//_dbgDrawLine(_pos.x, _pos.y, _pos.x + (50 * vec), _pos.y + (50 * vec), 0xffffff, 2.0);
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

void Enemy::CalAngle(const Vector2d & sPos, const Vector2d & ePos)
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
