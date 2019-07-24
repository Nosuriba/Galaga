#include <algorithm>
#include <stdlib.h>	
#include <time.h>
#include "../Game.h"
#include "../DebugConOut.h"
#include "MainScene.h"
#include "ResultScene.h"

#include "../Object/Player.h"
#include "../Object/Bee.h"
#include "../Object/Butterfly.h"
#include "../Object/Scorpion.h"
#include "../Common/ImageMng.h"

MainScene::MainScene() : _charSize(30,32), _enMax(10, 5)
{
	_enCnt = 0;

	/// 敵のﾃｰﾌﾞﾙを生成している
	_enTblInfo.reserve(_enMax.x * _enMax.y);
	for (int i = 0; i < (_enMax.x * _enMax.y); ++i)
	{
		_enTblInfo.emplace_back(0);
	}
	/// 特定のﾃｰﾌﾞﾙには配置できないようにしている
	_enTblInfo[0] = 1;
	_enTblInfo[1] = 1;
	_enTblInfo[2] = 1;
	_enTblInfo[7] = 1;
	_enTblInfo[8] = 1;
	_enTblInfo[9] = 1;
	_enTblInfo[10] = 1;
	_enTblInfo[19] = 1;
	_enTblInfo[20] = 1;
	_enTblInfo[29] = 1;

	_enCnt = 10;

	/// 左端
	_initPos[0] = Vector2(0, _charSize.height);
	_initPos[1] = Vector2(0, LpGame.gameScreenSize.y / 2);
	_initPos[2] = Vector2(0, 
						   LpGame.gameScreenSize.y - _charSize.height * 2);
	/// 右端
	_initPos[3] = Vector2(LpGame.gameScreenSize.x, _charSize.height);
	_initPos[4] = Vector2(LpGame.gameScreenSize.x, 
						  LpGame.gameScreenSize.y / 2);
	_initPos[5] = Vector2(LpGame.gameScreenSize.x,
						  LpGame.gameScreenSize.y - _charSize.height * 2);

	/// 左端
	_enSpace[0] = Vector2(-_charSize.width, -_charSize.height);
	_enSpace[1] = Vector2(-_charSize.width, 0);
	_enSpace[2] = Vector2(-_charSize.width, _charSize.height);
	/// 右端
	_enSpace[3] = Vector2(_charSize.width, -_charSize.height);
	_enSpace[4] = Vector2(_charSize.width, 0);
	_enSpace[5] = Vector2(_charSize.width, _charSize.height);
	Init();
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	srand((unsigned int)time(0));

	_ghGameScreen = MakeScreen(LpGame.gameScreenSize.x, LpGame.gameScreenSize.y, true);

	/// 仮の生成
	_objs.emplace_back(std::make_shared<Player>(Vector2(100, LpGame.gameScreenSize.y - _charSize.height), _charSize));
}

void MainScene::AddEnemy(const int & line, const EnemyState & state)
{
	if (line == 0)
	{
		/// ボス敵
		_objs.emplace_back(std::make_shared<Scorpion>(state));
	}
	else if (line == 1 || line == 2)
	{
		/// 中間の敵
		_objs.emplace_back(std::make_shared<Butterfly>(state));
	}
	else
	{
		/// 雑魚
		_objs.emplace_back(std::make_shared<Bee>(state));
	}
}

void MainScene::Draw()
{
	SetDrawScreen(_ghGameScreen);
	ClsDrawScreen();
	for (auto obj : _objs)
	{
		if (obj != nullptr)
		{
			obj->Object::Draw();
		}
	}
	LpGame.AddDrawQue({ _ghGameScreen, LpGame.gameScreenPos.x, LpGame.gameScreenPos.y});
}

unique_scene MainScene::Update(unique_scene scene, const Input & p)
{
	_dbgKeyOld = _dbgKey;
	_dbgKey    = CheckHitKey(KEY_INPUT_SPACE);
	auto randNum = rand();

	if (_dbgKey && !_dbgKeyOld)
	{
		for (int cnt = 0; cnt < 5;)
		{
			/// 出現している敵が最大数を超えている時、処理を抜ける
			if (_enCnt >= (_enMax.x * _enMax.y))
			{
				break;
			}
			auto num = rand() % (_enMax.x * _enMax.y);
			if (!_enTblInfo[num])
			{
				/// 敵の情報設定
				auto invPos = Vector2((num % _enMax.x) * 5, (num / _enMax.x) * 5);
				auto aimPos = Vector2d(LpGame.gameScreenPos.x / 2 + ((num % _enMax.x) * _charSize.width) + invPos.x,
									   LpGame.gameScreenPos.y / 2 + ((num / _enMax.x) * _charSize.height) + invPos.y);
				auto space  = _enSpace[randNum % 6];
				
				/// 敵の生成
				auto line = num / _enMax.x;
				auto debugPos = Vector2d(200, 300);
				EnemyState state = { _initPos[randNum % 6] + space, _charSize, 
									 EN_TYPE::NORMAL, num, 10 * cnt, aimPos, debugPos};
				
				AddEnemy(line, state);
				++cnt;
				++_enCnt;
				_enTblInfo[num] = 1;
			}
		}
	}

	for (auto obj : _objs)
	{
		/// 最初に登録された敵のｱﾆﾒｰｼｮﾝｶｳﾝﾄを加算する処理
		if (obj->GetObjID() == Obj::ENEMY)
		{
			obj->LeadAnimUpdate();
			break;
		}
	}

	for (auto obj : _objs)
	{
		obj->Update();
		if (obj->GetDeath() && obj->GetObjID() == Obj::ENEMY)
		{
			_enTblInfo[obj->GetEnemyNum()] = 0;
			--_enCnt;
		}
	}

	Draw();

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