#include <DxLib.h>
#include "../Game.h"
#include "TitleScene.h"
#include "MainScene.h"

TitleScene::TitleScene()
{
	Init();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
}

void TitleScene::Update(const Input & p)
{
	if (p.IsTrigger(PAD_INPUT_10))
	{
		Game::GetInstance().ChangeScene(new MainScene());
		return;
	}
}
