#pragma once
#include "Enemy.h"

class Bee :
	public Enemy
{
public:
	Bee();
	Bee(const EnemyState& state);
	~Bee();

	void SetSigEnd(const Vector2d& sigEnd) override;
	
private:
	void Init(EN_TYPE type);
};

