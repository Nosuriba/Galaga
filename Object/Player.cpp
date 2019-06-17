#include <DxLib.h>
#include "Player.h"

Player::Player()
{
	_imgHandle = DxLib::LoadGraph("image/player.png");
}

Player::~Player()
{
	DxLib::DeleteGraph(_imgHandle);
}

void Player::Draw()
{
	DxLib::DrawRectGraph(100,100,charSize.x,0, charSize.x, charSize.y, _imgHandle, true, true);
}

void Player::Update()
{
}
