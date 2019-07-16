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

//	0 : pos, 1 : size  2 : type, 3 : id, 4 : aimPos, 5 : num
using EnemyState = std::tuple<Vector2, Size, EN_TYPE, EN_ID, Vector2, int>;

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
	void MidMove();
	void Target();
	void Rotation();
	void Move();
	void Shot();

	void MidMoveUpdate();
	void TargetUpdate();
	void RotationUpdate();
	void MoveUpdate();
	void ShotUpdate();

	void Init(EN_TYPE type, EN_ID id);
	void CalAngle();			// 角度計算用
	void (Enemy::*_updater)();

	Vector2 _aimPos;	// 目標座標
	Vector2 _midPos;	// 中間座標

	int _midCnt;		// 中間座標まで移動する時間
};

