#include <DxLib.h>
#include "../Common/ImageMng.h"
#include "Player.h"

Player::Player()
{
}

Player::Player(const Vector2f & pos, const Vector2f & vel)
{
	_pos = pos;
	_vel = vel;

	_updater = &Player::IdleUpdate;
}

Player::~Player()
{
}

void Player::Idle()
{
	_updater = &Player::IdleUpdate;
}

void Player::Move()
{
	_updater = &Player::MoveUpdate;
}

void Player::Shot()
{
	_updater = &Player::ShotUpdate;
}

void Player::Die()
{
	_updater = &Player::DieUpdate;
}

void Player::IdleUpdate(const Input & p)
{
	if (p.IsKeyPressing(KEY_INPUT_D) ||
		p.IsKeyPressing(KEY_INPUT_A))
	{
		Move();
	}
}

void Player::MoveUpdate(const Input & p)
{
	if (p.IsKeyPressing(KEY_INPUT_D))
	{
		_pos.x += 5.f;
	}
	else if (p.IsKeyPressing(KEY_INPUT_A))
	{
		_pos.x -= 5.f;
	}
	else
	{
		Idle();
	}
}

void Player::ShotUpdate(const Input & p)
{
	_updater = &Player::ShotUpdate;
}

void Player::DieUpdate(const Input & p)
{
	_updater = &Player::DieUpdate;
}

void Player::Update(const Input& p)
{
	(this->*_updater)(p);
}

void Player::Draw()
{
	/// こっちが本命
	/*DrawRectGraph(_pos.x, _pos.y, 0, 0, charSize.x, charSize.y,
				 ImageMng::GetInstance().GetID("image/player.png"), true, true);*/
	int img = ImageMng::GetInstance().GetID("image/player.png", Vector2(3, 1), Vector2(charSize.x, charSize.y))[0];
	DrawGraph(_pos.x, _pos.y, img, true);
}