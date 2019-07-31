#pragma once
#include "Vector2.h"
class Shot
{
public:
	Shot();
	Shot(const Vector2d& pos);
	~Shot();

	bool ShotCheck() const;
	void SetShot(const Vector2d& pos);
	void Update();
	void Draw();
private:
	Vector2d _pos;
	Vector2d _vel;
	Rect _rect;

	bool _isShot;		// true : 打っている, false : 打っていない

	const Size _shotSize = Size(20,20);
};

