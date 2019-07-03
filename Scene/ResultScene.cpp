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
unique_scene ResultScene::Update(unique_scene scene, const Input & p)
{
	DrawString(0, 0, "Result", 0xffffff);
	if (p.IsKeyTrigger(KEY_INPUT_SPACE))
	{
		return std::make_unique<TitleScene>();
	}
	return std::move(scene);
}

const SCN_ID ResultScene::GetSceneID() const
{
	return SCN_ID::RESULT;
}
