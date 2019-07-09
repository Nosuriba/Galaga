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
		obj->Object::Draw();

	}
	LpGame.AddDrawQue({ _ghGameScreen, LpGame.gameScreenPos.x, LpGame.gameScreenPos.y });
}

unique_scene MainScene::Update(unique_scene scene, const Input & p)
{
	/// �v���C���[�ƓG�̉��`��
	for (auto obj : _objVector)
	{
		obj->Update();
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
	if (CheckHitKey(KEY_INPUT_NUMPAD2))
	{
		_objVector[2]->SetAlive(false);
	}

	auto obj = _objVector.begin();
	for (;obj != _objVector.end();)
	{
		auto cnt = obj - _objVector.begin();
		if (!(*obj)->GetAlive())
		{
			obj = _objVector.erase(obj);
			continue;
		}
		++obj;
	}
	

	return std::move(scene);
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}