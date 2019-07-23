#pragma once
#include "Enemy.h"
class Bee :
	public Enemy
{
public:
	Bee();
	Bee(const EnemyState& state);
	~Bee();
private:
	void Init(EN_TYPE type);
};

