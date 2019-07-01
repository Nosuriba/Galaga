#include <DxLib.h>
#include "../Common/ImageMng.h"
#include "Player.h"
#include "Shot.h"
#include "../Input/KeyState.h"
#include "../Input/PadState.h"

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
	animKey(ANIM::NORMAL);
	_input = std::make_unique<KeyState>();

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
	animKey(ANIM::BLAST);
	_updater = &Player::DieUpdate;
}

void Player::Move()
{
	_updater = &Player::MoveUpdate;
}

void Player::IdleUpdate()
{
	/// 仮の死亡処理
	/*if (_input->IsTrigger(INPUT_ID::BTN_1))
	{
		Die();
	}
*/
	/*if (_input->IsPressing(INPUT_ID::RIGHT) ||
		  _input->IsPressing(INPUT_ID::LEFT))*/
	if (_input->state(INPUT_ID::RIGHT).first ||
		_input->state(INPUT_ID::LEFT).first)
	{
		Move();
	}
}

void Player::MoveUpdate()
{
	/*if (_input->IsPressing(INPUT_ID::RIGHT))*/
	if (_input->state(INPUT_ID::RIGHT).first)
	{
		_pos.x += 5.f;
	}
	/*else if (_input->IsPressing(INPUT_ID::LEFT))*/
	else if (_input->state(INPUT_ID::LEFT).first)
	{
		_pos.x -= 5.f;
	}
	else
	{
		Idle();
	}
}

void Player::DieUpdate()
{
}

void Player::Init()
{
	anim_vec data;

	/// ﾃﾞﾌｫﾙﾄｱﾆﾒｰｼｮﾝの登録
	data.emplace_back(IMAGE_ID("player")[0], 30);
	data.emplace_back(IMAGE_ID("player")[1], 30);
	SetAnim(ANIM::NORMAL, data);

	/// 捕獲時ｱﾆﾒｰｼｮﾝの登録
	data.emplace_back(IMAGE_ID("player")[2], 30);
	SetAnim(ANIM::EX, data);

	/// 爆破ｱﾆﾒｰｼｮﾝの登録(仮)
	data.resize(4);
	auto id = data.begin();
	for (; id != data.end(); ++id)
	{
		auto cnt = id - data.begin();
		data[cnt] = std::make_pair(IMAGE_ID("blast")[cnt], 10);
	}
	SetAnim(ANIM::BLAST, data);
}

void Player::Update()
{
	_input->Update();
	(this->*_updater)();

	/*if (_input->IsTrigger(INPUT_ID::BTN_1))*/
	if (_input->state(INPUT_ID::BTN_1).first &&
		!(_input->state(INPUT_ID::BTN_1).second))
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
}

const Obj Player::GetObjID() const
{
	return Obj::PLAYER;
}