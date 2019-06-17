#include <DxLib.h>
#include "Game.h"
#include "Input.h"
#include "Object/Player.h"
#include "Scene/Scene.h"
#include "Scene/TitleScene.h"

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
	DxLib::SetWindowText("1701310_ñkêÏ èÅàÍ : Galaga");
	if (DxLib_Init() == -1)
	{
		return;
	}
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	_scene = std::make_shared<TitleScene>();
}

void Game::Run()
{
	Input input;
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		ClsDrawScreen();

		input.Update();
		_scene->Update(input);

		ScreenFlip();
	}
}

void Game::End()
{
	DxLib_End();
}

void Game::ChangeScene(const shared_scene & scene)
{
	_scene = scene;
}

