#pragma once

#include "Object.h"

class Shot;

using shared_shot = std::shared_ptr<Shot>;

class Player :
	public Object
{
public:
	Player();
	Player(const Vector2f& pos, const Vector2f& vel);
	~Player();

	void Idle();
	void Die();
	void Move();

	void IdleUpdate(const Input& p);
	void MoveUpdate(const Input& p);
	void DieUpdate(const Input& p);

	void Update(const Input& p) override;
	void Draw() override;
	const Obj GetObjID() const override;
private:
	void Init();
	void AnimUpdate();			// ±∆“∞ºÆ›ÇÃçXêVóp

	void (Player::*_updater)(const Input& p);
	std::vector<shared_shot> _shots;
};

