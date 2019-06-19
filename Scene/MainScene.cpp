#include "../Game.h"
#include "MainScene.h"
#include "ResultScene.h"

/// 仮描画をするためにファイルを追加したので後で消す
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
	objs.push_back(std::make_shared<Player>(Vector2f(500, 400), Vector2f(0, 0)));
	objs.push_back(std::make_shared<Enemy>(Vector2f(300, 300), Vector2f(0,0)));
}

void MainScene::Update(const Input & p)
{
	/// プレイヤーと敵の仮描画
	for (auto obj : objs)
	{
		obj->Draw();
		obj->Update(p);
	}

	DrawString(0, 0, "Main", 0xffffff);
	DrawGraph(0, 0, ImageMng::GetInstance().GetID("image/frame.png"), true);
	if (p.IsKeyTrigger(KEY_INPUT_SPACE))
	{
		Game::GetInstance().ChangeScene(new ResultScene());
	}
}
