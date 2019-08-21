#include <DxLib.h>
#include "../Game.h"
#include "TitleScene.h"
#include "ResultScene.h"

ResultScene::ResultScene()
{
	Init();
	_dispCnt = 0;
	LpAudioMng.PlayBGM("Music/clear.mp3");
}

ResultScene::~ResultScene()
{
}

void ResultScene::Init()
{
	_ghResultScene = MakeScreen(LpGame.gameScreenSize.x, LpGame.gameScreenSize.y, true);
}

const SCN_ID ResultScene::GetSceneID() const
{
	return SCN_ID::RESULT;
}

void ResultScene::Draw()
{
	/// ¹Þ°Ñ½¸Ø°Ý‚Ì•`‰æ‚ðs‚Á‚Ä‚¢‚é
	auto beforScr = GetDrawScreen();
	SetDrawScreen(_ghResultScene);
	ClsDrawScreen();
	Vector2 offset(150, LpGame.gameScreenSize.y / 3);
	for (auto charCode : "GAME CLEAR")
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
	LpGame.AddDrawQue({ _ghResultScene, LpGame.gameScreenPos.x, LpGame.gameScreenPos.y });
	SetDrawScreen(beforScr);
}

unique_scene ResultScene::Update(unique_scene scene, const std::unique_ptr<InputState>& p)
{
	Draw();
	_dispCnt = (_dispCnt <= 60 ? _dispCnt + 1 : 0);
	if (p->IsTrigger(INPUT_ID::START))
	{
		return std::make_unique<TitleScene>();
	}
	return std::move(scene);
}
