#include <DxLib.h>
#include "../Common/ImageMng.h"
#include "Player.h"
#include "Shot.h"

Player::Player()
{
}

Player::Player(const Vector2f & pos, const Vector2f & vel)
{
	_pos = pos;
	_vel = vel;

	auto center = Vector2(_pos.x, pos.y);
	auto size = _charSize;
	_rect = Rect(center, size);

	_updater = &Player::IdleUpdate;
}

Player::~Player()
{
}

void Player::Idle()
{
	_updater = &Player::IdleUpdate;
}

void Player::Die()
{
	_updater = &Player::DieUpdate;
}

void Player::Move()
{
	_updater = &Player::MoveUpdate;
}

void Player::IdleUpdate(const Input & p)
{
	/// 仮の死亡処理
	if (p.IsKeyTrigger(KEY_INPUT_Z))
	{
		Die();
	}

	if (p.IsKeyPressing(KEY_INPUT_A) ||
		p.IsKeyPressing(KEY_INPUT_D))
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

void Player::DieUpdate(const Input & p)
{
	invCnt++;
	/// 一定時間経つと、死亡状態から解除される
	if (invCnt >= 40)
	{
		invCnt = 0;
		Idle();
	}
}

void Player::Update(const Input& p)
{
	(this->*_updater)(p);

	if (p.IsKeyTrigger(KEY_INPUT_SPACE))
	{
		_shots.push_back(std::make_shared<Shot>(_pos, Vector2f(0, -2.f)));
	}
	/// 仮のショット
	for (auto& shot : _shots)
	{
		shot->Update();
		shot->Draw();
	}
}

void Player::Draw()
{
	/// 死亡時の爆破にｱﾆﾒｰｼｮﾝをつけている
	if (_updater == &Player::DieUpdate)
	{
		/// 仮のｱﾆﾒｰｼｮﾝ
		animCnt = (invCnt / 10) % 4;
		DrawRectGraph(_pos.x - 16, _pos.y - 16, animCnt * 64 , 0, 64, 64,
					   LpImageMng.GetID("image/pl_blast.png"), true, true);
	}
	else
	{

		DrawRectGraph(_pos.x, _pos.y, 0, 0, _charSize.width, _charSize.height,
					  LpImageMng.GetID("image/player.png"), true, true);
	}
	
}