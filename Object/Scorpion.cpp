#include "Scorpion.h"

Scorpion::Scorpion()
{
}

Scorpion::Scorpion(const EnemyState & state)
{
	_size = std::get<static_cast<int>(EN_STATE::SIZE)>(state);
	auto center = Vector2(std::get<static_cast<int>(EN_STATE::POS)>(state).x + _size.width / 2,
						  std::get<static_cast<int>(EN_STATE::POS)>(state).y + _size.height / 2);
	_pos	= Vector2d(center.x, center.y);
	_vel	= Vector2d();
	_rect	= Rect(center, _size);
	_ePos	= std::get<static_cast<int>(EN_STATE::SIGPOS)>(state);;
	_aimPos = std::get<static_cast<int>(EN_STATE::AIM)>(state);
	_rad = 0.0;
	Init(std::get<static_cast<int>(EN_STATE::TYPE)>(state));

	SetEnemyNum(std::get<static_cast<int>(EN_STATE::NUM)>(state));
	animKey(ANIM::NORMAL);

	Sigmoid();
}

Scorpion::~Scorpion()
{
	TRACE("Scorpion Die!!\n");
}

void Scorpion::Init(EN_TYPE type)
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
	/// ±ÆÒ°¼®Ý‚ÌI—¹ˆÊ’u‚ðÝ’è‚µ‚Ä‚¢‚é
	data.emplace_back(-1, 60);

	SetAnim(ANIM::DEATH, data);
}
