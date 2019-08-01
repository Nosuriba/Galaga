#include "Butterfly.h"

Butterfly::Butterfly()
{
}

Butterfly::Butterfly(const EnemyState & state)
{
	_size = std::get<static_cast<int>(EN_STATE::SIZE)>(state);
	auto center = Vector2(std::get<static_cast<int>(EN_STATE::POS)>(state).x + _size.width / 2,
						  std::get<static_cast<int>(EN_STATE::POS)>(state).y + _size.height / 2);
	_pos	= Vector2d(center.x, center.y);
	_vel	= Vector2d();
	_rect	= Rect(center, _size);
	_aimPos = std::get<static_cast<int>(EN_STATE::AIM)>(state);
	_rad = 0.0;
	_gain = 1.0;
	_sigEnd   = std::get<static_cast<int>(EN_STATE::SIGPOS)>(state);
	_waitTime = std::get<static_cast<int>(EN_STATE::WAIT)>(state);

	Init(std::get<static_cast<int>(EN_STATE::TYPE)>(state));

	_enNum = std::get<static_cast<int>(EN_STATE::NUM)>(state);
	animKey(ANIM::NORMAL);

}

Butterfly::~Butterfly()
{
	TRACE("Butterfly Die!! \n");
}

void Butterfly::Init(EN_TYPE type)
{
	anim_vec data;
	auto enType = static_cast<int>(type) * 2;

	data.emplace_back(IMAGE_ID("enemy")[10 + enType], 30);
	data.emplace_back(IMAGE_ID("enemy")[11 + enType], 60);
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


int Butterfly::MoveUpdate()
{
	AnimUpdate(1);
	_pos.x += _moveTblInfo.second;
	_sigBegin = _pos;

	/// 回転, ｼｸﾞﾓｲﾄﾞ, 目標地点, 
	return 0;
}

void Butterfly::SetMoveInfo(const Vector2d& sigEnd)
{
	if (_moveList.size() == 0 && _actionCnt < 2)
	{
 		++_actionCnt;
		_sigEnd = sigEnd;
		_gain = 0.5;
		_sigAdd = 0.2;
		Rotation();
		_moveList.emplace_back(&Enemy::Sigmoid);
		_moveList.emplace_back(&Enemy::Target);
	}
}

