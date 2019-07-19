#include <DxLib.h>
#include <stdlib.h>
#include "Enemy.h"
#include "../Common/ImageMng.h"
#include "../DebugDisp.h"
#include "../DebugConOut.h"

Enemy::Enemy() : _sigMax(0), _distance(0)
{
}

Enemy::Enemy(const EnemyState& state) : _sigMax(40) , _distance(30)
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

	/// 曲がる情報の設定
	_curveInfo[0] = Vector2(1, 1);
	_curveInfo[1] = Vector2(1, -1);
	_curveInfo[2] = Vector2(-1, -1);
	_curveInfo[3] = Vector2(-1, 1);

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
	_sigCnt = -_sigMax;
	_sigRange = abs(_sigMax);
	_updater = &Enemy::CurveUpdate;
}

void Enemy::Target()
{
	auto theta = atan2(_aimPos.y - _pos.y, _aimPos.x - _pos.x);
	auto cost = cos(theta);
	auto sint = sin(theta);

	CalRad(_pos, _aimPos);

	_vel = Vector2d(3 * cost, 3 * sint);
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
	auto sigmoid = [](const double& gain, const double& x)
	{
		auto debug = exp(-gain * x);
		return 1.0 / (1.0 + exp(-gain * x));
	};

	auto dir = _moveDir[_moveDir.size() - 1];

	/// ｶｳﾝﾄが一定値を超えた時の状態遷移
	if (_sigCnt >= _sigRange)
	{
		_moveDir.pop_back();
		if (_moveDir.size() <= 0)
		{
			dbgPoint.clear();
			Rotation();
			return;
		}
		else
		{
			Curve();
			return;
		}
	}
	_vel.x = 2 * _curveInfo[dir].x;
	if (_sigCnt <= 0)
	{
		_vel.y += 2 * sigmoid(1.0, _sigCnt / (_sigMax / 10)) * _curveInfo[dir].y;
	}
	else
	{
		_vel.y *= 0.85;
	}
	++_sigCnt;
	//CalRad(_pos, _nextPos);
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
	auto cost = cos(_rotAngle * (DX_PI / 180));
	auto sint = sin(_rotAngle * (DX_PI / 180));
	_pos = _rotCenter + Vector2d(_rotDistance * cost,
								 _rotDistance * sint);
	_rotAngle = (_curveInfo[0].x < 0 ? _rotAngle - 4 : _rotAngle + 4);

}

void Enemy::MoveUpdate()
{
}

void Enemy::ShotUpdate()
{
}

void Enemy::CalRad(const Vector2d & sPos, const Vector2d & ePos)
{
	_rad = atan2(ePos.y - sPos.y, ePos.x - sPos.x);

	/*r = r * (180 / DX_PI);

	_dbgDrawFormatString(0, 100, 0xffff00, "%d", r);

	_rad = r * (DX_PI / 180);*/
}
void Enemy::MakeRotaInfo(const double & distance)
{
	_rotDistance = distance;
	_rotCenter = _pos + Vector2d(_distance * _curveInfo[0].x,
								 _distance * - _curveInfo[0].y);

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
