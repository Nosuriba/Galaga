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
	_dbgKeyTbl[0] = KEY_INPUT_NUMPAD0;
	_dbgKeyTbl[1] = KEY_INPUT_NUMPAD1;
	_dbgKeyTbl[2] = KEY_INPUT_NUMPAD2;
	_dbgKeyTbl[3] = KEY_INPUT_NUMPAD3;
	_dbgKeyTbl[4] = KEY_INPUT_NUMPAD4;
	_dbgKeyTbl[5] = KEY_INPUT_NUMPAD5;
	_dbgKeyTbl[6] = KEY_INPUT_NUMPAD6;
	_dbgKeyTbl[7] = KEY_INPUT_NUMPAD7;
	_dbgKeyTbl[8] = KEY_INPUT_NUMPAD8;
	_dbgKeyTbl[9] = KEY_INPUT_NUMPAD9;

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
	_objVector[1]->SetKey(_dbgKeyTbl[0]);
	for (int i = 0; i < 9; ++i)
	{
		TRACE("%d体目の敵を生成\n", _objVector.size());
		_objVector.emplace_back(std::make_shared<Enemy>(Vector2(offset + 80 + (40 * (i % 3)), 160 - (40 * (i / 3)))));
		_objVector[i + 2]->SetKey(_dbgKeyTbl[i + 1]);
	}

}


void MainScene::Draw()
{
	SetDrawScreen(_ghGameScreen);
	ClsDrawScreen();
	/// プレイヤーと敵の仮描画
	for (auto obj : _objVector)
	{
		if (obj != nullptr)
		{
			obj->Object::Draw();
		}
		

	}
	LpGame.AddDrawQue({ _ghGameScreen, LpGame.gameScreenPos.x, LpGame.gameScreenPos.y });
}

unique_scene MainScene::Update(unique_scene scene, const Input & p)
{
	/// プレイヤーと敵の仮描画
	for (auto obj : _objVector)
	{
		if (obj != nullptr)
		{
			obj->Update();
		}
		
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

	/// vectorの中身を空にするかの処理
	auto obj = _objVector.begin();
	for (;obj != _objVector.end();)
	{

		/// 敵が死亡していた時、中身を空にする
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