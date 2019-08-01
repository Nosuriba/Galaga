#pragma once
#include "Vector2.h"

struct ShotInfo
{
	Vector2d _pos;
	Vector2d _vel;
	Size _size;
	Rect _rect;

	bool flag;

	ShotInfo() : _pos(0, 0), _vel(0, 0), _size(0, 0) {};
	ShotInfo(const Vector2d& pos, const Vector2d& vel, const Size& size)
	{
		_pos = pos;
		_vel = vel;
		_size = size;
	}
};

class Shot
{
public:
	Shot();
	Shot(const Vector2d& pos, const Vector2d& vel);
	~Shot();

	bool IsOutScreen() const;
	void Update();
	void Draw(const int& id);
	const Rect GetRect() const;
private:
	/// structÇ≈ï™ÇØÇÈïKóvê´Ç™Ç»Ç¢Ç©Ç‡ÇµÇÍÇ»Ç¢
	ShotInfo _shot;

	const Size _shotSize;
};

