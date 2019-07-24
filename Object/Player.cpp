#include <DxLib.h>
#include "../Common/ImageMng.h"
#include "Player.h"
#include "Shot.h"
#include "../Input/KeyState.h"
#include "../Input/PadState.h"

Player::Player()
{
}

Player::Player(const Vector2 & pos, const Size& size)
{
	_size	= size;
	auto center = Vector2(pos.x + _size.width / 2, pos.y + _size.height / 2);
	_pos	= Vector2d(center.x, center.y);
	_rad	= 0.0;
	_rect   = Rect(center, _size);
	
	Init();
	animKey(ANIM::NORMAL);

	/// ﾊﾟｯﾄﾞが接続されていない時、ｷｰ操作の情報を生成する
	if (GetJoypadNum() == 0)
	{
		_input = std::make_unique<KeyState>();
	}
	else
	{
		/// セーブとロードの部分を作成していないので
		/// 作成しておくように...
		_input = std::make_unique<PadState>();
	}
	
	_updater = &Player::IdleUpdate;
}

Player::~Player()
{
}

void Player::Init()
{
	anim_vec data;

	/// ﾃﾞﾌｫﾙﾄｱﾆﾒｰｼｮﾝの登録
	data.emplace_back(IMAGE_ID("player")[0], 30);
	data.emplace_back(IMAGE_ID("player")[1], 60);
	SetAnim(ANIM::NORMAL, data);

	/// 捕獲時ｱﾆﾒｰｼｮﾝの登録
	data.emplace_back(IMAGE_ID("player")[2], 30);
	SetAnim(ANIM::EX, data);

	/// 爆破ｱﾆﾒｰｼｮﾝの登録
	data.emplace_back(IMAGE_ID("pl_blast")[0], 15);
	for (int i = 1; i < 4; ++i)
	{
		data.emplace_back(IMAGE_ID("pl_blast")[i], 15 + (5 * i));
	}
	/// ｱﾆﾒｰｼｮﾝの終了位置を設定している
	data.emplace_back(-1, 60);
	SetAnim(ANIM::DEATH, data);
}

void Player::Idle()
{
	_updater = &Player::IdleUpdate;
}

void Player::Die()
{
	animKey(ANIM::DEATH);
	_updater = &Player::DieUpdate;
}

void Player::Move()
{
	_updater = &Player::MoveUpdate;
}

void Player::IdleUpdate()
{
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
		_pos.x += 5;
	}
	/*else if (_input->IsPressing(INPUT_ID::LEFT))*/
	else if (_input->state(INPUT_ID::LEFT).first)
	{
		_pos.x -= 5;
	}
	else
	{
		Idle();
	}
}

void Player::DieUpdate()
{
}

void Player::Update()
{
	_input->Update();
	(this->*_updater)();
	if (DestryCheck())
	{
		return;
	}

	/// 仮の死亡処理
	if (_input->IsTrigger(INPUT_ID::BTN_1))
	{
		animKey(ANIM::DEATH);
		_isAlive = false;
		ResetInvCnt();
	}
	auto center = Vector2(_pos.x + _size.width / 2, _pos.y + _size.height / 2);
	_rect	    = Rect(center, _size);

	/// 仮でﾃﾞﾊﾞｯｸﾞ用の描画をしている
	_dbgDrawBox(_rect.Left()  - _size.width / 2, _rect.Top()	- _size.height / 2,
				_rect.Right() - _size.width / 2, _rect.Bottom() - _size.height / 2, 0x00ff00, true);
	_dbgDrawFormatString(0, 0, 0xffffff, "(player) X座標 : %d, Y座標 : %d", _pos.x, _pos.y);


	/// とりあえず今は無視しておこう
	///*if (_input->IsTrigger(INPUT_ID::BTN_1))*/
	//if (_input->state(INPUT_ID::BTN_1).first &&
	//  !(_input->state(INPUT_ID::BTN_1).second))
	//{
	//	_shots.push_back(std::make_shared<Shot>(_pos));
	//}

	///// 仮のショット
	//for (auto& shot : _shots)
	//{
	//	shot->Update();
	//	shot->Draw();
	//}
}

void Player::Draw()
{
}

const Obj Player::GetObjID() const
{
	return Obj::PLAYER;
}
