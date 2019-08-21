#pragma once
#include "Scene.h"
class ResultScene :
	public Scene
{
public:
	ResultScene();
	~ResultScene();
	void Init()override;
	unique_scene Update(unique_scene scene, const std::unique_ptr<InputState>& p) override;
private:
	void Draw();

	int _ghResultScene;
	int _dispCnt;
};

