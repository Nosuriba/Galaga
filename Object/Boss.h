#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
public:
	Boss();
	Boss(const EnemyState& state);
	~Boss();

	void SetSigEnd(const Vector2d& sigEnd) override;
private:
	void Init(EN_TYPE type);
};

