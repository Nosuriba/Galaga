#pragma once

#include <vector>
#include <memory>

#define LpGame (Game::GetInstance())

class Scene;

using shared_scene = std::shared_ptr<Scene>;

class Game
{
public:
	static Game & GetInstance()
	{
		return *s_Instance;
	}

	void Init();
	void Run();
	void End();

	void ChangeScene(const shared_scene& scene);
private:
	Game();
	~Game();
	struct GameDeleter
	{
		void operator()(Game * game) const
		{
			delete game;
		}
	};

	static std::unique_ptr<Game, GameDeleter> s_Instance;
	std::shared_ptr<Scene> _scene;
};

