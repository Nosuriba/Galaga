#include <DxLib.h>
#include "../Game.h"
#include "ResultScene.h"
#include "TitleScene.h"

ResultScene::ResultScene()
{
	Init();
}


ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
}

void ResultScene::Update(const Input & p)
{
	if (p.IsTrigger(PAD_INPUT_10))
	{
		Game::GetInstance().ChangeScene(new TitleScene());
		return;
	}
}
