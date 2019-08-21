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

void Player::Idle(const std::unique_ptr<InputState>& p)
{
	_updater = &Player::IdleUpdate;
}

void Player::Die(const std::unique_ptr<InputState>& p)
{
	animKey(ANIM::DEATH);
	_updater = &Player::DieUpdate;
}

void Player::Move(const std::unique_ptr<InputState>& p)
{
	_updater = &Player::MoveUpdate;
}

void Player::IdleUpdate(const std::unique_ptr<InputState>& p)
{
	if (p->IsPressing(INPUT_ID::RIGHT) ||
		p->IsPressing(INPUT_ID::LEFT))
	{
		Move(p);
	}
}

void Player::MoveUpdate(const std::unique_ptr<InputState>& p)
{
	if (p->IsPressing(INPUT_ID::RIGHT))
	{
		_pos.x += 4;
	}
	else if (p->IsPressing(INPUT_ID::LEFT))
	{
		_pos.x -= 4;
	}
	else
	{
		Idle(p);
	}
}

void Player::DieUpdate(const std::unique_ptr<InputState>& p)
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

void Player::Update(const std::unique_ptr<InputState>& p)
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
	(this->*_updater)(p);
	
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
	if (p->IsTrigger(INPUT_ID::BTN_1))
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
