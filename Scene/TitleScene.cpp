#include "../Game.h"
#include "TitleScene.h"
#include "MainScene.h"

#include "../Input/KeyState.h"

TitleScene::TitleScene()
{
	
	Init();
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{
	_dispCnt = 0;
	input = std::make_shared<KeyState>();
	_ghTitleScreen = MakeScreen(LpGame.gameScreenSize.x, LpGame.gameScreenSize.y, true);
}

const SCN_ID TitleScene::GetSceneID() const
{
	return SCN_ID::TITLE;
}

void TitleScene::Draw()
{
	auto beforScr = GetDrawScreen();
	SetDrawScreen(_ghTitleScreen);
	ClsDrawScreen();

	if (_dispCnt >= 30)
	{
		Vector2 offset(120, 300);
		for (auto charCode : "PRESS SPACE KEY")
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
	}

	LpGame.AddDrawQue({ _ghTitleScreen, LpGame.gameScreenPos.x, LpGame.gameScreenPos.y });
	SetDrawScreen(beforScr);
}

unique_scene TitleScene::Update(unique_scene scene, const std::unique_ptr<InputState>& p)
{
	_dispCnt = (_dispCnt <= 60 ? _dispCnt + 1 : 0);
	if (p->IsTrigger(INPUT_ID::START))
	{
		return std::make_unique<MainScene>();
	}

	Draw();
	return std::move(scene);
}


