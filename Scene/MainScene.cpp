#include <DxLib.h>
#include "../Game.h"
#include "MainScene.h"
#include "ResultScene.h"

MainScene::MainScene()
{
	Init();
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
}

void MainScene::Update(const Input & p)
{	
	if (p.IsTrigger(PAD_INPUT_10))
	{
		Game::GetInstance().ChangeScene(new ResultScene());
		return;
	}

}
