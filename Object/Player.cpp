#include <DxLib.h>
#include "../ImageMng.h"
#include "Player.h"

Player::Player()
{
}

Player::Player(const Vector2f & pos, const Vector2f & vel)
{
	_pos = pos;
	_vel = vel;
}

Player::~Player()
{
}

void Player::Draw()
{
	Object::Draw(ImageMng::GetInstance().GetID("image/player.png"));
}

void Player::Update(const Input& p)
{
	if (p.IsKeyPressing(KEY_INPUT_D))
	{
		_pos.x += 1.f;
	}
	else if (p.IsKeyPressing(KEY_INPUT_A))
	{
		_pos.x -= 1.f;
	}
	else if (p.IsKeyPressing(KEY_INPUT_W))
	{
		_pos.y -= 1.f;
	}
	else if (p.IsKeyPressing(KEY_INPUT_S))
	{
		_pos.y += 1.f;
	}
	else{}
}
