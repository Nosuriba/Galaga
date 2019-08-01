#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
public:
	Boss();
	Boss(const EnemyState& state);
	~Boss();

	void SetMoveInfo(const Vector2d& sigEnd) override;
	int MoveUpdate() override;
private:
	void Init(EN_TYPE type);
};

