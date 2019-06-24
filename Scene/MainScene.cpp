#include "../Game.h"
#include "MainScene.h"
#include "ResultScene.h"

#include "../Object/Object.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"
#include "../Common/ImageMng.h"

MainScene::MainScene()
{
	Init();
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	/// 仮の生成
	objList.emplace_back(std::make_shared<Player>(Vector2f(500, 450), Vector2f(0, 0)));
	objList.emplace_back(std::make_shared<Enemy>(Vector2f(300, 300), Vector2f(0,0)));
}

void MainScene::Update(const Input & p)
{
	/// プレイヤーと敵の仮描画
	for (auto obj : objList)
	{
		obj->Draw();
		obj->Update(p);
	}

	DrawGraph(0, 0, ImageMng::GetInstance().GetID("image/frame.png"), true);
	DrawString(0, 0, "Main", 0xffffff);

	if (p.IsKeyTrigger(KEY_INPUT_F5))
	{
		Game::GetInstance().ChangeScene(new ResultScene());
	}
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}
