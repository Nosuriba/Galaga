#include "../Game.h"
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
	objList.emplace_back(std::make_shared<Player>(Vector2f(500, 450), Vector2f(0, 0)));
	objList.emplace_back(std::make_shared<Enemy>(Vector2f(300, 300), Vector2f(0,0)));
}

void MainScene::Draw()
{
	
	/// debug�p�̕`���������Ascreen�̏������ɖ߂����߂�
	int ghBefor = GetDrawScreen();
	/// SetDrawScreen�̎g���Ɛ^���ÂɂȂ�̂ŁA���̕����𒲂ׂ�
	SetDrawScreen(_ghGameScreen);
	ClsDrawScreen();
	/// �v���C���[�ƓG�̉��`��
	for (auto obj : objList)
	{
		obj->Object::Draw();

	}
	LpGame.AddDrawQue({ _ghGameScreen, LpGame.gameScreenPos.x, LpGame.gameScreenPos.y });
	SetDrawScreen(ghBefor);
}

unique_scene MainScene::Update(unique_scene scene, const Input & p)
{
	/// �v���C���[�ƓG�̉��`��
	for (auto obj : objList)
	{
		obj->Update();
	}

	Draw();

	DrawString(0, 0, "Main", 0xffffff);

	if (p.IsKeyTrigger(KEY_INPUT_SPACE))
	{
		return std::make_unique<ResultScene>();
	}

	return std::move(scene);
}

const SCN_ID MainScene::GetSceneID() const
{
	return SCN_ID::MAIN;
}
