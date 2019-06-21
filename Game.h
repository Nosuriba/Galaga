#pragma once

#include <vector>
#include <memory>

class Scene;

using unique_scene = std::unique_ptr<Scene>;

class Game
{
public:
	static Game & GetInstance()
	{
		return *s_Instance;
	}

	void Init();
	void Run();

	void ChangeScene(Scene * scene);
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
	unique_scene _scene;
};

