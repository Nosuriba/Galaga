#include <tuple>
#include "Object.h"

enum class EN_STATE
{
	POS,
	TYPE,
	SIZE,
	AIM,
	MAX
};

enum class EN_TYPE
{
	NORMAL,
	BONUS,
	BOSS,
	MAX
};

// 0 : pos, 1 : type, 2 : aimPos
using EnemyState = std::tuple<Vector2, EN_TYPE, Size, Vector2>;

class Enemy :
	public Object
{
public:
	Enemy();
	Enemy(EnemyState state);
	~Enemy();
	
	void Update() override;
	void Draw() override;
	const Obj GetObjID() const override;
private:
	void Idle();
	void Target();
	void Rotation();
	void Move();
	void Shot();
	void Die();

	void IdleUpdate();
	void TargetUpdate();
	void RotationUpdate();
	void MoveUpdate();
	void ShotUpdate();
	void DieUpdate();

	void Init(EN_TYPE type);
	void (Enemy::*_updater)();

	Vector2 _vel;
	Vector2 _aimPos;			// –Ú•WˆÊ’u
};

