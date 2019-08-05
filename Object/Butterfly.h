#pragma once
#include "Enemy.h"
class Butterfly :
	public Enemy
{
public:
	Butterfly();
	Butterfly(const EnemyState& state);
	~Butterfly();

	void SetSigEnd(const Vector2d& sigEnd) override;
private:
	void Init(EN_TYPE type);
};

