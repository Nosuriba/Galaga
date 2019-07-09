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
	Init();

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
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
	_ghGameScreen = MakeScreen(LpGame.gameScreenSize.x, LpGame.gameScreenSize.y, true);

	/// ���̐���
	_objVector.emplace_back(std::make_shared<Player>(Vector2(100, 200)));
	SetEnemy();
}

void MainScene::SetEnemy()
{
	int offset = 100;
	TRACE("%d�̖ڂ̓G�𐶐�\n", _objVector.size());
	_objVector.emplace_back(std::make_shared<Enemy>(Vector2(offset + 120, 200)));

	for (int i = 0; i < 9; ++i)
	{
		TRACE("%d�̖ڂ̓G�𐶐�\n", _objVector.size());
		_objVector.emplace_back(std::make_shared<Enemy>(Vector2(offset + 80 + (40 * (i % 3)), 160 - (40 * (i / 3)))));
	}

}


void MainScene::Draw()
{
	SetDrawScreen(_ghGameScreen);
	ClsDrawScreen();
	/// �v���C���[�ƓG�̉��`��
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
	/// �v���C���[�ƓG�̉��`��
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

	/// �폜�����̓��C���V�[�����ŏ����悤�ɂ���
	/// �e���L�[�ŉ������ʒu�̓G���폜���鏈���͂ǂ����悤����
	/// ���݂̐ݒ���ȒP�ɂ܂Ƃ߂�ꂽ�炢�����ǂ�
	/// 

	auto obj = _objVector.begin() + 1;
	for (; obj != _objVector.end(); ++obj)
	{
		auto cnt = obj - _objVector.begin() - 1;
		if ((*obj) == nullptr)
		{
			continue;
		}
		(*obj)->SetAlive(!CheckHitKey(_dbgKeyTbl[cnt]));
	}

	/// vector�̒��g����ɂ��邩�̏���
	obj = _objVector.begin() + 1;
	for (;obj != _objVector.end(); ++obj)
	{
		if ((*obj) == nullptr)
		{
			continue;
		}

		/// �G�����S���Ă������A���g����ɂ���
		if (!(*obj)->GetAlive())
		{
			(*obj) = nullptr;
		}
	}
	

	return std::move(scene);
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}