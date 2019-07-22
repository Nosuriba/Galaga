#include <algorithm>
#include <stdlib.h>	
#include <time.h>
#include "../Game.h"
#include "../DebugConOut.h"
#include "MainScene.h"
#include "ResultScene.h"

#include "../Object/Object.h"
#include "../Object/Player.h"
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
	/*_enTblInfo[0] = 1;
	_enTblInfo[1] = 1;
	_enTblInfo[8] = 1;
	_enTblInfo[9] = 1;
	_enTblInfo[10] = 1;
	_enTblInfo[19] = 1;
	_enTblInfo[20] = 1;
	_enTblInfo[29] = 1;*/

	/// 敵の移動方向の設定
	_dirInfo.resize(6);
	for (int i = 0; i < _dirInfo.size(); ++i)
	{
		_dirInfo[i].resize(2);
	}
	DecideDir();

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
	_objs.emplace_back(std::make_shared<Player>(Vector2(100, 200), _charSize));
}

void MainScene::AddEnemy(const EnemyState& state)
{
	_objs.emplace_back(std::make_shared<Enemy>(state));
}

void MainScene::DecideDir()
{
	_dirInfo[0][0] = 0;
	_dirInfo[0][1] = 0;

	_dirInfo[1][0] = 1;
	_dirInfo[1][1] = 0;

	_dirInfo[2][0] = 0;
	_dirInfo[2][1] = 1;

	_dirInfo[3][0] = 3;
	_dirInfo[3][1] = 3;

	_dirInfo[4][0] = 2;
	_dirInfo[4][1] = 3;

	_dirInfo[5][0] = 3;
	_dirInfo[5][1] = 2;
	
}

EN_ID MainScene::SetID(const int & num)
{
	auto line = num / _enMax.x;
	if (line == 0)
	{
		return EN_ID::SCORPION;
	}
	else if (line == 1 || line == 2)
	{
		return EN_ID::BUTTERFLY;
	}
	else
	{
		return EN_ID::BEE;
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
		/// 一体ずつ出しているので、for文を使わないような処理を書くようにする
		for (int cnt = 0; cnt < 1;)
		{
			/// 出現している敵が最大数を超えている時、処理を抜ける
			if (_enCnt >= (_enMax.x * _enMax.y))
			{
				break;
			}
			auto num = rand() % (_enMax.x * _enMax.y);
			if (!_enTblInfo[num])
			{
				auto invPos = Vector2((num % _enMax.x) * 5, (num / _enMax.x) * 5);
				auto aimPos = Vector2d(LpGame.gameScreenPos.x / 2 + ((num % _enMax.x) * _charSize.width) + invPos.x,
									   LpGame.gameScreenPos.y / 2 + ((num / _enMax.x) * _charSize.height) + invPos.y);
				auto space = _enSpace[randNum % 6] + (_enSpace[randNum % 6] * cnt);
				
				/// ﾗﾝﾀﾞﾑで敵を出現させるようにしている
				//auto type = (EN_TYPE)(randNum % static_cast<int>(EN_TYPE::MAX));
				
				AddEnemy({ _initPos[randNum % 6] + space, _charSize, EN_TYPE::NORMAL, SetID(num), aimPos, num, _dirInfo[randNum % 6] });

				/// 特定の位置から出ているかの確認用(疲れた時はたまに見て楽しもう)
				// AddEnemy({ _initPos[2], _charSize, type, id, aimPos, num, _dirInfo[2] });
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