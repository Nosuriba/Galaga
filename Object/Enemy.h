#include "Object.h"

class Enemy :
	public Object
{
public:
	Enemy();
	Enemy(const Vector2f & pos, const Vector2f & vel);
	~Enemy();
	
	void Rotation();
	void Move();
	void Shot();
	void Die();

	void RotationUpdate();
	void IdleUpdate();
	void MoveUpdate();
	void ShotUpdate();
	void DieUpdate();

	void Update(const Input& p) override;
	void Draw() override;
	const Obj GetObjID() const override;
private:
	void Init();
	void (Enemy::*_updater)();
};

