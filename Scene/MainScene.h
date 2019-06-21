#pragma once
#include "Scene.h"

class Object;

class MainScene :
	public Scene
{
public:
	MainScene();
	~MainScene();
	void Init()override;
	void Update(const Input& p)override;
	const SCN_ID GetSceneID() const override;
private:
	std::vector<std::shared_ptr<Object>> objs;
};

