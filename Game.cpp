#include <DxLib.h>
#include "Game.h"
#include "Input.h"
#include "Object/Player.h"
#include "Scene/Scene.h"
#include "Scene/TitleScene.h"
#include "Scene/MainScene.h"
#include "Common/ImageMng.h"
#include "DebugConOut.h"
#include "DebugDisp.h"

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
	DxLib::SetWindowText("1701310_–kì ˆê : Galaga");
	if (DxLib_Init() == -1)
	{
		return;
	}
	SET_IMAGE_ID("˜g", "image/frame.png");
	_dbgSetUp(200);

	_scene = std::make_unique<MainScene>();
}

void Game::Run()
{
	Input input;			/// ‚±‚¢‚Â‚ªInputState‚Ì¸×½‚É•Ï‚í‚è‚»‚¤...
	
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
 		_dbgStartUp;
		_drawVector.clear();

		input.Update();
		_scene = _scene->Update(std::move(_scene), input);

		auto debug = GetDrawScreen();
		/// ‘‚«‚İ‚ğs‚Á‚½½¸Ø°İ‚ğÊŞ¯¸ÊŞ¯Ì§‚É‚Ü‚Æ‚ß‚Ä•`‰æ‚·‚é
		DxLib::SetDrawScreen(DX_SCREEN_BACK);
		debug = GetDrawScreen();
		ClsDrawScreen();

		/// ŠO˜g‚Ì“o˜^
		AddDrawQue({ IMAGE_ID("˜g")[0], 0, 0 });
		Draw();
		ScreenFlip();
	}
	DxLib_End();
}

bool Game::AddDrawQue(draw_queT dQue)
{
	/// ‰æ‘œÊİÄŞÙ‚Ì“Ç‚İ‚İ‚É¸”s‚µ‚½
	if (std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue) == -1)
	{
		return false;
	}
	_drawVector.emplace_back(dQue);
	return true;
}

void Game::Draw()
{
	_dbgAddDraw;
	for (auto dQue : _drawVector)
	{
		DrawGraph(std::get<static_cast<int>(DRAW_QUE::X)>(dQue),
				  std::get<static_cast<int>(DRAW_QUE::Y)>(dQue),
				  std::get<static_cast<int>(DRAW_QUE::IMAGE)>(dQue),
				  true);
	}

}
