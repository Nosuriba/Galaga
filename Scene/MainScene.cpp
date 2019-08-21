#include <algorithm>
#include <stdlib.h>	
#include <time.h>			/// �����̐����Ŏg�p���Ă���
#include <DxLib.h>
#include "MainScene.h"
#include "ResultScene.h"
#include "../Game.h"
#include "../Collision.h"
#include "../DebugConOut.h"

#include "../Object/Shot.h"
#include "../Object/Player.h"
#include "../Object/Bee.h"
#include "../Object/Butterfly.h"
#include "../Object/Boss.h"

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
	InitTbl();

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

	_col = std::make_unique<Collision>();

	_textCnt = 0;
	_textData.emplace_back("PLAYER ");
	_textData.emplace_back("STAGE ");

	/// ���y����~����Ă��邩�̔���p�֐����Ȃ���������
	/// ��Œǉ�����B
	LpAudioMng.PlayBGM("Music/wait.mp3");
	_mode = &MainScene::WaitMode;
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	srand((unsigned int)time(0));

	_ghGameScreen = MakeScreen(LpGame.gameScreenSize.x, LpGame.gameScreenSize.y, true);
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}

void MainScene::InitTbl()
{
	_tblInfo = { 1,0 };

	double posX, posY;
	/// ������ð��وʒu�����߂�v�Z
	posX = LpGame.gameScreenPos.x / 2 + _charSize.width;
	posY = LpGame.gameScreenPos.y / 2 + (_enMax.y - 2) * _charSize.height;
	_tblCtlPos[0] = Vector2(posX, posY);

	/// �E����ð��وʒu�����߂�v�Z
	posX = LpGame.gameScreenPos.x / 2 + _enMax.x * _charSize.width;
	_tblCtlPos[1] = Vector2(posX, posY);
}

void MainScene::CreateEnemy(const shared_itr& enBegin)
{
	auto isCreate = enBegin == _objs.end();
	auto enemy = enBegin;
	for (; enemy != _objs.end(); ++enemy)
	{
		if ((*enemy)->IsMoveTbl())
		{
			isCreate = true;
		}
		else
		{
			isCreate = false;
			break;
		}
	}
	
	/// �G�̐���(���Ő������Ă���)
	if (isCreate)
	{
		auto randNum = rand();
		auto debugPos = Vector2d(200 + (rand() % 10 * 10), 250);
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
				EnemyState state = { _initPos[randNum % 6], _charSize,
									 EN_TYPE::NORMAL, 10 * cnt, debugPos, aimPos };

				AddEnemy(line, state);
				++cnt;
				++_enCnt;
				_enTblInfo[num] = 1;
			}
			LpAudioMng.PlaySE("Music/comeOut.mp3");
		}

		/// �G�𖖔��ɿ�Ă��Ă���
		std::sort(_objs.begin(),
				  _objs.end(),
				  [](shared_obj& obj, shared_obj& obj2) { return (*obj).GetObjID() > (*obj2).GetObjID(); });
	}
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

void MainScene::Draw()
{
	/// �ްѽ�ذ݂̕`����s���Ă���
	auto beforScr = GetDrawScreen();
	SetDrawScreen(_ghGameScreen);
	ClsDrawScreen();

	for (auto obj : _objs)
	{
		if (obj != nullptr)
		{
			obj->Object::Draw();
		}
	}

	if (_mode == &MainScene::WaitMode)
	{
		for (int i = 0; i <= (_textCnt / 120); ++i)
		{
			Vector2 offset(150, LpGame.gameScreenSize.y / 3 + (i * 30));
			for (auto charCode : _textData[i])
			{
				if (charCode >= 'A' || charCode <= 'Z')
				{
					if (charCode <= 0)
					{
						continue;
					}
					if (charCode == 32)
					{
						offset.x += 16;
						continue;
					}
					int id = charCode - 'A';
					DrawGraph(offset.x, offset.y, IMAGE_ID("text")[id], true);
					offset.x += 16;
				}
			}
			DrawGraph(offset.x, offset.y, IMAGE_ID("num")[1], true);
		}
		
	}

	LpGame.AddDrawQue({ _ghGameScreen, LpGame.gameScreenPos.x, LpGame.gameScreenPos.y});
	SetDrawScreen(beforScr);
}

void MainScene::TblMoveUpdate()
{
	if (_tblCtlPos[0].x <= _charSize.width / 2 ||
		_tblCtlPos[1].x >= LpGame.gameScreenSize.x - _charSize.width / 2)
	{
		_tblInfo.second = -_tblInfo.second;
	}
	_tblInfo.first += _tblInfo.second;
}

bool MainScene::PlayerCol(const shared_obj& player, const shared_itr& enBegin)
{
	auto enemy = enBegin;
	for (; enemy != _objs.end(); ++enemy)
	{
		/// �G�Ƃ̓����蔻��
		if (_col->IsCollision(player->GetRect(), (*enemy)->GetRect()))
		{
			return true;
		}

		/// �G�̼��ĂƂ̓����蔻��
		for (auto& shot : (*enemy)->GetShot())
		{
			if (shot != nullptr)
			{
				if (_col->IsCollision(player->GetRect(), shot->GetRect()) &&
					player->IsAlive())
				{
					(*enemy)->ShotDelete(shot);
					return true;
				}
			}
		}
	}
	return false;
}

bool MainScene::EnemyCol(const shared_obj& enemy, const shared_itr& enBegin)
{
	auto player = _objs.begin();
	for (; player != enBegin; ++player)
	{
		/// ��ڲ԰�̼��ĂƂ̓����蔻��
		for (auto shot : (*player)->GetShot())
		{
			if (shot != nullptr)
			{
				if (_col->IsCollision(enemy->GetRect(), shot->GetRect()) &&
					enemy->IsAlive())
				{
					(*player)->ShotDelete(shot);
					return true;
				}
			}
		}
	}
	return false;
}

int MainScene::WaitMode(const std::unique_ptr<InputState>& p)
{
	Draw();
	_textCnt = (_textCnt <= 238 ? _textCnt + 1 : _textCnt);
	if (_textCnt == 120)
	{
		/// ��ڲ԰�̐���
		_objs.emplace_back(std::make_shared<Player>(Vector2(LpGame.gameScreenSize.x / 2 - _charSize.width,
															LpGame.gameScreenSize.y - _charSize.height), _charSize));
	}

	if (!LpAudioMng.CheckSound("Music/wait.mp3"))
	{
		_mode = &MainScene::PlayingMode;
	}
	return 0;
}

int MainScene::PlayingMode(const std::unique_ptr<InputState>& p)
{
	/// �G�̐����O�̐擪���擾���Ă���
	auto enBegin = std::find_if(_objs.begin(),
								_objs.end(),
								[](shared_obj& obj) {return (*obj).GetObjID() == OBJ::ENEMY; });
	auto player = _objs.begin();

	CreateEnemy(enBegin);

	/// �G�𐶐���̐擪���擾���Ă���
	enBegin = std::find_if(_objs.begin(),
		_objs.end(),
		[](shared_obj& obj) {return (*obj).GetObjID() == OBJ::ENEMY; });
	auto enemy = enBegin;


	/// �S�Ă̓G���z�u���ꂽ���̏���
	if (_enCnt >= (_enMax.x * _enMax.y))
	{
		_isTable = true;
		Vector2d pPos;
		pPos = (*player)->GetPos();
		for (; enemy != _objs.end(); ++enemy)
		{
			if ((*enemy)->IsMoveTbl())
			{
				auto isAction = (rand() % 20 == 0);
				if (isAction && _tblInfo.second == 0)
				{
					(*enemy)->SetSigEnd(pPos);
				}
			}
			else
			{
				_isTable = false;
			}
		}
	}

	/// �ŏ��ɓo�^���ꂽ�G�̂ݏ����X�V���鏈��
	enemy = enBegin;
	for (; enemy != _objs.end(); ++enemy)
	{
		if ((*enemy)->IsMoveTbl())
		{
			TblMoveUpdate();
			/// ð��ِ���̍��W�X�V
			for (auto& tPos : _tblCtlPos)
			{
				tPos.x += _tblInfo.second;
			}
		}
		(*enemy)->LeadAnimUpdate();
		(*enemy)->SetTblInfo(_tblInfo);
		break;
	}
	/// ð��ُ��̍X�V
	if (!_isTable)
	{
		_tblInfo.second = (_tblInfo.second == 0 ? 1 : _tblInfo.second);
	}
	else
	{
		/// �S���z�u���ꂽ��A�^�񒆂ɓ��������Ƃ����ړ����~�߂Ă���
		_tblInfo.second = (_tblInfo.first == 0 ? 0 : _tblInfo.second);
	}

	/// �G����ڲ԰�̍X�V
	for (auto obj : _objs)
	{
		obj->Update(p);
	}

	/// ��ڲ԰�̓����蔻��
	player = _objs.begin();
	for (; player != enBegin; ++player)
	{
		if (PlayerCol((*player), enBegin))
		{
			(*player)->ChangeAlive();
		}
	}

	/// �G�̓����蔻��
	enemy = enBegin;
	for (; enemy != _objs.end(); ++enemy)
	{
		if (EnemyCol((*enemy), enBegin))
		{
			(*enemy)->ChangeAlive();
		}
	}

	/// �ްѽ�ذݏ�̕`��
	Draw();
	/// vector�̍폜����͈͂̎w��
	auto eraseBegin = remove_if(_objs.begin(),				// �J�n�ʒu
		_objs.end(),				// �I���ʒu
		[](shared_obj& obj) {return (*obj).GetDeath(); });		// move���邩�̔��蕔

	/// �w�肵���͈͂�vector���폜���Ă���
	_objs.erase(eraseBegin, _objs.end());

	return 0;
}

unique_scene MainScene::Update(unique_scene scene, const std::unique_ptr<InputState>& p)
{
	(this->*_mode)(p);

	if (_enCnt >= (_enMax.x * _enMax.y))
	{
		auto isClear = true;
		for (auto obj : _objs)
		{
			if (obj->GetObjID() == OBJ::ENEMY)
			{
				isClear = false;
				break;
			}
		}
		
		if (isClear)
		{
			return std::make_unique<ResultScene>();
		}
	}
	return std::move(scene);
}