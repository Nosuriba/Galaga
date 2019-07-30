#pragma once
#include "Enemy.h"
class Boss :
	public Enemy
{
public:
	Boss();
	Boss(const EnemyState& state);
	~Boss();
private:
	void Init(EN_TYPE type);
};

