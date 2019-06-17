#pragma once
#include "Scene.h"

class Bubble;

class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();
	
	void Init();
	void Update(const Input & p);
private:
};

