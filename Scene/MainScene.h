#pragma once
#include <list>
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
	std::list<std::shared_ptr<Object>> objList;
};

