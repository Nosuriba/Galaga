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
	_enCnt = 0;
	/// �G��ׂ̻��ޕ����炵�Ă��镔��������
	/// ���[
	_initPos[0] = Vector2(-LpGame.gameScreenPos.x, -LpGame.gameScreenPos.y);
	_initPos[1] = Vector2(-LpGame.gameScreenPos.x, LpGame.gameScreenSize.y / 2);
	_initPos[2] = Vector2(-LpGame.gameScreenPos.x, LpGame.gameScreenSize.y + LpGame.gameScreenPos.y - 32);
	
	/// �E�[
	_initPos[3] = Vector2(LpGame.gameScreenSize.x + LpGame.gameScreenPos.x - 30, -LpGame.gameScreenPos.y);
	_initPos[4] = Vector2(LpGame.gameScreenSize.x + LpGame.gameScreenPos.x - 30, 
						  LpGame.gameScreenSize.y / 2);
	_initPos[5] = Vector2(LpGame.gameScreenSize.x + LpGame.gameScreenPos.x - 30,
						  LpGame.gameScreenSize.y + LpGame.gameScreenPos.y - 32);
	Init();
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	_ghGameScreen = MakeScreen(LpGame.gameScreenSize.x, LpGame.gameScreenSize.y, true);

	/// ���̐���
	_objs.emplace_back(std::make_shared<Player>(Vector2(100, 200)));
	// SetEnemy();
}

void MainScene::SetEnemy()
{
	int offset = 100;
	AddEnemy({ Vector2(offset + 120, 200), EN_TYPE::BOSS, LpGame.gameScreenSize / 2 });
	TRACE("%d�̖ڂ̓G�𐶐�\n", (int)_objs.size() - 1);
	for (int i = 0; i < 9; ++i)
	{
		AddEnemy({ Vector2(offset + 80 + (40 * (i % 3)), 160 - (40 * (i / 3))), EN_TYPE::BONUS , LpGame.gameScreenSize / 2});
		TRACE("%d�̖ڂ̓G�𐶐�\n", (int)_objs.size() - 1);
	}
}

void MainScene::AddEnemy(EnemyState state)
{
	_objs.emplace_back(std::make_shared<Enemy>(state));
}

void MainScene::Draw()
{
	SetDrawScreen(_ghGameScreen);
	ClsDrawScreen();
	/// �v���C���[�ƓG�̉��`��
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
	static int num = 0;
	_dbgKeyOld = _dbgKey;
	_dbgKey    = CheckHitKey(KEY_INPUT_SPACE);

	if (_dbgKey && !_dbgKeyOld)
	{
		/// �G�̊Ԋu���󂯂鏈���������Ă���
		auto invPos = (_enCnt / 7) * 10;
		auto pos = Vector2(LpGame.gameScreenPos.x + ((_enCnt % 7) * 30) + 10, 
						   LpGame.gameScreenPos.y + ((_enCnt / 7) * 32) + invPos);
		//AddEnemy({ _initPos[rand() % 6], EN_TYPE::NORMAL, pos});
		AddEnemy({ _initPos[num % 6], EN_TYPE::NORMAL, pos});
		++num;
		++_enCnt;
		_enCnt = (_enCnt <= 20 ? _enCnt : 0);
	}

	/// �v���C���[�ƓG�̉��`��
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