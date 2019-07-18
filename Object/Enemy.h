#include <tuple>
#include "Object.h"

enum class EN_STATE
{
	POS,
	SIZE,
	TYPE,
	ID,
	AIM,
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

//	0 : 座標, 1 : ｻｲｽﾞ  2 : 種類, 3 : ID, 4 : 目標地点, 5 : 敵のﾃｰﾌﾞﾙの位置 6 : 移動方向の情報
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, EN_ID, Vector2d, int, std::vector<Vector2>>;

class Enemy :
	public Object
{
public:
	Enemy();
	Enemy(const EnemyState& state);
	~Enemy();
	
	void Update() override;
	void Draw() override;
	const Obj GetObjID() const override;
private:
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

	void Init(EN_TYPE type, EN_ID id);
	void CalRad(const Vector2d& sPos, const Vector2d& ePos);
	double Sigmoid(const double& gain, const double& x);	
	void (Enemy::*_updater)();

	Vector2d _aimPos;	// 目標座標
	Vector2d _nextPos;

	std::vector<Vector2d> dbgPoint;
	std::vector<Vector2> _moveDir;
	// int _moveDir;		// 移動方向
	int _moveCnt;		// 移動する回数

	double _rotAngle;	// 回転用の角度
	double _sigCnt;		// ｼｸﾞﾓｲﾄﾞ関数の値
	double _sigRange;	// ｼｸﾞﾓｲﾄﾞ関数の範囲
};

