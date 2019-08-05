#include <DxLib.h>
#include <stdlib.h>
#include "Enemy.h"
#include "../DebugDisp.h"
#include "../DebugConOut.h"

int Enemy::_actionCnt = 0;

Enemy::Enemy() : _sigMax(10), _distance(30)
{
	/// 初期の移動ﾘｽﾄを登録している
	_moveList.emplace_back(&Enemy::Sigmoid);
	_moveList.emplace_back(&Enemy::Rotation);
	_moveList.emplace_back(&Enemy::Target);

	_sigAdd = 0.3;
	_spMag = 0;
	_spVel = 0;
	_spDistance = Vector2d();
	_moveTblInfo.first = 1;
	_isAction = false;

	Wait();
}

Enemy::~Enemy()
{
	_moveTblInfo = { 0,0 };
	_actionCnt -= (_isAction ? 1 : 0);
}

void Enemy::SetSigAdd(const double & sigAdd)
{
	_sigAdd = sigAdd;
}

bool Enemy::ChangeMove()
{
	if (_moveList.size() > 0)
	{
		_updater = _moveList.front();
		_moveList.pop_front();
		return true;
	}
	return false;
}

void Enemy::CalRad(const Vector2d & sPos, const Vector2d & ePos, const double& angle)
{
	_rad = atan2(ePos.y - sPos.y, ePos.x - sPos.x);
	_rad += angle * (DX_PI / 180);

	auto debug = _rad * (180 / DX_PI);
}
void Enemy::MakeRotaInfo()
{
	_rotCenter = _pos + Vector2d(0, _distance * _rotDir.y);

	auto theta = atan2(_pos.y - _rotCenter.y, _pos.x - _rotCenter.x);
	_angle	= theta * (180 / DX_PI);
	_rotAngle = 0;
}

const OBJ Enemy::GetObjID() const
{
	return OBJ::ENEMY;
}

int Enemy::Wait()
{
	_updater = &Enemy::WaitUpdate;
	return 0;
}

int Enemy::Sigmoid()
{
	_sigCnt	  = -_sigMax;
	_sigBegin = _pos;
	_sigRange = _sigEnd - _sigBegin;
	_updater  = &Enemy::SigmoidUpdate;
	return 0;
}

int Enemy::Rotation()
{
	/// 回転方向の指定
	_rotDir.x = (_sigBegin.x < LpGame.gameScreenSize.x / 2 ? 1 : -1);
	_rotDir.y = (_sigBegin.y < LpGame.gameScreenSize.y / 2 ? 1 : -1);

	MakeRotaInfo();

	_updater = &Enemy::RotationUpdate;

	return 0;
}

int Enemy::Target()
{
	CalRad(_pos, _aimPos + Vector2d(_moveTblInfo.first, 0), 90);
	auto theta = atan2(_aimPos.y - _pos.y, _aimPos.x - _pos.x);
	auto cost = cos(theta);
	auto sint = sin(theta);
	_vel	 = Vector2d(3 * cost, 3 * sint);
	_updater = &Enemy::TargetUpdate;

	return 0;
}

int Enemy::Move()
{
	/// 行動中の敵がいないときは、ｶｳﾝﾄを変動しないようにしている
	if (_isTable)
	{
		_actionCnt -= (_actionCnt == 0 ? 0 : 1);
	}
	
	_waitAction = 60;		/// 行動待機時間の仮設定
	_isTable = true;
	_rad = 0;
	/// 先頭のｱﾆﾒｰｼｮﾝｶｳﾝﾄを渡している
	SetInvCnt(_leadCnt);
	_updater = &Enemy::MoveUpdate;

	return 0;
}

int Enemy::Spread()
{
	_spDistance = (_spDistance == Vector2d() ? _pos - Vector2d(LpGame.gameScreenSize.x / 2, 1) 
											 : _spDistance);
	_spMag		= (_spMag == 0 ? 1.0 : _spMag);
	_spVel		= (_spVel == 0 ? 0.002 : _spVel);
	_spLength = _spDistance * _spMag;

	_updater = &Enemy::SpreadUpdate;
	return 0;
}

int Enemy::WaitUpdate()
{
	if (_waitTime <= 0)
	{
		if (!ChangeMove())
		{
			Move();
		}
	}
	--_waitTime;

	return 0;
}

int Enemy::SigmoidUpdate()
{
	if (_sigCnt >= _sigMax)
	{
		if (!ChangeMove())
		{
			Move();
		}
		return 0;
	}

	auto sigmoid = [](const double& x, const double& gain){ return 1.0 / (1.0 + exp(-gain * x));};
	double X, Y;
	if (_isTable)
	{
		X = sigmoid(_sigCnt, _gain);
		Y = (_sigCnt + _sigMax) / (_sigMax * 2);
	}
	else
	{
		X = (_sigCnt + _sigMax) / (_sigMax * 2);
		Y = sigmoid(_sigCnt, _gain);
	}

	/// 敵の移動(移動する幅のXとYをグラフに変換して移動させている)
	_pos.x = X * _sigRange.x + _sigBegin.x;
	_pos.y = Y * _sigRange.y + _sigBegin.y;
	
	_sigCnt += _sigAdd;
	CalRad(_pos, _sigEnd, 90);

	return 0;
}

int Enemy::RotationUpdate()
{
	AnimUpdate(5);
	_angle += 4 * _rotDir.x * _rotDir.y;
	_rotAngle += 4;

	auto cost = cos(_angle * (DX_PI / 180));
	auto sint = sin(_angle * (DX_PI / 180));
	auto ePos = _rotCenter + Vector2d(_distance * cost,
									  _distance * sint);
	 CalRad(_pos, ePos, 90);
	_pos = ePos;

	
	if (_rotAngle >= 360 + (-_rotDir.y * 90))
	{
		if (!ChangeMove())
		{
			Move();
		}
	}

	return 0;
}

int Enemy::TargetUpdate()
{
	double theta, cost, sint;
	Vector2 length;
	/// 目標地点までのﾗｼﾞｱﾝ計算
	if (_isTable)
	{
		theta = atan2((_spLength.y + 1) - _pos.y, (_spLength.x + LpGame.gameScreenSize.x / 2) -_pos.x);
		cost = cos(theta);
		sint = sin(theta);

		length = Vector2(abs(_pos.x - (_spLength.x + LpGame.gameScreenSize.x / 2)), 
						 abs(_pos.y - _spLength.y));
	}
	else
	{
		theta = atan2(_aimPos.y - _pos.y, (_aimPos.x + _moveTblInfo.first) - _pos.x);
		cost  = cos(theta);
		sint  = sin(theta);

		length = Vector2(abs(_pos.x - (_aimPos.x + _moveTblInfo.first)), abs(_pos.y - _aimPos.y));

		_vel.x += _moveTblInfo.second;				// 移動ﾃｰﾌﾞﾙの速度を加算している
	}

	/// 目標地点に向けての速度設定
	
	_vel.x = (length.x <= 1 ? 0 : _vel.x);
	_vel.y = (length.y <= 1 ? 0 : _vel.y);

	/// 目標地点の付近まで到達してなかった時、速度計算を行う
	_vel.x = (_vel.x == 0 ? 0 : 3 * cost);
	_vel.y = (_vel.y == 0 ? 0 : 3 * sint);

	if (_vel == Vector2d(0, 0))
	{
		if (_isTable)
		{
			_pos = Vector2d(_spLength.x + LpGame.gameScreenSize.x / 2, _spLength.y);
		}
		else
		{
			_pos = Vector2d(_aimPos.x + _moveTblInfo.first, _aimPos.y);
		}

		if (!ChangeMove())
		{
			Move();
		}
	}
	return 0;
}

int Enemy::SpreadUpdate()
{
	AnimUpdate(1);
	_pos = _spLength + Vector2d(LpGame.gameScreenSize.x / 2, 1);
	return 0;
}

int Enemy::MoveUpdate()
{
	AnimUpdate(1);
	_pos.x += _moveTblInfo.second;
	_sigBegin = _pos;

	if (_moveTblInfo.first == 0 &&
		_moveTblInfo.second == 0)
	{
		Spread();
	}
	return 0;
}

void Enemy::Update()
{
	if (DestryCheck())
	{
		if (!_isAlive && animKey() != ANIM::DEATH)
		{
			animKey(ANIM::DEATH);
			ResetAnim();
		}
		AnimUpdate(1);
		return;
	}
	(this->*_updater)();

	/// 拡縮の情報を更新
	if (_moveTblInfo.first == 0 &&
		_moveTblInfo.second == 0)
	{
		_spLength = _spDistance * _spMag;
		_spMag += _spVel;
		if (_spVel <= 0)
		{
			_spVel = (_spMag <= 1.0 ? -_spVel : _spVel);
		}
		else
		{
			_spVel = (_spMag >= 1.24 ? -_spVel : _spVel);
		}
	}



	_pos += _vel;

	auto center = Vector2(_pos.x + _size.width / 2, _pos.y + _size.height / 2);
	_rect = Rect(center, _size);
}

