#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
public:
	Boss();
	Boss(const EnemyState& state);
	~Boss();

	void Update() override;
	int MoveUpdate() override;
private:
	void Init(EN_TYPE type);
};

