#pragma once
#include "Scene.h"

class GameManager;

class MainScene :
	public Scene
{
public:
	MainScene();
	~MainScene();

	void Init();
	void Update(const Input & p);
private:
};

