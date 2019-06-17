#include "../Game.h"
#include "MainScene.h"
#include "ResultScene.h"

/// ���`������邽�߂Ƀt�@�C����ǉ������̂Ō�ŏ���
#include "../Object/Object.h"
#include "../Object/Player.h"
#include "../Object/Enemy.h"

MainScene::MainScene()
{
}


MainScene::~MainScene()
{
}

void MainScene::Init()
{
}

void MainScene::Update(const Input & p)
{
	/// �v���C���[�ƓG�̉��`��
	std::vector<std::unique_ptr<Object>> obj;
	obj.push_back(std::make_unique<Player>());
	obj.push_back(std::make_unique<Enemy>());
	for (auto& itr : obj)
	{
		itr->Draw();
	}

	DrawString(0, 0, "Main", 0xffffff);
	if (p.IsKeyTrigger(KEY_INPUT_SPACE))
	{
		LpGame.ChangeScene(std::make_shared<ResultScene>());
	}
}
