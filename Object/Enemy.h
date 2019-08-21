#pragma once

#include <tuple>
#include <array>
#include <list>
#include "Object.h"
#include "../Common/ImageMng.h"
#include "../DebugConOut.h"
#include "../Game.h"

enum class EN_STATE
{
	POS,
	SIZE,
	TYPE,
	WAIT,
	SIGPOS,
	AIM,
	MAX
};

/// 敵の種類
enum class EN_TYPE
{
	NORMAL,
	BONUS,
	BOSS,
	MAX
};

/// 敵のID
enum class EN_ID
{
	BEE,
	BUTTERFLY,
	BOSS,
	MAX
};

// 0 : 座標, 1 : ｻｲｽﾞ 2 : 種類, 3 : 待機時間 4 : ｼｸﾞﾓｲﾄﾞの終点, 5 : 目標地点
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, int, Vector2d, Vector2d>;

class Enemy :
	public Object
{
public:
	Enemy();
	virtual ~Enemy();
	void Update(const std::unique_ptr<InputState>& p);

	/// 関数ﾎﾟｲﾝﾀのｱﾄﾞﾚｽを取得するため、publicに移動した
	int Sigmoid();
	int Rotation();
	virtual int Target();
	int TargetUpdate();

	const OBJ GetObjID() const override;
	virtual void SetSigEnd(const Vector2d& sigEnd) override = 0;

protected:
	/// 各行動の初期化
	int Wait();
	int Move();
	int Scaling();

	/// 各行動の更新
	int WaitUpdate();
	virtual int SigmoidUpdate();
	int RotationUpdate();
	int ScalingUpdate();						
	int MoveUpdate();

	void CalRad(const Vector2d& sPos, const Vector2d& ePos, const double& angle);

	std::list<int(Enemy::*)()> _moveList;	// 移動状態の保存用
	int (Enemy::*_updater)();

	Vector2d _aimPos;		// 目標座標
	Vector2d _sigRange;		

	/// 拡縮の移動で使用するもの
	Vector2d _spLength;		
	Vector2d _spDistance;	

	int _waitTime;			// 敵が移動する前の待機時間
	int _shotWait;

	bool _isAction;

	double _sigAdd;			// ｼｸﾞﾓｲﾄﾞのｶｳﾝﾄ加算用
	double _gain;			
	double _spMag;			
	double _spVel;			

	static int _actionCnt;		
private:
	bool ChangeMove();

	void MakeRotaInfo();		

	Vector2  _rotDir;
	Vector2d _rotCenter;	

	int _angle;
	int _rotAngle;			// 回転した角度

	double _sigCnt;			
	const double _sigMax;
	const double _distance;
};

