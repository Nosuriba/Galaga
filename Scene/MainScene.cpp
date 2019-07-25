#include <algorithm>
#include <stdlib.h>	
#include <time.h>				/// ×İÀŞÑ¶¬‚ğ‚â‚ß‚½A‚¢‚¸‚êÁ‚·‚©‚à‚µ‚ê‚È‚¢
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

	/// “G‚ÌÃ°ÌŞÙ‚ğ¶¬‚µ‚Ä‚¢‚é
	_enTblInfo.reserve(_enMax.x * _enMax.y);
	for (int i = 0; i < (_enMax.x * _enMax.y); ++i)
	{
		_enTblInfo.emplace_back(0);
	}
	/// “Á’è‚ÌÃ°ÌŞÙ‚É‚Í”z’u‚Å‚«‚È‚¢‚æ‚¤‚É‚µ‚Ä‚¢‚é
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

	_posLD = Vector2d(LpGame.gameScreenPos.x / 2,
					  LpGame.gameScreenPos.y / 2 + (_enMax.y - 1) * _charSize.height);

	/// ¶’[
	_initPos[0] = Vector2(-_charSize.width, _charSize.height);
	_initPos[1] = Vector2(-_charSize.width, LpGame.gameScreenSize.y / 2);
	_initPos[2] = Vector2(-_charSize.width, LpGame.gameScreenSize.y - _charSize.height * 2);
	/// ‰E’[
	_initPos[3] = Vector2(LpGame.gameScreenSize.x, _charSize.height);
	_initPos[4] = Vector2(LpGame.gameScreenSize.x, 
						  LpGame.gameScreenSize.y / 2);
	_initPos[5] = Vector2(LpGame.gameScreenSize.x,
						  LpGame.gameScreenSize.y - _charSize.height * 2);
	Init();
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	srand((unsigned int)time(0));

	_ghGameScreen = MakeScreen(LpGame.gameScreenSize.x, LpGame.gameScreenSize.y, true);

	/// ÌßÚ²Ô°‚Ì¶¬
	_objs.emplace_back(std::make_shared<Player>(Vector2(100, LpGame.gameScreenSize.y - _charSize.height), _charSize));
}

void MainScene::AddEnemy(const int & line, const EnemyState & state)
{
	if (line == 0)
	{
		/// »¿Ø‚Ì¶¬
		_objs.emplace_back(std::make_shared<Scorpion>(state));
	}
	else if (line == 1 || line == 2)
	{
		/// ’±‚Ì¶¬
		_objs.emplace_back(std::make_shared<Butterfly>(state));
	}
	else
	{
		/// –I‚Ì¶¬
		_objs.emplace_back(std::make_shared<Bee>(state));
	}
}

void MainScene::Draw()
{
	/// ¹Ş°Ñ½¸Ø°İ‚Ì•`‰æ‚ğs‚Á‚Ä‚¢‚é
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
	/// “G‚ğ‰¼¶¬‚·‚é‚½‚ß‚Ìİ’è
	_dbgKeyOld = _dbgKey;
	_dbgKey    = CheckHitKey(KEY_INPUT_SPACE);

	auto randNum = rand();

	/// “G‚Ì¶¬(‰¼‚Å¶¬‚µ‚Ä‚¢‚é)
	if (_dbgKey && !_dbgKeyOld)
	{
		for (int cnt = 0; cnt < 3;)
		{
			/// oŒ»‚µ‚Ä‚¢‚é“G‚ªÅ‘å”‚ğ’´‚¦‚Ä‚¢‚éAˆ—‚ğ”²‚¯‚é
			if (_enCnt >= (_enMax.x * _enMax.y))
			{
				break;
			}
			auto num = rand() % (_enMax.x * _enMax.y);
			if (!_enTblInfo[num])
			{
				/// “G‚Ìî•ñİ’è
				auto invPos = Vector2((num % _enMax.x) * 5, (num / _enMax.x) * 5);
				auto aimPos = Vector2d(LpGame.gameScreenPos.x / 2 + ((num % _enMax.x) * _charSize.width) + invPos.x,
									   LpGame.gameScreenPos.y / 2 + ((num / _enMax.x) * _charSize.height) + invPos.y);
				
				/// “G‚Ì¶¬
				auto line = num / _enMax.x;
				auto debugPos = Vector2d(200, 300);
				EnemyState state = { _initPos[randNum % 6], _charSize, 
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
		/// Å‰‚É“o˜^‚³‚ê‚½“G‚Ì±ÆÒ°¼®İ¶³İÄ‚ğ‰ÁZ‚·‚éˆ—
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
			/// ÃŞÊŞ¯¸Ş’†‚Ì‚½‚ßA“G‚ª€–S‚µ‚½ˆÊ’u‚ÉÄ¶¬‚Å‚«‚é‚æ‚¤‚É‚µ‚Ä‚¢‚é
			_enTblInfo[obj->GetEnemyNum()] = 0;
			--_enCnt;
		}
	}

	_dbgDrawBox(_posLD.x, _posLD.y, _posLD.x + _charSize.width, _posLD.y + _charSize.height, 0xffff00, true);

	Draw();

	/*if (p.IsKeyTrigger(KEY_INPUT_SPACE))
	{
		return std::make_unique<ResultScene>();
	}*/
	/// vector‚Ìíœ‚·‚é”ÍˆÍ‚Ìw’è
	auto eraseBegin = remove_if(_objs.begin(),				// ŠJnˆÊ’u
								_objs.end(),				// I—¹ˆÊ’u
							    [](std::shared_ptr<Object>& obj) {return (*obj).GetDeath(); });		// move‚·‚é‚©‚Ì”»’è•”

	/// w’è‚µ‚½”ÍˆÍ‚Ìvector‚ğíœ‚µ‚Ä‚¢‚é
	_objs.erase(eraseBegin, _objs.end());
	return std::move(scene);
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}