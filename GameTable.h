#pragma once
#include <array>
#include "Vector2.h"

class Enemy;

class GameTable
{
public:
	GameTable();
	~GameTable();
	std::shared_ptr<Enemy> SetEnemy(const Vector2& pos);
	void MoveTable();
private:

	std::array<Vector2, 6> _initPos;	// “G‚Ì‰ŠúÀ•W
	std::array<Vector2, 6> _enSpece;	// “G‚ÌŠÔŠu
};

