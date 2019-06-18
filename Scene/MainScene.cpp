#include "../Game.h"
#include "MainScene.h"
#include "ResultScene.h"

/// ���`������邽�߂Ƀt�@�C����ǉ������̂Ō�ŏ���
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
	/// ���̐���
	objs.push_back(std::make_shared<Player>(Vector2f(0, 0), Vector2f(0, 0)));
	objs.push_back(std::make_shared<Enemy>(Vector2f(200, 100), Vector2f(0,0)));
}

void MainScene::Update(const Input & p)
{
	/// �v���C���[�ƓG�̉��`��
	for (auto obj : objs)
	{
		//obj->Draw();
		obj->Draw(ImageMng::GetInstance().GetID("image/flag.png"));
		obj->Update(p);
	}

	DrawString(0, 0, "Main", 0xffffff);
	if (p.IsKeyTrigger(KEY_INPUT_SPACE))
	{
		Game::GetInstance().ChangeScene(new ResultScene());
	}
}
