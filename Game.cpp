#include <DxLib.h>
#include "Game.h"
#include "Object/Player.h"
#include "Scene/Scene.h"
#include "Scene/TitleScene.h"
#include "Scene/MainScene.h"
#include "Common/ImageMng.h"
#include "Input/KeyState.h"
#include "Input/PadState.h"
#include "DebugConOut.h"
#include "DebugDisp.h"
#include "resource.h"

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
	DxLib::SetWindowIconID(IDI_ICON1);
	if (DxLib_Init() == -1)
	{
		return;
	}
	_dbgSetUp(200);

	/// ‰æ‘œID‚Ì‰Šúİ’è
	SET_IMAGE_ID("frame",	 "image/frame.png");
	SET_IMAGE_ID("player",	 "image/player.png", Vector2(3, 1), Vector2(30, 32));
	SET_IMAGE_ID("pl_blast", "image/pl_blast.png", Vector2(4, 1), Vector2(64, 64));
	SET_IMAGE_ID("enemy",	 "image/enemy.png", Vector2(10, 3), Vector2(30, 32));
	SET_IMAGE_ID("en_blast", "image/en_blast.png", Vector2(5, 1), Vector2(64, 64));
	SET_IMAGE_ID("shot",	 "image/shot.png", Vector2(2, 1), Vector2(3, 8));
	SET_IMAGE_ID("text",	 "image/text.png", Vector2(30, 1), Vector2(16, 16));
	SET_IMAGE_ID("num",		 "image/num.png", Vector2(10, 1), Vector2(16, 16));
	_scene = std::make_unique<TitleScene>();
}

void Game::Run()
{
	std::unique_ptr<InputState> input;
	if (GetJoypadNum() == 0)
	{
		input = std::make_unique<KeyState>();
	}
	else
	{
		input = std::make_unique<PadState>();
	}

	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
 		_dbgStartUp;
		_drawVector.clear();
	
		input->Update();
		_scene = _scene->Update(std::move(_scene), input);

		auto debug = GetDrawScreen();
		/// ‘‚«‚İ‚ğs‚Á‚½½¸Ø°İ‚ğÊŞ¯¸ÊŞ¯Ì§‚É‚Ü‚Æ‚ß‚Ä•`‰æ‚·‚é
		DxLib::SetDrawScreen(DX_SCREEN_BACK);
		debug = GetDrawScreen();
		ClsDrawScreen();

		/// ŠO˜g‚Ì“o˜^
		AddDrawQue({ IMAGE_ID("frame")[0], 0, 0 });
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
