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
	void Draw();
	unique_scene Update(unique_scene scene, const Input& p) override;
	const SCN_ID GetSceneID() const override;
private:
	std::list<std::shared_ptr<Object>> objList;

	int _ghGameScreen;		// ¹Þ°Ñ½¸Ø°Ý‚Ì‰æ‘œÊÝÄÞÙ
};

