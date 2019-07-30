#include "Boss.h"

Boss::Boss()
{
}

Boss::Boss(const EnemyState & state)
{
	_size = std::get<static_cast<int>(EN_STATE::SIZE)>(state);
	auto center = Vector2(std::get<static_cast<int>(EN_STATE::POS)>(state).x + _size.width / 2,
						  std::get<static_cast<int>(EN_STATE::POS)>(state).y + _size.height / 2);
	_pos	= Vector2d(center.x, center.y);
	_rect	= Rect(center, _size);

	_vel	= Vector2d();
	_sigEnd	= std::get<static_cast<int>(EN_STATE::SIGPOS)>(state);;
	_aimPos = std::get<static_cast<int>(EN_STATE::AIM)>(state);
	_rad	= 0.0;
	_waitCnt = std::get<static_cast<int>(EN_STATE::WAIT)>(state);
	Init(std::get<static_cast<int>(EN_STATE::TYPE)>(state));

	_enNum = std::get<static_cast<int>(EN_STATE::NUM)>(state);
	animKey(ANIM::NORMAL);

}

Boss::~Boss()
{
	TRACE("Boss Die!!\n");
}

void Boss::Update()
{
	if (DestryCheck())
	{
		return;
	}
	(this->*_updater)();
	_pos += _vel;

	auto center = Vector2(_pos.x + _size.width / 2, _pos.y + _size.height / 2);
	_rect = Rect(center, _size);

	/// debug用で敵を削除している
	old = now;
	now = CheckHitKey(KEY_INPUT_C);

	if (now && !old)
	{
		animKey(ANIM::DEATH);
		_isAlive = false;
		ResetInvCnt();
	}

	/// ﾃﾞﾊﾞｯｸﾞ用の描画
	//if (_updater == &Enemy::RotationUpdate)
	//{
	//	_dbgDrawCircle(_rotCenter.x, _rotCenter.y, 5, 0x00ff00, true);
	//}
	//_dbgDrawBox(_rect.Left() - _size.width / 2, _rect.Top() - _size.height / 2,
	//	_rect.Right() - _size.width / 2, _rect.Bottom() - _size.height / 2, 0xff0000, true);
}

void Boss::Init(EN_TYPE type)
{
	anim_vec data;
	auto enType = static_cast<int>(type) * 2;

	data.emplace_back(IMAGE_ID("enemy")[20 + enType], 30);
	data.emplace_back(IMAGE_ID("enemy")[21 + enType], 60);
	SetAnim(ANIM::NORMAL, data);

	data.emplace_back(IMAGE_ID("en_blast")[0], 15);
	for (int i = 1; i < 5; ++i)
	{
		data.emplace_back(IMAGE_ID("en_blast")[i], 15 + (5 * i));
	}
	/// ｱﾆﾒｰｼｮﾝの終了位置を設定している
	data.emplace_back(-1, 60);

	SetAnim(ANIM::DEATH, data);
}
