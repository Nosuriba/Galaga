#pragma once

#include <vector>
#include <memory>
#include <tuple>
#include "Vector2.h"

class Scene;

#define LpGame (Game::GetInstance())

using unique_scene = std::unique_ptr<Scene>;
using draw_queT = std::tuple<int, int, int>;

enum class DRAW_QUE
{
	IMAGE,
	X,
	Y
};

class Game
{
public:
	static Game & GetInstance()
	{
		return *s_Instance;
	}

	void Init();
	void Run();

	bool AddDrawQue(draw_queT dQue);

	const Vector2 screenSize;
	const Vector2 gameScreenSize;
	const Vector2 gameScreenPos;

private:
	Game();
	~Game();

	void Draw();
	struct GameDeleter
	{
		void operator()(Game * game) const
		{
			delete game;
		}
	};

	// tupleの要素(1.画像ハンドル, 2.X座標, 3.Y座標)
	std::vector<draw_queT> _drawVector;
	static std::unique_ptr<Game, GameDeleter> s_Instance;
	unique_scene _scene;
};

