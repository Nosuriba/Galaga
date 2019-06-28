#include "../Game.h"
#include "TitleScene.h"
#include "ResultScene.h"

ResultScene::ResultScene()
{
}


ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
}

void ResultScene::Update(const Input & p)
{
	DrawString(0, 0, "Result", 0xffffff);
	if (p.IsKeyTrigger(KEY_INPUT_SPACE))
	{
		Game::GetInstance().ChangeScene(new TitleScene());
	}
}

const SCN_ID ResultScene::GetSceneID() const
{
	return SCN_ID::RESULT;
}
