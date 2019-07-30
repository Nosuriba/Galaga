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
	_sigEnd	= std::get<static_cast<int>(EN_STATE::SIGPOS)>(state);
	_aimPos = std::get<static_cast<int>(EN_STATE::AIM)>(state);
	_rad = 0.0;
	_waitCnt = std::get<static_cast<int>(EN_STATE::WAIT)>(state);

	Init(std::get<static_cast<int>(EN_STATE::TYPE)>(state));

	_enNum = std::get<static_cast<int>(EN_STATE::NUM)>(state);
	animKey(ANIM::NORMAL);

}

Butterfly::~Butterfly()
{
	TRACE("Butterfly Die!! \n");
}

void Butterfly::Update()
{
	if (DestryCheck())
	{
		return;
	}
	(this->*_updater)();
	_pos += _vel;

	auto center = Vector2(_pos.x + _size.width / 2, _pos.y + _size.height / 2);
	_rect = Rect(center, _size);

	/// debug—p‚Å“G‚ğíœ‚µ‚Ä‚¢‚é
	old = now;
	now = CheckHitKey(KEY_INPUT_C);

	if (now && !old)
	{
		animKey(ANIM::DEATH);
		_isAlive = false;
		ResetInvCnt();
	}
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
	/// ±ÆÒ°¼®İ‚ÌI—¹ˆÊ’u‚ğİ’è‚µ‚Ä‚¢‚é
	data.emplace_back(-1, 60);

	SetAnim(ANIM::DEATH, data);
}
