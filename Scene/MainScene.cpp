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
	Init();
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
	AddEnemy(Vector2(offset + 120, 200), EN_TYPE::BOSS);
	TRACE("%d�̖ڂ̓G�𐶐�\n", (int)_objVector.size() - 1);
	for (int i = 0; i < 9; ++i)
	{
		AddEnemy(Vector2(offset + 80 + (40 * (i % 3)), 160 - (40 * (i / 3))), EN_TYPE::BONUS);
		TRACE("%d�̖ڂ̓G�𐶐�\n", (int)_objVector.size() - 1);
	}
}

void MainScene::AddEnemy(const Vector2& pos, EN_TYPE type)
{
	_objVector.emplace_back(std::make_shared<Enemy>(pos, type));
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
		unsigned int num;
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
	auto eraseBegin = remove_if(_objVector.begin(),				// �J�n�ʒu
								_objVector.end(),				// �I���ʒu
							    [](std::shared_ptr<Object>& obj) {return (*obj).GetDeath(); });		// move���邩�̔��蕔

	/// �w�肵���͈͂�vector���폜���Ă���
	_objVector.erase(eraseBegin, _objVector.end());

	return std::move(scene);
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}