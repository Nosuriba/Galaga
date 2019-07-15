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

MainScene::MainScene() : _charSize(30,32)
{
	_enCnt = 0;

	/// ���[
	_initPos[0] = Vector2(-LpGame.gameScreenPos.x, -LpGame.gameScreenPos.y);
	_initPos[1] = Vector2(-LpGame.gameScreenPos.x, LpGame.gameScreenSize.y / 2);
	_initPos[2] = Vector2(-LpGame.gameScreenPos.x, 
						   LpGame.gameScreenSize.y + LpGame.gameScreenPos.y - _charSize.height);
	/// �E�[
	_initPos[3] = Vector2(LpGame.gameScreenSize.x + LpGame.gameScreenPos.x - _charSize.width,
						 -LpGame.gameScreenPos.y);
	_initPos[4] = Vector2(LpGame.gameScreenSize.x + LpGame.gameScreenPos.x - _charSize.width, 
						  LpGame.gameScreenSize.y / 2);
	_initPos[5] = Vector2(LpGame.gameScreenSize.x + LpGame.gameScreenPos.x - _charSize.width,
						  LpGame.gameScreenSize.y + LpGame.gameScreenPos.y - _charSize.height);

	/// ���[
	_enSpace[0] = Vector2(-_charSize.width, -_charSize.height);
	_enSpace[1] = Vector2(-_charSize.width, 0);
	_enSpace[2] = Vector2(-_charSize.width, _charSize.height);
	/// �E�[
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

	/// ���̐���
	_objs.emplace_back(std::make_shared<Player>(Vector2(100, 200), _charSize));
}

void MainScene::AddEnemy(EnemyState state)
{
	_objs.emplace_back(std::make_shared<Enemy>(state));
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
	auto enMax = randNum % 3;

	if (_dbgKey && !_dbgKeyOld)
	{
		
		for (int i = 0; i < enMax; ++i)
		{
			auto invPos = Vector2((_enCnt % 7) * 10, (_enCnt / 7) * 10);
			auto aimPos	= Vector2(LpGame.gameScreenPos.x + ((_enCnt % 7) * 30) + invPos.x,
								  LpGame.gameScreenPos.y + ((_enCnt / 7) * 32) + invPos.y);

			auto space = _enSpace[randNum % 6] + (_enSpace[randNum % 6] * i);
			/// ����тœG���o��������悤�ɂ��Ă���
			auto type = (EN_TYPE)(randNum % static_cast<int>(EN_TYPE::MAX));
			// auto id	  = (EN_ID)(randNum % static_cast<int>(EN_ID::MAX));

			AddEnemy({ _initPos[randNum % 6] + space, _charSize, type, EN_ID::BEE, aimPos });

			++_enCnt;
			_enCnt = (_enCnt <= 20 ? _enCnt : 0);
		}
	
	}

	for (auto obj : _objs)
	{
		/// �ŏ��ɓo�^���ꂽ�G�̱�Ұ��ݶ��Ă����Z���鏈��
		if (obj->GetObjID() == Obj::ENEMY)
		{
			obj->LeadUpdate();
			break;
		}
	}

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

	/// vector�̍폜����͈͂̎w��
	auto eraseBegin = remove_if(_objs.begin(),				// �J�n�ʒu
								_objs.end(),				// �I���ʒu
							    [](std::shared_ptr<Object>& obj) {return (*obj).GetDeath(); });		// move���邩�̔��蕔

	/// �w�肵���͈͂�vector���폜���Ă���
	_objs.erase(eraseBegin, _objs.end());
	return std::move(scene);
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}