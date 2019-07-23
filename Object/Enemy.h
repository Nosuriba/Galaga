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
	AIM,
	TYPE,
	NUM,
	MOVEINFO,
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

//	0 : 座標, 1 : ｻｲｽﾞ  2 : 目標地点 3 : 種類, 4 : 敵のﾃｰﾌﾞﾙの位置 5 : 移動方向の情報
using EnemyState = std::tuple<Vector2, Size, Vector2d, EN_TYPE, int, std::vector<int>>;

class Enemy :
	public Object
{
public:
	Enemy();
	Enemy(const EnemyState& state);
	virtual ~Enemy();
	
	void Update() override;
	void Draw() override;
	const Obj GetObjID() const override;

protected:
	//// 必要のない機能はすべて、privateもしくは削除する
	void Curve();
	void Target();
	void Rotation();
	void Move();
	void Shot();

	void CurveUpdate();
	void TargetUpdate();
	void RotationUpdate();
	void MoveUpdate();
	void ShotUpdate();

	/// protectedに必要のないものは、privateに移動しておく
	Vector2 _rotDir;
	Vector2d _aimPos;		// 目標座標
	Vector2d _nextPos;
	Vector2d _rotCenter;	// 回転するときの中心点

	std::vector<int> _curveID;			// 曲がるIDの指定
	std::vector<Vector2d> dbgPoint;
	std::array<Vector2, 4> _curveInfo;
	double _rotDistance;	// 回転幅の距離
	double _rotAngle;		// 回転用の角度

	int _sigCnt;		// ｼｸﾞﾓｲﾄﾞ関数の値
	int _sigRange;		// ｼｸﾞﾓｲﾄﾞ関数の範囲

	const int _sigMax;
	const double _distance;
private:
	
	void Init(EN_TYPE type, EN_ID id);
	void CalRad(const Vector2d& sPos, const Vector2d& ePos, const double& angle);
	void MakeRotaInfo(const double& distance);		// 回転するための情報を生成している

	void (Enemy::*_updater)();

};

