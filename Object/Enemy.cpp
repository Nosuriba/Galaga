#include <DxLib.h>
#include <stdlib.h>
#include "Enemy.h"
#include "../DebugDisp.h"
#include "../DebugConOut.h"

char Enemy::now = 0;
char Enemy::old = 0;

Enemy::Enemy() : _sigMax(10), _distance(30)
{
	_moveList.emplace_back(&Enemy::Sigmoid);
	_moveList.emplace_back(&Enemy::Rotation);
	_moveList.emplace_back(&Enemy::Target);

	_sigAdd = 0.3;

	Wait();
}

Enemy::~Enemy()
{
	_moveTblInfo = { 0,0 };
}

int Enemy::Wait()
{
	_updater = &Enemy::WaitUpdate;
	return 0;
}

int Enemy::Sigmoid()
{
	/// ｼｸﾞﾓｲﾄﾞを使った移動範囲の設定
	_sigCnt	  = -_sigMax;
	_sigBegin = _pos;
	_sigRange = _sigEnd - _sigBegin;
	_updater  = &Enemy::SigmoidUpdate;
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

int Enemy::Rotation()
{
	/// 回転方向の設定
	_rotDir.x = (_sigBegin.x < LpGame.gameScreenSize.x / 2 ? 1 : -1);
	_rotDir.y = (_sigBegin.y < LpGame.gameScreenSize.y / 2 ? 1 : -1);

	MakeRotaInfo();

	_updater = &Enemy::RotationUpdate;

	return 0;
}

int Enemy::Move()
{
	_tblFlag = true;
	_rad = 0;
	/// 先頭のｱﾆﾒｰｼｮﾝｶｳﾝﾄを渡している
	SetInvCnt(_leadCnt);
	_updater = &Enemy::MoveUpdate;

	return 0;
}

int Enemy::WaitUpdate()
{
	if (_waitCnt <= 0)
	{
		if (!ChangeMove())
		{
			Move();
		}
	}
	--_waitCnt;

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

	auto sigmoid = [](const double& x){ return 1.0 / (1.0 + exp(-1.0 * x));};
	double X = (_sigCnt + _sigMax) / (_sigMax * 2);
	double Y = sigmoid(_sigCnt);

	/// 敵の移動(移動する幅のXとYをグラフに変換して移動させている)
	_pos.x = X * _sigRange.x + _sigBegin.x;
	_pos.y = Y * _sigRange.y + _sigBegin.y;
	
	_sigCnt += _sigAdd;
	CalRad(_pos, _sigEnd, 90);

	return 0;
}
 
int Enemy::TargetUpdate()
{
	/// 目標地点までのﾗｼﾞｱﾝ計算
	auto theta = atan2(_aimPos.y - _pos.y, (_aimPos.x + _moveTblInfo.first) - _pos.x);
	auto cost = cos(theta);
	auto sint = sin(theta);

	/// 敵の座標から目標地点までの距離の計算
	auto length = Vector2(abs(_pos.x - (_aimPos.x + _moveTblInfo.first)), abs(_pos.y - _aimPos.y));

	/// 目標地点に向けての速度設定
	_vel.x += _moveTblInfo.second;				// 移動ﾃｰﾌﾞﾙの速度を加算している
	_vel.x = (length.x <= 1 ? 0 : _vel.x);
	_vel.y = (length.y <= 1 ? 0 : _vel.y);

	/// 目標地点の付近まで到達してなかった時、速度計算を行う
	_vel.x = (_vel.x == 0 ? 0 : 3 * cost);
	_vel.y = (_vel.y == 0 ? 0 : 3 * sint);
	
	if (_vel == Vector2d(0,0))
	{
		_pos = Vector2d(_aimPos.x + _moveTblInfo.first, _aimPos.y);
		if (!ChangeMove())
		{
			Move();
		}
	}

	return 0;
}

int Enemy::RotationUpdate()
{
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

int Enemy::MoveUpdate()
{
	_pos.x += _moveTblInfo.second;
	_sigBegin = _pos;
	return 0;
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
	/// 中心地点の計算を別の場所で行った方がいい
	_rotCenter = _pos + Vector2d(0, _distance * _rotDir.y);

	auto theta  = atan2(_pos.y - _rotCenter.y,  _pos.x - _rotCenter.x);
	_angle		= theta * (180 / DX_PI);
	_rotAngle	= 0;
}

const Obj Enemy::GetObjID() const
{
	return Obj::ENEMY;
}
