#include "../Game.h"
#include "../DebugConOut.h"
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

	/// 仮の生成
	_objVector.emplace_back(std::make_shared<Player>(Vector2(100, 200)));
	SetEnemy();
}

void MainScene::SetEnemy()
{
	int offset = 100;
	TRACE("%d体目の敵を生成\n", _objVector.size());
	_objVector.emplace_back(std::make_shared<Enemy>(Vector2(offset + 120, 200)));

	for (int i = 0; i < 9; ++i)
	{
		TRACE("%d体目の敵を生成\n", _objVector.size());
		_objVector.emplace_back(std::make_shared<Enemy>(Vector2(offset + 80 + (40 * (i % 3)), 160 - (40 * (i / 3)))));
	}

}


void MainScene::Draw()
{
	SetDrawScreen(_ghGameScreen);
	ClsDrawScreen();
	/// プレイヤーと敵の仮描画
	for (auto obj : _objVector)
	{
		obj->Object::Draw();

	}
	LpGame.AddDrawQue({ _ghGameScreen, LpGame.gameScreenPos.x, LpGame.gameScreenPos.y });
}

unique_scene MainScene::Update(unique_scene scene, const Input & p)
{
	/// プレイヤーと敵の仮描画
	for (auto obj : _objVector)
	{
		obj->Update();
	}

	Draw();
	DrawString(0, 0, "Main", 0xffffff);

	/*if (p.IsKeyTrigger(KEY_INPUT_SPACE))
	{
		return std::make_unique<ResultScene>();
	}*/

	/// 削除処理はメインシーン側で書くようにする
	/// テンキーで押した位置の敵を削除する処理はどうしようかな
	/// ﾎﾞﾀﾝの設定を簡単にまとめられたらいいけどな
	/// 
	if (CheckHitKey(KEY_INPUT_NUMPAD2))
	{
		_objVector[2]->SetAlive(false);
	}

	auto obj = _objVector.begin();
	for (;obj != _objVector.end();)
	{
		auto cnt = obj - _objVector.begin();
		if (!(*obj)->GetAlive())
		{
			obj = _objVector.erase(obj);
			continue;
		}
		++obj;
	}
	

	return std::move(scene);
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}