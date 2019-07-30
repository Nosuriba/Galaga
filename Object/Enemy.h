#pragma once

#include <tuple>
#include <array>
#include <list>
#include "Object.h"
#include "../Common/ImageMng.h"
#include "../DebugConOut.h"

enum class EN_STATE
{
	POS,
	SIZE,
	TYPE,
	NUM,
	WAIT,
	AIM,
	SIGPOS,
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

// 0 : 座標, 1 : ｻｲｽﾞ 2 : 種類, 3 : 敵のﾃｰﾌﾞﾙの位置 4 : 待機時間 5 : 目標地点 6 : ｼｸﾞﾓｲﾄﾞの移動地点
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, int, int, Vector2d, Vector2d>;

class Enemy :
	public Object
{
public:
	Enemy();
	virtual ~Enemy();
	
	virtual void Update() = 0;
	const Obj GetObjID() const override;

protected:
	/// 各行動の初期化
	int Wait();
	int Sigmoid();
	int Target();
	int Rotation();
	int Move();

	/// 各行動の更新
	int WaitUpdate();
	int SigmoidUpdate();
	int TargetUpdate();
	int RotationUpdate();
	int MoveUpdate();

	void SetSigAdd(const double& sigAdd);	// ｼｸﾞﾓｲﾄﾞに加算する値の変更用

	std::list<int(Enemy::*)()> _moveList;	// 移動状態の保存用
	int (Enemy::*_updater)();

	/// protectedに必要のないものは、privateに移動しておく
	Vector2d _aimPos;		// 目標座標
	Vector2d _sigBegin;		// ｼｸﾞﾓｲﾄﾞの始点
	Vector2d _sigEnd;		// ｼｸﾞﾓｲﾄﾞの終点
	Vector2d _sigRange;		// ｼｸﾞﾓｲﾄﾞの移動幅

	Vector2 _rotDir;
	Vector2d _rotCenter;	// 回転するときの中心点

	int _waitCnt;			// 敵が移動する前の待機時間

	int _angle;
	int _rotAngle;			// 回点した角度

	double _sigCnt;			// ｼｸﾞﾓｲﾄﾞ関数の値

	const double _sigMax;
	const double _distance;

	/// debug用で敵を削除している(後で必ず消せ！！)
	static char now;
	static char old;
private:

	bool ChangeMove();			// 移動状態の変更
	void CalRad(const Vector2d& sPos, const Vector2d& ePos, const double& angle);
	void MakeRotaInfo();		// 回転するための情報を生成している

	double _sigAdd;				// ｼｸﾞﾓｲﾄﾞのｶｳﾝﾄ加算用
};

