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

	SET_IMAGE_ID("player", "image/player.png", Vector2(3, 1), Vector2(_charSize.width, _charSize.height));
	SET_IMAGE_ID("blast", "image/pl_blast.png", Vector2(4, 1), Vector2(_charSize.width * 2, _charSize.height * 2));

	Init();
	_animKey = ANIM::NORMAL;

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
	_animKey = ANIM::BLAST;
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
}

void Player::Init()
{
	anim_vec data;

	/// ID(描画する位置番号), フレーム
	data.emplace_back(IMAGE_ID("player")[0], 30);
	data.emplace_back(IMAGE_ID("player")[1], 30);
	SetAnim(ANIM::NORMAL, std::move(data));
	data.clear();

	/// 爆破ｱﾆﾒｰｼｮﾝの登録(仮)
	data.resize(4);
	auto id = data.begin();
	for (; id != data.end(); ++id)
	{
		auto cnt = id - data.begin();
		data[cnt] = std::make_pair(IMAGE_ID("blast")[cnt], 10);
	}
	SetAnim(ANIM::BLAST, std::move(data));
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

	Object:: AnimUpdate();
}

void Player::Draw()
{
}

const Obj Player::GetObjID() const
{
	return Obj::PLAYER;
}