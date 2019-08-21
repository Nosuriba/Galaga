#pragma once
#include "Scene.h"

class InputState;

class TitleScene :
	public Scene
{
public:
	TitleScene();
	~TitleScene();

	void Init() override;
	unique_scene Update(unique_scene scene, const std::unique_ptr<InputState>& p) override;
private:
	void Draw();

	int _ghTitleScreen;
	int _dispCnt;

	std::shared_ptr<InputState> input;
};

