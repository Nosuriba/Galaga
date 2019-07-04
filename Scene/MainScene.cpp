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
	_ghGameScreen = MakeScreen(LpGame.gameScreenSize.x, LpGame.gameScreenSize.y, true);

	/// âºÇÃê∂ê¨
	objList.emplace_back(std::make_shared<Player>(Vector2f(100, 200), Vector2f(0,0)));
	objList.emplace_back(std::make_shared<Enemy>(Vector2f(20, 20), Vector2f(0,0)));
}

void MainScene::Draw()
{
	SetDrawScreen(_ghGameScreen);
	ClsDrawScreen();
	/// ÉvÉåÉCÉÑÅ[Ç∆ìGÇÃâºï`âÊ
	for (auto obj : objList)
	{
		obj->Object::Draw();

	}
	LpGame.AddDrawQue({ _ghGameScreen, LpGame.gameScreenPos.x, LpGame.gameScreenPos.y });
}

unique_scene MainScene::Update(unique_scene scene, const Input & p)
{
	/// ÉvÉåÉCÉÑÅ[Ç∆ìGÇÃâºï`âÊ
	for (auto obj : objList)
	{
		obj->Update();
	}

	Draw();

	DrawString(0, 0, "Main", 0xffffff);

	/*if (p.IsKeyTrigger(KEY_INPUT_SPACE))
	{
		return std::make_unique<ResultScene>();
	}
*/
	return std::move(scene);
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}
