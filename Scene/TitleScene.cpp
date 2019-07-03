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

unique_scene TitleScene::Update(unique_scene scene, const Input & p)
{
	DrawString(0, 0, "Title", 0xffffff);
	if (p.IsKeyTrigger(KEY_INPUT_SPACE))
	{
		return std::make_unique<MainScene>();
	}
	return std::move(scene);
}

const SCN_ID TitleScene::GetSceneID() const
{
	return SCN_ID::TITLE;
}
