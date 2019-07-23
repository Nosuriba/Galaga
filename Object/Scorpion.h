#pragma once
#include "Enemy.h"
class Scorpion :
	public Enemy
{
public:
	Scorpion();
	Scorpion(const EnemyState& state);
	~Scorpion();
private:
	void Init(EN_TYPE type);
};

