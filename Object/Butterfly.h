#pragma once
#include "Enemy.h"
class Butterfly :
	public Enemy
{
public:
	Butterfly();
	Butterfly(const EnemyState& state);
	~Butterfly();

	void Update() override;
	int MoveUpdate() override;
private:
	void Init(EN_TYPE type);
};

