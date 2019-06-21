#pragma once

#include "Object.h"

class Player :
	public Object
{
public:
	Player();
	Player(const Vector2f& pos, const Vector2f& vel);
	~Player();

	void Idle();
	void Shot();
	void Die();

	void IdleUpdate(const Input& p);
	void ShotUpdate(const Input& p);
	void DieUpdate(const Input& p);

	void Move(const Input& p);
	void Update(const Input& p) override;
	void Draw() override;
private:
	void (Player::*_updater)(const Input& p);
};

