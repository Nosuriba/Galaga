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
	/// âºÇÃê∂ê¨
	objList.emplace_back(std::make_shared<Player>(Vector2f(500, 450), Vector2f(0, 0)));
	objList.emplace_back(std::make_shared<Enemy>(Vector2f(300, 300), Vector2f(0,0)));

	SET_IMAGE_ID("bg", "image/frame.png");
}

void MainScene::Update(const Input & p)
{
	/// ÉvÉåÉCÉÑÅ[Ç∆ìGÇÃâºï`âÊ
	for (auto obj : objList)
	{
		obj->Object::Draw();
		obj->Update(p);
	}

	DrawGraph(0, 0, IMAGE_ID("bg")[0], true);
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
