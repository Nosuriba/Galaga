#pragma once

#include "Object.h"

class Player :
	public Object
{
public:
	Player();
	Player(const Vector2f& pos, const Vector2f& vel);
	~Player();

	void Draw();
	void Update(const Input& p);

private:

};

