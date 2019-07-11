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

// 0 : pos, 1 : type, 2 : size, 3 : aimPoint
using EnemyState = std::tuple<Vector2, EN_TYPE, Vector2, Vector2>;

class Enemy :
	public Object
{
public:
	Enemy();
	Enemy(const Vector2 & pos, EN_TYPE type);
	~Enemy();
	
	void Update() override;
	void Draw() override;
	const Obj GetObjID() const override;
private:
	void Rotation();
	void Move();
	void Shot();
	void Die();

	void RotationUpdate();
	void IdleUpdate();
	void MoveUpdate();
	void ShotUpdate();
	void DieUpdate();

	void Init(const int&  id);
	void (Enemy::*_updater)();
};

