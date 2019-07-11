#include <algorithm>
#include <stdlib.h>	
#include "../Game.h"
#include "../DebugConOut.h"
#include "MainScene.h"
#include "ResultScene.h"

#include "../Object/Object.h"
#include "../Object/Player.h"
#include "../Common/ImageMng.h"

MainScene::MainScene()
{
	//// 後で位置は修正するようにしておく
	/// 左端
	_initPos[0] = Vector2(-LpGame.gameScreenPos.x, -LpGame.gameScreenPos.y);
	_initPos[1] = Vector2(-LpGame.gameScreenPos.x, LpGame.gameScreenSize.y / 2);
	_initPos[2] = Vector2(-LpGame.gameScreenPos.x, LpGame.gameScreenSize.y + LpGame.gameScreenPos.y / 2);
	
	/// 右端
	_initPos[3] = Vector2(LpGame.gameScreenSize.x + LpGame.gameScreenPos.x / 2 , -LpGame.gameScreenPos.y);
	_initPos[4] = Vector2(LpGame.gameScreenSize.x + LpGame.gameScreenPos.x / 2, 
						  LpGame.gameScreenSize.y / 2);
	_initPos[5] = Vector2(LpGame.gameScreenSize.x + LpGame.gameScreenPos.x / 2,
						  LpGame.gameScreenSize.y + LpGame.gameScreenPos.y / 2);
	Init();
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	_ghGameScreen = MakeScreen(LpGame.gameScreenSize.x, LpGame.gameScreenSize.y, true);

	/// 仮の生成
	_objs.emplace_back(std::make_shared<Player>(Vector2(100, 200)));
	// SetEnemy();
}

void MainScene::SetEnemy()
{
	int offset = 100;
	AddEnemy(Vector2(offset + 120, 200), EN_TYPE::BOSS);
	TRACE("%d体目の敵を生成\n", (int)_objs.size() - 1);
	for (int i = 0; i < 9; ++i)
	{
		AddEnemy(Vector2(offset + 80 + (40 * (i % 3)), 160 - (40 * (i / 3))), EN_TYPE::BONUS);
		TRACE("%d体目の敵を生成\n", (int)_objs.size() - 1);
	}
}

void MainScene::AddEnemy(const Vector2& pos, EN_TYPE type)
{
	_objs.emplace_back(std::make_shared<Enemy>(pos, type));
}

void MainScene::Draw()
{
	SetDrawScreen(_ghGameScreen);
	ClsDrawScreen();
	/// プレイヤーと敵の仮描画
	for (auto obj : _objs)
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
	static int dbgCnt = 0;
	_dbgKeyOld = _dbgKey;
	_dbgKey    = CheckHitKey(KEY_INPUT_SPACE);

	if (_dbgKey && !_dbgKeyOld)
	{
		if (dbgCnt <= 5)
		{
			AddEnemy(_initPos[dbgCnt], EN_TYPE::NORMAL);
			dbgCnt++;
		}
		
	}

	/// プレイヤーと敵の仮描画
	for (auto obj : _objs)
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

	/// vectorの削除する範囲の指定
	auto eraseBegin = remove_if(_objs.begin(),				// 開始位置
								_objs.end(),				// 終了位置
							    [](std::shared_ptr<Object>& obj) {return (*obj).GetDeath(); });		// moveするかの判定部

	/// 指定した範囲のvectorを削除している
	_objs.erase(eraseBegin, _objs.end());
	return std::move(scene);
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}