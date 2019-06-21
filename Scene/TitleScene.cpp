#include "../Game.h"
#include "TitleScene.h"
#include "MainScene.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
}

void TitleScene::Update(const Input & p)
{
	DrawString(0, 0, "Title", 0xffffff);
	if (p.IsKeyTrigger(KEY_INPUT_F5))
	{
		Game::GetInstance().ChangeScene(new MainScene());
	}
}

const SCN_ID TitleScene::GetSceneID() const
{
	return SCN_ID::TITLE;
}
