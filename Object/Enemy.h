#pragma once

#include <tuple>
#include <array>
#include "Object.h"
#include "../Common/ImageMng.h"
#include "../DebugConOut.h"

enum class EN_STATE
{
	POS,
	SIZE,
	TYPE,
	NUM,
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
	SCORPION,
	MAX
};

// 0 : 座標, 1 : ｻｲｽﾞ 2 : 種類, 3 : 敵のﾃｰﾌﾞﾙの位置 4 : 目標地点 5 : ｼｸﾞﾓｲﾄﾞの移動地点
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, int, Vector2d, Vector2d>;

class Enemy :
	public Object
{
public:
	Enemy();
	virtual ~Enemy();
	
	void Update() override;
	void Draw() override;
	const Obj GetObjID() const override;

protected:
	//// 必要のない機能はすべて、privateもしくは削除する
	void Sigmoid();
	void Target();
	void Rotation();
	void Move();
	void Shot();

	void SigmoidUpdate();
	void TargetUpdate();
	void RotationUpdate();
	void MoveUpdate();
	void ShotUpdate();

	/// protectedに必要のないものは、privateに移動しておく
	Vector2 _rotDir;
	Vector2d _aimPos;		// 目標座標
	Vector2d _sPos;			// ｼｸﾞﾓｲﾄﾞのｽﾀｰﾄ地点
	Vector2d _ePos;			// ｼｸﾞﾓｲﾄﾞのｺﾞｰﾙ地点
	Vector2d _rotCenter;	// 回転するときの中心点

	double _rotDistance;	// 回転幅の距離
	double _rotAngle;		// 回転用の角度

	double _sigCnt;		// ｼｸﾞﾓｲﾄﾞ関数の値

	const double _sigMax;
	const double _distance;
private:
	
	void Init(EN_TYPE type, EN_ID id);
	void CalRad(const Vector2d& sPos, const Vector2d& ePos, const double& angle);
	void MakeRotaInfo(const double& distance);		// 回転するための情報を生成している

	void (Enemy::*_updater)();

};

