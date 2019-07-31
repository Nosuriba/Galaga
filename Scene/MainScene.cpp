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
#include "../Object/Boss.h"
#include "../Common/ImageMng.h"

MainScene::MainScene() : _charSize(30,32), _enMax(10, 5)
{
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

	ResetTbl();

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

void MainScene::ResetTbl()
{
	_tblInfo = { 0,0 };

	double posX, posY;
	/// ������ð��وʒu�����߂�v�Z
	posX = LpGame.gameScreenPos.x / 2 + _charSize.width;
	posY = LpGame.gameScreenPos.y / 2 + (_enMax.y - 2) * _charSize.height;
	_tblCtlPos[0] = Vector2(posX, posY);

	/// �E����ð��وʒu�����߂�v�Z
	posX = LpGame.gameScreenPos.x / 2 + _enMax.x * _charSize.width;
	_tblCtlPos[1] = Vector2(posX, posY);
}

void MainScene::AddEnemy(const int & line, const EnemyState & state)
{
	if (line == 0)
	{
		/// ��؂̐���
		_objs.emplace_back(std::make_shared<Boss>(state));
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

void MainScene::TblMoveUpdate()
{
	if (_tblCtlPos[0].x <= _charSize.width / 2 || 
		_tblCtlPos[1].x >= LpGame.gameScreenSize.x  - _charSize.width / 2)
	{
		_tblInfo.second = -_tblInfo.second;
	}
	_tblInfo.first += _tblInfo.second;
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
		for (int cnt = 0; cnt < 8;)
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
				auto aimPos = Vector2d(LpGame.gameScreenPos.x / 2 + ((num % _enMax.x) + 1) * _charSize.width,
									   LpGame.gameScreenPos.y / 2 + ((num / _enMax.x) - 1) * _charSize.height);
				
				/// �G�̐���
				auto line = num / _enMax.x;
				auto debugPos = Vector2d(200, 250);
				EnemyState state = { _initPos[randNum % 6], _charSize, 
									 EN_TYPE::NORMAL, num, 10 * cnt, aimPos};
				
				AddEnemy(line, state);
				/// ���Ӳ�ނ̖ڕW�n�_��ݒ肵�Ă���
				_objs[_objs.size() - 1]->SetSigEnd(debugPos);
				++cnt;
				++_enCnt;
				_enTblInfo[num] = 1;
			}
		}
	}

	for (auto obj : _objs)
	{
		/// �ŏ��ɓo�^���ꂽ�G�̱�Ұ��ݶ��Ă����Z���鏈��
		if (obj->GetObjID() == OBJ::ENEMY)
		{
			if (obj->CheckMoveTbl())
			{
				_tblInfo.second = (_tblInfo.second == 0 ? 1 : _tblInfo.second);
				TblMoveUpdate();
				/// ð��ِ���̍��W�X�V
				for (auto& tPos : _tblCtlPos)
				{
					tPos.x += _tblInfo.second;
				}
			}
			else
			{
				//// ���������ޯ�ޗp�łƂ肠��������Ă���̂ŁA�ォ�����
				ResetTbl();
			}
			/// �ŏ��̓G��ð��قɔz�u������ð��ق̈ړ����J�n����悤�ȏ������g�p
			obj->LeadAnimUpdate();
			obj->SetMoveTbl(_tblInfo);
			break;
		}
	}

	for (auto obj : _objs)
	{
		obj->Update();
		if (obj->GetDeath() && obj->GetObjID() == OBJ::ENEMY)
		{
			/// ���ޯ�ޒ��̂��߁A�G�����S�����ʒu�ɍĐ����ł���悤�ɂ��Ă���
			_enTblInfo[obj->GetEnemyNum()] = 0;
			--_enCnt;
		}
	}

	/// ���ޯ�ޗp�ō��������
	auto checkEnemy = false;
	for (auto obj : _objs)
	{
		if (obj->GetObjID() == OBJ::ENEMY)
		{
			checkEnemy = true;
		}
	}
	if (!checkEnemy)
	{
		ResetTbl();
	}

	/// ð��ِ�������ޯ�ޕ`��
	for (auto& tPos : _tblCtlPos)
	{
 		_dbgDrawBox(tPos.x - _charSize.width / 2, tPos.y - _charSize.height / 2,
					tPos.x + _charSize.width / 2, tPos.y + _charSize.height / 2,
					0xffff00, true);
		_dbgDrawFormatString(0, 0, 0xffffff, "�ړ��� : %d", _tblInfo.first);
	}
	
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