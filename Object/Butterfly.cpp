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

	animKey(ANIM::NORMAL);

}

Butterfly::~Butterfly()
{
	TRACE("Butterfly Die!! \n");
}

int Butterfly::Target()
{
	if (_isTable)
	{
		_pos = Vector2d(LpGame.gameScreenSize.x / 2 + _spLength.x, -_size.height * 3);
	}

	CalRad(_pos, _aimPos + Vector2d(_moveTblInfo.first, 0), 90);
	auto theta = atan2(_aimPos.y - _pos.y, _aimPos.x - _pos.x);
	auto cost = cos(theta);
	auto sint = sin(theta);
	_vel	  = Vector2d(3 * cost, 3 * sint);
	_updater = &Enemy::TargetUpdate;

	return 0;
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

void Butterfly::SetSigEnd(const Vector2d& sigEnd)
{
	if (_moveList.size() == 0 && 
		_actionCnt < 2 && 
		_spVel != 0)
	{
 		++_actionCnt;
		_sigEnd = sigEnd + Vector2d(0, _size.height * 2);
		_gain = 0.3;
		_sigAdd = 0.2;
		Rotation();
		_isAction = true;
		_moveList.emplace_back(&Enemy::Sigmoid);
		_moveList.emplace_back(&Enemy::Target);
	}
}

