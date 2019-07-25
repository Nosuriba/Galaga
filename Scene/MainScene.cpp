#include <algorithm>
#include <stdlib.h>	
#include <time.h>				/// ����ѐ�������߂����A�����������������Ȃ�
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

	/// �G��ð��ق𐶐����Ă���
	_enTblInfo.reserve(_enMax.x * _enMax.y);
	for (int i = 0; i < (_enMax.x * _enMax.y); ++i)
	{
		_enTblInfo.emplace_back(0);
	}
	/// �����ð��قɂ͔z�u�ł��Ȃ��悤�ɂ��Ă���
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

	/// ���[
	_initPos[0] = Vector2(-_charSize.width, _charSize.height);
	_initPos[1] = Vector2(-_charSize.width, LpGame.gameScreenSize.y / 2);
	_initPos[2] = Vector2(-_charSize.width, LpGame.gameScreenSize.y - _charSize.height * 2);
	/// �E�[
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

	/// ��ڲ԰�̐���
	_objs.emplace_back(std::make_shared<Player>(Vector2(100, LpGame.gameScreenSize.y - _charSize.height), _charSize));
}

void MainScene::AddEnemy(const int & line, const EnemyState & state)
{
	if (line == 0)
	{
		/// ��؂̐���
		_objs.emplace_back(std::make_shared<Scorpion>(state));
	}
	else if (line == 1 || line == 2)
	{
		/// ���̐���
		_objs.emplace_back(std::make_shared<Butterfly>(state));
	}
	else
	{
		/// �I�̐���
		_objs.emplace_back(std::make_shared<Bee>(state));
	}
}

void MainScene::Draw()
{
	/// �ްѽ�ذ݂̕`����s���Ă���
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
	/// �G�����������邽�߂̐ݒ�
	_dbgKeyOld = _dbgKey;
	_dbgKey    = CheckHitKey(KEY_INPUT_SPACE);

	auto randNum = rand();

	/// �G�̐���(���Ő������Ă���)
	if (_dbgKey && !_dbgKeyOld)
	{
		for (int cnt = 0; cnt < 3;)
		{
			/// �o�����Ă���G���ő吔�𒴂��Ă��鎞�A�����𔲂���
			if (_enCnt >= (_enMax.x * _enMax.y))
			{
				break;
			}
			auto num = rand() % (_enMax.x * _enMax.y);
			if (!_enTblInfo[num])
			{
				/// �G�̏��ݒ�
				auto invPos = Vector2((num % _enMax.x) * 5, (num / _enMax.x) * 5);
				auto aimPos = Vector2d(LpGame.gameScreenPos.x / 2 + ((num % _enMax.x) * _charSize.width) + invPos.x,
									   LpGame.gameScreenPos.y / 2 + ((num / _enMax.x) * _charSize.height) + invPos.y);
				
				/// �G�̐���
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
		/// �ŏ��ɓo�^���ꂽ�G�̱�Ұ��ݶ��Ă����Z���鏈��
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
			/// ���ޯ�ޒ��̂��߁A�G�����S�����ʒu�ɍĐ����ł���悤�ɂ��Ă���
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