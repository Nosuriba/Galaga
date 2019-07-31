#pragma once
#include "Enemy.h"

class Bee :
	public Enemy
{
public:
	Bee();
	Bee(const EnemyState& state);
	~Bee();
	int MoveUpdate() override;

	void SetMoveInfo(const Vector2d& sigEnd) override;
	void Update() override;
	
private:
	void Init(EN_TYPE type);
};

