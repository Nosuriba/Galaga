#include <DxLib.h>
#include "Game.h"
#include "Input.h"
#include "Object/Player.h"
#include "Scene/Scene.h"
#include "Scene/TitleScene.h"
#include "DebugConOut.h"

std::unique_ptr<Game, Game::GameDeleter> Game::s_Instance(new Game());

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	DxLib::SetGraphMode(800, 600, 32);
	DxLib::ChangeWindowMode(true);
	DxLib::SetWindowText("1701310_北川 潤一 : Galaga");
	if (DxLib_Init() == -1)
	{
		return;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	_scene = std::make_unique<TitleScene>();
	/*TRACE("DXLIBの初期化終了\n");
	TRACE("%d", 20);*/
}

void Game::Run()
{
	Input input;			/// こいつがInputStateのｸﾗｽに変わりそう...
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClsDrawScreen();

		input.Update();
 		_scene->Update(input);

		ScreenFlip();
	}
	DxLib_End();
}

void Game::ChangeScene(Scene * scene)
{
	_scene.reset(scene);
}

