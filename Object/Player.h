#pragma once

#include <memory>
#include "Object.h"

class Shot;
class InputState;

using shared_shot = std::shared_ptr<Shot>;

class Player :
	public Object
{
public:
	Player();
	Player(const Vector2& pos, const Size& size);
	~Player();


	void Update() override;
	void Draw() override;
	const Obj GetObjID() const override;
private:
	void Init();

	void Idle();
	void Die();
	void Move();

	void IdleUpdate();
	void MoveUpdate();
	void DieUpdate();

	void (Player::*_updater)();

	std::unique_ptr<InputState> _input;
	std::vector<shared_shot> _shots;
};

