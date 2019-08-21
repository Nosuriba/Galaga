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

	void Update(const std::unique_ptr<InputState>& p) override;
	const OBJ GetObjID() const override;
private:
	void Init();

	void Idle(const std::unique_ptr<InputState>& p);
	void Die(const std::unique_ptr<InputState>& p);
	void Move(const std::unique_ptr<InputState>& p);

	void IdleUpdate(const std::unique_ptr<InputState>& p);
	void MoveUpdate(const std::unique_ptr<InputState>& p);
	void DieUpdate(const std::unique_ptr<InputState>& p);

	void IsOutScreen();

	void (Player::*_updater)(const std::unique_ptr<InputState>& p);

	int _inviCnt;		// –³“GŽžŠÔ
};

