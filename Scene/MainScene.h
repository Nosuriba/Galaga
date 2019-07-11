#pragma once
#include <list>
#include "Scene.h"
#include "../Object/Enemy.h"

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
	std::vector<std::shared_ptr<Object>> _objVector;

	
	void SetEnemy();
	void AddEnemy(const Vector2& pos, EN_TYPE type);

	int _ghGameScreen;		// ¹Þ°Ñ½¸Ø°Ý‚Ì‰æ‘œÊÝÄÞÙ
};

