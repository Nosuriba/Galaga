#include <DxLib.h>
#include "Enemy.h"

Enemy::Enemy()
{
	_imgHandle = DxLib::LoadGraph("image/enemy.png");
}

Enemy::~Enemy()
{
	DxLib::DeleteGraph(_imgHandle);
}

void Enemy::Draw()
{
	DxLib::DrawRectGraph(250, 250, 0, 0, charSize.x, charSize.y, _imgHandle, true, true);
}

void Enemy::Update()
{
}
