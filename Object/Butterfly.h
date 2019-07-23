#pragma once
#include "Enemy.h"
class Butterfly :
	public Enemy
{
public:
	Butterfly();
	Butterfly(const EnemyState& state);
	~Butterfly();
private:
	void Init(EN_TYPE type);
};

