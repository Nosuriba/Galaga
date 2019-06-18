#include <DxLib.h>
#include "Enemy.h"
#include "../ImageMng.h"

Enemy::Enemy()
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(const Input& p)
{
}

void Enemy::Draw()
{
	DxLib::DrawRectGraph(250, 250, 0, 0, charSize.x, charSize.y,
						 ImageMng::GetInstance().GetID("image/enemy.png"), true, true);
}
