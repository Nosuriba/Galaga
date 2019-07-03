#include <DxLib.h>
#include "Game.h"
#include "Input.h"
#include "Object/Player.h"
#include "Scene/Scene.h"
#include "Scene/TitleScene.h"
#include "Scene/MainScene.h"
#include "Common/ImageMng.h"
#include "DebugConOut.h"

std::unique_ptr<Game, Game::GameDeleter> Game::s_Instance(new Game());

Game::Game() : screenSize{ 800,600 },
gameScreenSize{ 500,390 },
gameScreenPos{ (screenSize.x - gameScreenSize.x) / 2, (screenSize.y - gameScreenSize.y) / 2 }
{
}

Game::~Game()
{
}

void Game::Init()
{
	DxLib::SetGraphMode(screenSize.x, screenSize.y, 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1701310_ñkêÏ èÅàÍ : Galaga");
	if (DxLib_Init() == -1)
	{
		return;
	}
	

	SET_IMAGE_ID("òg", "image/frame.png");

	_scene = std::make_unique<MainScene>();
}

void Game::Run()
{
	Input input;			/// Ç±Ç¢Ç¬Ç™InputStateÇÃ∏◊ΩÇ…ïœÇÌÇËÇªÇ§...
	
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		_drawList.clear();
		input.Update();
		_scene = _scene->Update(std::move(_scene), input);
		DxLib::SetDrawScreen(DX_SCREEN_BACK);
		ClsDrawScreen();
		AddDrawQue({ IMAGE_ID("òg")[0], 0, 0 });
		Draw();
		ScreenFlip();
	}
	DxLib_End();
}

bool Game::AddDrawQue(draw_queT dQue)
{
	/// âÊëú ›ƒﬁŸÇÃì«Ç›çûÇ›Ç…é∏îsÇµÇΩéû
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) == -1)
	{
		return false;
	}
	_drawList.emplace_back(dQue);
	return true;
}

void Game::Draw()
{
	for (auto dQue : _drawList)
	{
		DrawGraph(std::get<static_cast<int>(DRAW_QUE::X)>(dQue),
				  std::get<static_cast<int>(DRAW_QUE::Y)>(dQue),
				  std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue),
				  true);
	}
}
