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

// 0 : 座標, 1 : ｻｲｽﾞ 2 : 種類, 3 : 敵のﾃｰﾌﾞﾙの位置 4 : 待機時間 5 : ｼｸﾞﾓｲﾄﾞの終点, 6 : 目標地点
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, int, int, Vector2d, Vector2d>;

class Enemy :
	public Object
{
public:
	Enemy();
	virtual ~Enemy();
	void Update();

	/// 関数ﾎﾟｲﾝﾀのｱﾄﾞﾚｽを取得するため、publicに移動した
	int Sigmoid();
	int Rotation();
	int Target();

	const OBJ GetObjID() const override;
	virtual void SetSigEnd(const Vector2d& sigEnd) override = 0;

protected:
	/// 各行動の初期化
	int Wait();
	int Move();
	int Spread();

	/// 各行動の更新
	int WaitUpdate();
	int SigmoidUpdate();
	int RotationUpdate();
	int TargetUpdate();
	int SpreadUpdate();						//// 敵が全員出現したときに拡大縮小するような挙動にする
	int MoveUpdate();

	void SetSigAdd(const double& sigAdd);	// ｼｸﾞﾓｲﾄﾞに加算する値の変更用

	std::list<int(Enemy::*)()> _moveList;	// 移動状態の保存用
	int (Enemy::*_updater)();

	/// protectedに必要のないものは、privateに移動しておく
	Vector2d _aimPos;		// 目標座標
	Vector2d _sigRange;		// ｼｸﾞﾓｲﾄﾞの移動幅

	Vector2d _spLength;		// 広がる範囲

	int _waitTime;			// 敵が移動する前の待機時間
	int _waitAction;		// 敵が行動するまでの待機時間

	double _sigAdd;			// ｼｸﾞﾓｲﾄﾞのｶｳﾝﾄ加算用
	double _gain;			// ｼｸﾞﾓｲﾄﾞのｸﾞﾗﾌ制御用
	double _spMag;			// 広がる倍率
	double _spVel;			// 広がる速度

	static int _actionCnt;		// 行動中の敵の数
private:
	bool ChangeMove();			// 移動状態の変更
	void CalRad(const Vector2d& sPos, const Vector2d& ePos, const double& angle);
	void MakeRotaInfo();		// 回転するための情報を生成している

	Vector2  _rotDir;
	Vector2d _rotCenter;	// 回転するときの中心点

	int _angle;
	int _rotAngle;			// 回転した角度

	double _sigCnt;			// ｼｸﾞﾓｲﾄﾞの値
	const double _sigMax;
	const double _distance;
};

