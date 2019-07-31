#include "Bee.h"

Bee::Bee()
{
}

Bee::Bee(const EnemyState & state)
{
	_size = std::get<static_cast<int>(EN_STATE::SIZE)>(state);
	auto center = Vector2(std::get<static_cast<int>(EN_STATE::POS)>(state).x + _size.width / 2,
						  std::get<static_cast<int>(EN_STATE::POS)>(state).y + _size.height / 2);
	_pos = Vector2d(center.x, center.y);
	_vel = Vector2d();
	_rect = Rect(center, _size);
	_aimPos = std::get<static_cast<int>(EN_STATE::AIM)>(state);
	_rad = 0.0;
	_waitTime = std::get<static_cast<int>(EN_STATE::WAIT)>(state);

	Init(std::get<static_cast<int>(EN_STATE::TYPE)>(state));

	_enNum = std::get<static_cast<int>(EN_STATE::NUM)>(state);
	animKey(ANIM::NORMAL);

}

Bee::~Bee()
{
	TRACE("Bee Die!! \n");
}

void Bee::Init(EN_TYPE type)
{
	anim_vec data;
	auto enType = static_cast<int>(type) * 2;

	data.emplace_back(IMAGE_ID("enemy")[0 + enType], 30);
	data.emplace_back(IMAGE_ID("enemy")[1 + enType], 60);
	SetAnim(ANIM::NORMAL, data);

	data.emplace_back(IMAGE_ID("en_blast")[0], 15);
	for (int i = 1; i < 5; ++i)
	{
		data.emplace_back(IMAGE_ID("en_blast")[i], 15 + (5 * i));
	}
	/// ±∆“∞ºÆ›ÇÃèIóπà íuÇê›íËÇµÇƒÇ¢ÇÈ
	data.emplace_back(-1, 60);

	SetAnim(ANIM::DEATH, data);
}


int Bee::MoveUpdate()
{
	AnimUpdate(1);
	_pos.x += _moveTblInfo.second;
	_sigBegin = _pos;

	/// âºÇÃìoò^
	if (_waitAction < 0)
	{
		Rotation();
		_gain = 0.3;
		_moveList.emplace_back(&Enemy::Sigmoid);
		_moveList.emplace_back(&Enemy::Rotation);
		_moveList.emplace_back(&Enemy::Target);
	}
	--_waitAction;
	return 0;
}

void Bee::Update()
{
	if (DestryCheck())
	{
		AnimUpdate(1);
		return;
	}
	(this->*_updater)();
	_pos += _vel;

	auto center = Vector2(_pos.x + _size.width / 2, _pos.y + _size.height / 2);
	_rect = Rect(center, _size);

	/// debugópÇ≈ìGÇçÌèúÇµÇƒÇ¢ÇÈ
	old = now;
	now = CheckHitKey(KEY_INPUT_C);

	if (now && !old)
	{
		animKey(ANIM::DEATH);
		_isAlive = false;
		ResetInvCnt();
	}
}