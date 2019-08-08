#include <DxLib.h>
#include "../Common/ImageMng.h"
#include "Player.h"
#include "Shot.h"
#include "../Input/KeyState.h"
#include "../Input/PadState.h"
#include "../Game.h"

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
	_inviCnt = 0;
	
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
		_pos.x += 4;
	}
	/*else if (_input->IsPressing(INPUT_ID::LEFT))*/
	else if (_input->state(INPUT_ID::LEFT).first)
	{
		_pos.x -= 4;
	}
	else
	{
		Idle();
	}
}

void Player::DieUpdate()
{
}

void Player::IsOutScreen()
{
	if (_pos.x < _size.width / 2)
	{
		_pos.x = _size.width / 2;
	}
	else if (_pos.x >= LpGame.gameScreenSize.x - _size.width / 2)
	{
		_pos.x = LpGame.gameScreenSize.x - _size.width / 2;
	}
}

void Player::Update()
{
	if (DestryCheck())
	{
		if (!_isAlive && animKey() != ANIM::DEATH)
		{

			/// 減らす仕組みにすればいいのかな
			for (auto& shot : _shots)
			{
				shot = nullptr;
			}
			LpAudioMng.PlaySE("Music/pl_die.mp3");
			animKey(ANIM::DEATH);
			ResetAnim();
		}
		AnimUpdate(1);
		/// 死亡した時、蘇生するようにしている
		if (_isDeath)
		{
			/// 死亡した時、体力があるか確認して
			animKey(ANIM::NORMAL);
			ResetAnim();
			_isAlive = true;
			_isDeath = false;
		}
		return;
	}
	AnimUpdate(1);
	_input->Update();
	(this->*_updater)();
	
	IsOutScreen();
	auto center = Vector2(_pos.x + _size.width / 2, _pos.y + _size.height / 2);
	_rect	    = Rect(center, _size);

	/// ｼｮｯﾄに関する処理
	for (auto& shot : _shots)
	{
		if (shot != nullptr)
		{
			if (shot->IsOutScreen())
			{
				shot = nullptr;
				continue;
			}
			shot->Update();
		}
	}

	/// ｼｮｯﾄの生成
	/*if (_input->IsTrigger(INPUT_ID::BTN_1))*/
	if (_input->state(INPUT_ID::BTN_1).first &&
	  !(_input->state(INPUT_ID::BTN_1).second))
	{
		for (int i = 0; i < _shots.size(); ++i)
		{
			if (_shots[i] == nullptr)
			{
				_shots[i] = std::make_shared<Shot>(_pos, Vector2d(0, -6));
				LpAudioMng.PlaySE("Music/shot.mp3");
				break;
			}
		}
	}

	/// 仮でﾃﾞﾊﾞｯｸﾞ用の描画をしている
	_dbgDrawBox(_rect.Left()  - _size.width / 2, _rect.Top()	- _size.height / 2,
				_rect.Right() - _size.width / 2, _rect.Bottom() - _size.height / 2, 0x00ff00, true);


	_dbgDrawFormatString(LpGame.gameScreenPos.x + _pos.x - _size.width - _size.width / 2, 
						 LpGame.gameScreenPos.y + _pos.y - _size.height, 
						 0xffffff, "(%d, %d)", (int)_pos.x, (int)(_pos.y));
}

const OBJ Player::GetObjID() const
{
	return OBJ::PLAYER;
}
